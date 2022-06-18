#pragma once

#include "Glass.hpp"
#include <string>

class OwnedGlass : public Glass
{
public:
   OwnedGlass(std::string owner, QPointF position, float radius, QColor color = Qt::white) :
      Glass(position, radius, color), _owner(owner) {};

   inline std::string get_owner() const noexcept { return _owner; }

private:
   std::string _owner = "";
};

