#pragma once

#include <list>
#include <memory>

#include "../Glasses/Glass.hpp"

class GameMode
{
public:
   virtual void update_logic(std::map<unsigned long, QRectF> &circles) = 0;
   virtual void update_view() = 0;

protected:
   GameMode() {};

   std::map<unsigned long, Glass> _glasses;
};
