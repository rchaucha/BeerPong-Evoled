#include "GameModeManager.hpp"

#include "RandomGM.hpp"


using namespace std;

GameMode* GameModeManager::create_new_gamemode(GameModesEnum gamemode_name, std::set<Player>&& players, std::set<Points>&& points)
{
   GameMode* gamemode;
   switch (gamemode_name) 
   {
   case Random:
      gamemode = new RandomGM();
   }

   gamemode->set_players(std::move(players));
   gamemode->set_points(std::move(points));
   
   return gamemode;
}
