#include "BeerPongUltimateApp.hpp"

#include <iostream>
#include "../Tools/DetectionTools.hpp"
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
}


void BeerPongUltimateApp::update_glasses() 
{
   _rgb_cam->updateFrame();

   if (_rgb_cam->isFrameEmpty())
   {
      std::cerr << "Image vide" << std::endl;
      return -1;
   }

   std::vector<QRectF> glasses_rect = DetectionTools::glasses(_rgb_cam->getFrame());

   std::transform(std::execution::par_unseq, glasses_rect.begin(), glasses_rect.end(), glasses_circle.begin(),
      [](cv::Rect2d& glass)
      {
         // Construire la map en cherchant pour chaque cercle son correspondant dans _circles
      });
   
   
}