#pragma once

#include "Glass.hpp"

class PointGlass : public Glass
{
public:
   PointGlass(int points, QPointF position, float radius, QColor color = Qt::white) :
      Glass(position, radius, color), _points(points) {};

   inline int get_points() const noexcept { return _points; }

private:
   int _points = 0;
};

