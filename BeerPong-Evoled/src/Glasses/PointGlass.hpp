#pragma once

#include "Glass.hpp"

class PointGlass : public Glass
{
public:
   PointGlass(int points, sf::Vector2f position, sf::Color color = sf::Color::White) :
      Glass(position, color), _points(points) {};

   inline int get_points() const noexcept { return _points; }

private:
   int _points = 0;
};

