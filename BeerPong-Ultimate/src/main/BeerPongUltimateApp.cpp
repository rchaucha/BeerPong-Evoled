#include "BeerPongUltimateApp.hpp"

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

QVector2D BeerPongUltimateApp::_frame2window(const QVector2D frame_coordinates) const
{
   float x = frame_coordinates.x() * (_window_size.height() / float(_frame_size.height()));
   float y = frame_coordinates.y() * (_window_size.width() / float(_frame_size.width()));

   return QVector2D(x, y);
}


int BeerPongUltimateApp::_err_msg(const QString& msg)
{
   return QMessageBox::critical( &_main_gui, "Error", msg,
                                 QMessageBox::Retry | QMessageBox::Close, QMessageBox::Retry);
}


unsigned long BeerPongUltimateApp::_get_corresponding_id(const QRectF& rect)
{
   std::map<float, unsigned long> dist2id;
   std::transform(std::execution::par_unseq, _circles.begin(), _circles.end(), dist2id.begin(),
      [](auto const& id2circle)
      {
         unsigned long ID = id2circle.first;
         QRectF* circle = &id2circle.second;

         return std::pair<float, unsigned long>(std::sqrt(pow(circle->x - rect.x, 2) + pow(circle->y - rect.y, 2)), ID);
      });

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


BeerPongUltimateApp::BeerPongUltimateApp(int& argc, char** argv) :
   QApplication(argc, argv),
   _rgb_cam(RGBCameraInput::getInstance())
{}


int BeerPongUltimateApp::init()
{
   _main_gui.show();
   _main_gui.windowHandle()->setScreen(qApp->screens()[0]);

   _projector_win.setParent(&_main_gui);
   _projector_win.show();
   _projector_win.windowHandle()->setScreen(qApp->screens()[1]);
   _projector_win.showFullScreen();

   while (!_rgb_cam->openCamera())
   {
      if (_err_msg("La webcam est introuvable.") == QMessageBox::Close)
         exit(0);
   }

   // on laisse passer quelques images pour que la camera se stabilise
   for (int i = 0; i < 30; i++)
      _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      if (_err_msg("Pas d'image reçue de la webcam.") == QMessageBox::Close)
         exit(0);
   }

   _frame_area = cv::selectROI(_rgb_cam->getFrame(), false, false);

   _window_size = _projector_win.size();
   _frame_size = _rgb_cam->getFrameSize();

   return 0;
}


void BeerPongUltimateApp::update_glasses() 
{
   _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      if (_err_msg("Pas d'image reçue de la webcam.") == QMessageBox::Close)
         exit(0);
   }

   std::vector<QRectF> glasses_rect;
   DetectionTools::glasses(_rgb_cam->getFrame(), glasses_rect, _r_min, _r_max,
                           _dist_between_circles, _detection_param1, _detection_param2);

   std::transform(std::execution::par_unseq, glasses_rect.begin(), glasses_rect.end(), glasses_circle.begin(),
      [](cv::Rect2d& glass)
      {
         // Construire la map en cherchant pour chaque cercle son correspondant dans _circles
      });
}