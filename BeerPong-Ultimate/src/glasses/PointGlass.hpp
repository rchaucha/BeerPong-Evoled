#pragma once

#include "Glass.hpp"

class PointGlass : public Glass
{
public:
   PointGlass(int points, QPointF position, float radius) :
      Glass(position, radius), _points(points) {};

   inline int get_points() const noexcept { return _points; }

private:
   int _points = 0;
};

