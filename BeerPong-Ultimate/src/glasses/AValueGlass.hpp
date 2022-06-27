#pragma once

#include "AGlass.hpp"


template <class T_value>
class AValueGlass : public AGlass
{
public:
   virtual GroupID get_group_id() const noexcept { return _group_id_manager->get_group_id(_glass_value); }

protected:
   AValueGlass(QPointF position, float radius, const T_value& value):
      AGlass(position, radius),
      _group_id_manager(GlassGroupIDManager::get_instance())
   { _set_value(value); }

   inline T_value _get_value() const noexcept { return _glass_value; }

   void _set_value(const T_value& new_value) noexcept { _glass_value = new_value; }

private:
   // Can be a number of points, an owner,...
   T_value _glass_value;

   GlassGroupIDManager _group_id_manager;
};
