#include "AValueGlass.hpp"


template <class T_value>
AValueGlass<T_value>::AValueGlass(QPointF position, float radius, T_value value) :
   AGlass(position, radius)
{ 
   _set_value(value);
}


template <class T_value>
inline void AValueGlass<T_value>::_set_value(const T_value& new_value) noexcept
{
   if (_value2group_id.count(new_value) == 0)
      _value2group_id[new_value] = new_group_id();

   _glass_value = new_value;
}