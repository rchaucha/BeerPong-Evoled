#pragma once

#include "Glass.hpp"
#include <string>
#include <map>

class OwnedGlass : public Glass
{
public:
   OwnedGlass(std::string owner, QPointF position, float radius) :
      Glass(position, radius), _owner(owner) {};

   inline std::string get_owner() const noexcept { return _owner; }
   inline void set_owner(const std::string& new_owner) noexcept { _owner = new_owner; }

private:
   static std::map<std::string, QColor> _player2color;

   std::string _owner = "";
};

