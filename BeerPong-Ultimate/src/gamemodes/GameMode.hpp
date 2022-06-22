#pragma once

#include <memory>
#include <map>
#include <algorithm>
#include <set>

#include "../glasses/AGlass.hpp"
#include "../gui/ColoredCircle.hpp"

class GameMode
{
public:
   virtual void update_logic(std::map<unsigned long, QRectF>& circles) = 0;
   virtual void update_view() = 0;

   virtual bool are_players_used() = 0;
   virtual bool are_points_glasses_used() = 0;


   void add_player(std::string new_player) { _players.insert(new_player); }
   bool remove_player(std::string player) { return _players.erase(player); }

   std::vector<ColoredCircle> get_glasses() const;

protected:
   GameMode(std::set<std::string>&& players) : _players(std::move(players)) {};
   GameMode(std::set<int>&& points) : _points(std::move(points)) {};
   GameMode(std::set<std::string>&& players, std::set<int>&& points) : _points(std::move(points)) {};

   virtual void _assign_new_glasses() = 0;

   std::map<unsigned long, std::unique_ptr<AGlass>> _glasses;
   std::set<std::string> _players;
   std::set<int> _points;

private: 
   // The GameMode doesn't need to know about the color management
   
   //https://stackoverflow.com/questions/470690/how-to-automatically-generate-n-distinct-colors
   static const std::vector<QColor> _boynton_colors;

   std::map<unsigned long, QColor> _group_color;
};
