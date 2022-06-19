#pragma once

#include "AValueGlass.hpp"

class PointGlass : public AValueGlass<int>
{
public:
   PointGlass(QPointF position, float radius, int points) :
      AValueGlass<int>(position, radius, points) {};

   inline int get_points() const noexcept { return _get_value(); }
   inline int set_points(int points) noexcept { _set_value(points); }
};

