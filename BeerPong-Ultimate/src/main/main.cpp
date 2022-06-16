#include <iostream>
#include <execution>

#include <SFML/Window/Event.hpp>
#include <opencv2/highgui.hpp>
#include <QtWidgets/QApplication>

#include "../GUI/Qt/QtGUI.hpp"
#include "../Tools/RGBCameraInput.hpp"
#include "../Tools/RGBCameraInput.hpp"
#include "../Tools/DetectionTools.hpp"
#include "../GUI/SFML/SFMLWindow.hpp"


sf::Vector2u window_size, frame_size;

sf::Vector2f frame2Window(const sf::Vector2f frame_coordinates)
{
   float x = frame_coordinates.x * (window_size.x / float(frame_size.x));
   float y = frame_coordinates.y * (window_size.y / float(frame_size.y));
   return sf::Vector2f(x, y);
}


int main(int argc, char* argv[])
{
   // Camera
   RGBCameraInput* rgb_cam = RGBCameraInput::getInstance();

   if (!rgb_cam->openCamera())
   {
      std::cerr << "La webcam est introuvable" << std::endl;
      return -1;
   }

   for (int i = 0; i < 30; i++)     // on laisse passer quelques images pour que la camera se stabilise
      rgb_cam->updateFrame();

   if (rgb_cam->isFrameEmpty())
   {
      std::cerr << "Image vide" << std::endl;
      return -1;
   }

   // Qt
   QApplication qt_application(argc, argv);
   QtGUI w;
   w.show();

   // SFML
   SFMLWindow
   sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Interactive table", sf::Style::Fullscreen);

   window_size = window.getSize();
   frame_size = rgb_cam->getFrameSize();
   
   cv::Rect2d projected_area = cv::selectROI(rgb_cam->getFrame(), true, true);

   while (window.isOpen())
   {
      rgb_cam->updateFrame();

      if (rgb_cam->isFrameEmpty())
      {
         std::cerr << "Image vide" << std::endl;
         return -1;
      }

      window.clear(sf::Color::Black);
      window.display();

      sf::Event event;
      while (window.pollEvent(event))
      {
         // "Enter" -> new detection
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
         {
            std::vector<cv::Rect2d> glasses_rect = DetectionTools::glasses(rgb_cam->getFrame());
            std::vector<sf::CircleShape> glasses_circle;
            glasses_circle.resize(glasses_rect.size());

            std::transform(std::execution::par_unseq, glasses_rect.begin(), glasses_rect.end(), glasses_circle.begin(),
               [](cv::Rect2d& glass)
               {
                  sf::CircleShape circle(glass.height / 2.0);
                  circle.setFillColor(sf::Color::Red);
                  circle.setPosition(frame2Window(sf::Vector2f(glass.x, glass.y)));
                  return circle;
               });
         }
         // "Echap" -> exit
         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            exit(0);
      }
   }

   return 0;
}