#pragma once

#include "GameMode.hpp"

class RandomGM : public GameMode
{
public:
   RandomGM() : GameMode() { srand(time(NULL)); }

   virtual void update_logic(std::map<unsigned long, QRectF>& circles) override;
   virtual void update_view() override;
};

