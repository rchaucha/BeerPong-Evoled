#pragma once

#include <string>
#include <map>

#include "AValueGlass.hpp"

class OwnedGlass : public AValueGlass<std::string>
{
public:
   OwnedGlass(QPointF position, float radius, std::string owner) :
      AValueGlass<std::string>(position, radius, owner) {};

   inline std::string get_owner() const noexcept { return _get_value(); }
   void set_owner(const std::string& new_owner) noexcept { _set_value(new_owner); }
};

