#pragma once

#include "GameMode.hpp"

#include <random>
#include <memory>


class RandomGM : public GameMode
{
public:
   RandomGM();

   virtual std::string get_name() override { return "Random"; };
   virtual std::string get_description() override 
   { return "Les verres sont attribués aléatoirement de manière équitable."; };

   virtual void update_logic(std::map<GlassID, QRectF>& circles) override;
   virtual void update_view() override;

   virtual bool are_players_used() { return true; }
   virtual bool are_points_glasses_used() { return false; }

private:
   RandomGM(const RandomGM&) = delete;

   std::unique_ptr<std::mt19937> _random_engine;
};

