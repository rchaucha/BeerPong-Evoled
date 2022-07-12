#include "GameModesManager.hpp"

#include "RandomGM.hpp"


std::unique_ptr<GameMode> GameModesManager::create_new_gamemode(std::string gamemode_name, std::set<Player>&& players, std::set<Points>&& points)
{
   std::unique_ptr<GameMode> gamemode(nullptr);
   if (gamemode_name == "Random")
      gamemode = std::make_unique<RandomGM>();

   if (gamemode)
   {
      gamemode->set_players(std::move(players));
      gamemode->set_points(std::move(points));
   }
   
   return gamemode;
}

std::string GameModesManager::get_description(std::string gamemode_name)
{
   if (gamemode_name == "Random")
      return "Les verres sont attribués de manière aléatoire de manière équitable.";

   return "";
}
