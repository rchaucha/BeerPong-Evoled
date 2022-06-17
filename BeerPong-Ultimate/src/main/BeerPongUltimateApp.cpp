#include "BeerPongUltimateApp.hpp"

#include <iostream>
#include "../Tools/RGBCameraInput.hpp"

QVector2D BeerPongUltimateApp::frame2Window(const QVector2D frame_coordinates) const
{
   float x = frame_coordinates.x() * (_window_size.height() / float(_frame_size.height()));
   float y = frame_coordinates.y() * (_window_size.width() / float(_frame_size.width()));

   return QVector2D(x, y);
}

BeerPongUltimateApp::BeerPongUltimateApp(int& argc, char** argv) :
   QApplication(argc, argv)
{
   // Camera
   _rgb_cam = RGBCameraInput::getInstance();

   if (!_rgb_cam->openCamera())
   {
      std::cerr << "La webcam est introuvable" << std::endl;
      return -1;
   }

   for (int i = 0; i < 30; i++)     // on laisse passer quelques images pour que la camera se stabilise
      _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      std::cerr << "Image vide" << std::endl;
      return -1;
   }
}