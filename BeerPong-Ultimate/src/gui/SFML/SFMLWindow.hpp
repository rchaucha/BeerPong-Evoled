#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class SFMLWindow : public sf::RenderWindow
{
public :
   SFMLWindow(sf::VideoMode mode, const sf::String& title) : sf::RenderWindow(mode, title, sf::Style::Fullscreen)
   {}

   void update(const std::vector<sf::CircleShape>& cicles);
};

