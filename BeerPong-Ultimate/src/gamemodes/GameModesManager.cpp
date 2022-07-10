#include "GameModesManager.hpp"

#include "RandomGM.hpp"

using namespace std;


GameMode* GameModesManager::create_new_gamemode(std::string gamemode_name, std::set<Player>&& players, std::set<Points>&& points)
{
   GameMode* gamemode;
   if (gamemode_name == "Random")
      gamemode = new RandomGM;

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
}
