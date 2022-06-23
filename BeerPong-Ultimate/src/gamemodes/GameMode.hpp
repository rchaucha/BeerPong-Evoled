#pragma once

#include <memory>
#include <map>
#include <algorithm>
#include <set>
#include <QRectF>

#include "../glasses/AGlass.hpp"


typedef unsigned long GlassID;

struct CircleInGroup
{
   unsigned long group_id = 0;
   QRectF rect;
};


class GameMode
{
public:
   virtual void update_logic(std::map<GlassID, QRectF>& circles) = 0;
   virtual void update_view() = 0;

   virtual bool are_players_used() = 0;
   virtual bool are_points_glasses_used() = 0;

   void set_players(std::set<std::string>&& players);
   void set_points(std::set<int>&& points);

   std::vector<CircleInGroup> get_glasses() const;

protected:
   GameMode() = default; 

   virtual void _assign_new_glasses() = 0;

   std::map<GlassID, std::unique_ptr<AGlass>> _glasses;
   std::set<std::string> _players;
   std::set<int> _points;
};
