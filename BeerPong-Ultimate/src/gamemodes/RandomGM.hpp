#pragma once

#include "GameMode.hpp"

class RandomGM : public GameMode
{
public:
   RandomGM() : GameMode() {}

   virtual void update_logic(std::map<unsigned long, QRectF>& old_circles) override;
   virtual void update_view() override;
};

