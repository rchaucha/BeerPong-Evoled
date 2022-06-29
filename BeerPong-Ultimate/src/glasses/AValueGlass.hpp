#pragma once

#include <memory>
#include "AGlass.hpp"


template <class T_value>
class AValueGlass : public AGlass
{
protected:
   AValueGlass(QPointF position, float radius, const T_value& value):
      AGlass(position, radius),
      _group_id_manager(std::make_unique<GlassGroupIDManager>())
   { _set_value(value); }

   inline T_value _get_value() const noexcept { return _glass_value; }

   void _set_value(const T_value& new_value) noexcept { _glass_value = new_value; }

   std::unique_ptr<GlassGroupIDManager> _group_id_manager;

private:
   // Can be a number of points, an owner,...
   T_value _glass_value;
};
