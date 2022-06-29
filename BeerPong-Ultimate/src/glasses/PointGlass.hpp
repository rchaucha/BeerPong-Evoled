#pragma once

#include "AValueGlass.hpp"

class PointGlass : public AValueGlass<Points>
{
public:
   PointGlass(QPointF position, float radius, int points) :
      AValueGlass<Points>(position, radius, points) {};

   virtual GroupID get_group_id() const noexcept { return _group_id_manager->get_group_id(get_points()); }

   inline Points get_points() const noexcept { return _get_value(); }
   inline Points set_points(Points points) noexcept { _set_value(points); }
};

