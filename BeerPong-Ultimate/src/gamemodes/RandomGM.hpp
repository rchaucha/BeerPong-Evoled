#pragma once

#include "GameMode.hpp"

class RandomGM : public GameMode
{
public:
   RandomGM(std::set<std::string>&& players) : GameMode(std::move(players)) 
   { srand(time(NULL)); }

   virtual void update_logic(std::map<unsigned long, QRectF>& circles) override;
   virtual void update_view() override;
};

