#pragma once

#include "GameMode.hpp"

#include <random>
#include <memory>


class RandomGM : public GameMode
{
public:
   RandomGM();

   virtual void update_logic(std::map<GlassID, QRectF>& circles) override;
   virtual void update_view() override;

   virtual bool are_players_used() { return true; }
   virtual bool are_points_glasses_used() { return false; }

private:
   std::unique_ptr<std::mt19937> _random_engine;
};

