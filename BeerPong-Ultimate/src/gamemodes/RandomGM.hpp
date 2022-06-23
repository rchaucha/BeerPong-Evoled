#pragma once

#include "GameMode.hpp"

class RandomGM : public GameMode
{
public:
   RandomGM(std::set<std::string>&& players) : GameMode(std::move(players)) 
   { srand(time(NULL)); }

   virtual void update_logic(std::map<unsigned long, QRectF>& circles) override;
   virtual void update_view() override;

   virtual bool are_players_used() { return true; }
   virtual bool are_points_glasses_used()  return false; }

   
};

