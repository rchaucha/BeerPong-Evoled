#pragma once

#include "AGlass.hpp"


template <class T_value>
class AValueGlass : public AGlass
{
public:

   virtual unsigned long get_group_id() const noexcept { return _value2group_id[_glass_value]; }

protected:
   AValueGlass(QPointF position, float radius, const T_value& value):
      AGlass(position, radius) 
   { _set_value(value); }

   inline T_value _get_value() const noexcept { return _glass_value; }

   void _set_value(const T_value& new_value) noexcept 
   {
      if (_value2group_id.count(new_value) == 0)
         _value2group_id[new_value] = new_group_id();

      _glass_value = new_value;
   }

private:
   // Can be a number of points, an owner,...
   T_value _glass_value;

   static inline std::map<T_value, unsigned long> _value2group_id;
};
