#include "BeerPongUltimateApp.hpp"

#include <iostream>
#include <QWindow>
#include "../Tools/DetectionTools.hpp"
#include "../Tools/RGBCameraInput.hpp"
#include "../GUI/ProjectorDisplay.hpp"
#include "../GUI/QtGUI.hpp"

QVector2D BeerPongUltimateApp::frame2Window(const QVector2D frame_coordinates) const
{
   float x = frame_coordinates.x() * (_window_size.height() / float(_frame_size.height()));
   float y = frame_coordinates.y() * (_window_size.width() / float(_frame_size.width()));

   return QVector2D(x, y);
}

BeerPongUltimateApp::BeerPongUltimateApp(int& argc, char** argv) :
   QApplication(argc, argv)
{
   QtGUI main_gui;
   main_gui.show();
   main_gui.windowHandle()->setScreen(qApp->screens()[0]);

   ProjectorDisplay projector_win(&main_gui);
   projector_win.show();
   projector_win.windowHandle()->setScreen(qApp->screens()[1]);
   projector_win.showFullScreen();

   _rgb_cam = RGBCameraInput::getInstance();

   if (!_rgb_cam->openCamera())
   {
      std::cerr << "La webcam est introuvable" << std::endl;
      return -1;
   }

   // on laisse passer quelques images pour que la camera se stabilise
   for (int i = 0; i < 30; i++)     
      _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      std::cerr << "Image vide" << std::endl;
      return -1;
   }

   _window_size = projector_win.size();
   _frame_size = _rgb_cam->getFrameSize();
}


void BeerPongUltimateApp::update_glasses() 
{
   _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      std::cerr << "Image vide" << std::endl;
      return -1;
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