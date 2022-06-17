#pragma once

#include <list>
#include <memory>

#include "../Glasses/Glass.hpp"

class GameMode
{
public:
   virtual void update_logic() = 0;
   virtual void update_view() = 0;

protected:
   GameMode() {};

   std::list<std::shared_ptr<Glass>> _glasses;
};
