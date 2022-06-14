#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../tools/RGBCameraInput.hpp"

int main()
{
   RGBCameraInput* rbg_cam = RGBCameraInput::getInstance();

   if (!rbg_cam->openCamera())
   {
      std::cerr << "La webcam est introuvable" << std::endl;
      return -1;
   }

   sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Interactive table", sf::Style::Fullscreen);

   return 0;
}