#pragma once

#include <memory>
#include <map>
#include <algorithm>
#include <set>

#include "../Glasses/Glass.hpp"
#include "../gui/ColoredCircle.h"

class GameMode
{
public:
   virtual void update_logic(std::map<unsigned long, QRectF>& circles) = 0;
   virtual void update_view() = 0;

   void add_player(std::string new_player) { _players.insert(new_player); }
   bool remove_player(std::string player) { return _players.erase(player); }

   std::vector<const ColoredCircle> get_glasses() const;

protected:
   GameMode() {};

   virtual void _assign_new_glasses() = 0;

   //https://stackoverflow.com/questions/470690/how-to-automatically-generate-n-distinct-colors
   static const std::vector<QColor> _boynton_colors;

   std::map<unsigned long, Glass> _glasses;
   std::set<std::string> _players;
};
