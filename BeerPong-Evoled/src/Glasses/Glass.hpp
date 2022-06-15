#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Glass
{
public:
   virtual ~Glass() {}

   inline sf::Vector2f get_position() const noexcept { return _position; }
   inline sf::Color get_color() const noexcept { return _color; }

protected:
   Glass(sf::Vector2f position, sf::Color color = sf::Color::White) :
      _position(position), _color(color) {};

   Glass(const Glass& orig) = delete;

private:
   sf::Vector2f _position;
   sf::Color _color;
};

