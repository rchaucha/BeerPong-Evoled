#pragma once

#include "AValueGlass.hpp"
#include <string>
#include <map>

class OwnedGlass : public AValueGlass<std::string>
{
public:
   OwnedGlass(QPointF position, float radius, std::string owner) :
      AValueGlass<std::string>(position, radius, owner) {};

   inline std::string get_owner() const noexcept { return _get_value(); }
   void set_owner(const std::string& new_owner) noexcept { _set_value(points); }
};

