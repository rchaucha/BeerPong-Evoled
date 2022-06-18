#pragma once

#include <list>
#include <memory>
#include <map>
#include <algorithm>

#include "../Glasses/Glass.hpp"
#include "../gui/ColoredCircle.h"

class GameMode
{
public:
   virtual void update_logic(std::map<unsigned long, QRectF>& old_circles) = 0;
   virtual void update_view() = 0;

   std::vector<const ColoredCircle> get_glasses() const;

protected:
   GameMode() {};

   std::map<unsigned long, Glass> _glasses;
};
