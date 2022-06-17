#pragma once

#include "GameMode.hpp"

class RandomGM : public GameMode
{
public:
   RandomGM() : GameMode() {}

   virtual void update_logic() override;
   virtual void update_view() override;
};

