#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Glass
{
public:
   virtual ~Glass() {}

   virtual void removed_action() = 0;


protected:
   Glass(sf::Vector2f position, sf::Color color = sf::Color::White) :
      _position(position), _color(color) {};

   Glass(const Glass& orig) = delete;

   sf::Vector2f _position;
   sf::Color _color;
};

