#include "BPUApp.hpp"

#include <execution>
#include <algorithm>
#include <cmath>
#include <opencv2/highgui.hpp>
#include <QWindow>
#include <QMessageBox>
#include "../Tools/DetectionTools.hpp"
#include "../Tools/RGBCameraInput.hpp"
#include "../GUI/ProjectorDisplay.hpp"
#include "../GUI/QtGUI.hpp"
#include "../gamemodes/GameMode.hpp"


QVector2D BPUApp::_frame2window(const QVector2D frame_coordinates) const
{
   float x = frame_coordinates.x() * (_window_size.height() / float(_frame_size.height()));
   float y = frame_coordinates.y() * (_window_size.width() / float(_frame_size.width()));

   return QVector2D(x, y);
}


int BPUApp::_err_msg(const QString& msg)
{
   return QMessageBox::critical( &_main_gui, "Error", msg,
                                 QMessageBox::Retry | QMessageBox::Close, QMessageBox::Retry);
}


unsigned long BPUApp::_get_corresponding_id(const QRectF& rect)
{
   std::map<const float, unsigned long> dist2id;

   for (auto const& [id, circle]: _circles)
   {
      float dist = sqrt(pow(circle.x() - rect.x(), 2) + pow(circle.y() - rect.y(), 2));

      dist2id[dist] = id;
   }

   float min_dist = 999999.0;
   unsigned long min_id = 0;
   for (auto const& [dist, id] : dist2id)
   {
      if (dist < min_dist)
      {
         min_dist = dist;
         min_id = id;
      }
   }

   if (min_dist < _r_min)
      return min_id;

   return -1;
}


BPUApp::BPUApp(int& argc, char** argv) :
   QApplication(argc, argv),
   _game_mode(nullptr),
   _rgb_cam(RGBCameraInput::getInstance()),
   _circles_id_count(0),
   _r_min(0),
   _r_max(100),
   _dist_between_circles(0.f),
   _detection_param1(100),
   _detection_param2(30)
{}


BPUApp::~BPUApp()
{
   close_current_gamemode();
}


int BPUApp::init()
{
   while (qApp->screens().size() < 1)
   {
      if (_err_msg("Veuillez brancher le projecteur.") == QMessageBox::Close)
         exit(0);
   }

   _main_gui.show();
   _main_gui.setScreen(qApp->screens()[0]);

   _projector_win.setParent(&_main_gui);
   _projector_win.show();

   _projector_win.setScreen(qApp->screens()[1]);
   _projector_win.showFullScreen();

   while (!_rgb_cam->openCamera())
   {
      if (_err_msg("La webcam est introuvable.") == QMessageBox::Close)
         exit(0);
   }

   // We miss a few images on purpose to let the webcam stabilize
   for (int i = 0; i < 30; i++)
      _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      if (_err_msg("Impossible d'obtenir l'image de la webcam.") == QMessageBox::Close)
         exit(0);
   }

   _frame_area = cv::selectROI(_rgb_cam->getFrame(), false, false);

   _window_size = _projector_win.size();
   _frame_size = _rgb_cam->getFrameSize();

   return 0;
}


void BPUApp::launch_gamemode(GameMode* gamemode)
{
   _game_mode = gamemode;
}


void BPUApp::close_current_gamemode()
{
   delete _game_mode;
   _game_mode = nullptr;
}


void BPUApp::update_glasses() 
{
   _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      if (_err_msg("Impossible d'obtenir l'image de la webcam.") == QMessageBox::Close)
         exit(0);
   }

   std::vector<QRectF> glasses_rect;
   DetectionTools::glasses(_rgb_cam->getFrame(), glasses_rect, _r_min, _r_max,
                           _dist_between_circles, _detection_param1, _detection_param2);

   std::vector<QRectF> new_circles;
   for (const QRectF& rect : glasses_rect)
   {
      auto id = _get_corresponding_id(rect);

      // If the circle doesn't match any of the old ones, we create a new id for it
      if (id == -1)
         id = ++_circles_id_count;
      
      _circles[id] = rect;
   }

   if (_game_mode)
   {
      _game_mode->update_logic(_circles);
      _game_mode->update_view();
      _projector_win.update_circles(_game_mode->get_glasses());
   }
}