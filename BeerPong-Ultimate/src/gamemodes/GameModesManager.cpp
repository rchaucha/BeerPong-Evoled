#include "GameModesManager.hpp"

#include "RandomGM.hpp"


GameModesManager::GameModesManager()
{
   _gamemode_instances[GameModesEnum::Random] = std::unique_ptr<GameMode>(new RandomGM());
}


std::unique_ptr<GameMode> GameModesManager::get_gamemode(GameModesEnum gamemode_name, std::set<Player>&& players, std::set<Points>&& points)
{
   _assert_gamemode_added(gamemode_name);

   std::unique_ptr<GameMode> gamemode = std::unique_ptr<GameMode>(new RandomGM());

   if (gamemode)
   {
      gamemode->set_players(std::move(players));
      gamemode->set_points(std::move(points));
   }
   
   return gamemode;
}


std::string GameModesManager::get_name(GameModesEnum gamemode_name)
{
   _assert_gamemode_added(gamemode_name);

   return _gamemode_instances[gamemode_name]->get_name();
}


std::string GameModesManager::get_description(GameModesEnum gamemode_name)
{
   _assert_gamemode_added(gamemode_name);

   return _gamemode_instances[gamemode_name]->get_description();
}


std::vector<GameModesManager::GameModesEnum> GameModesManager::get_gamemodes() const
{
   std::vector<GameModesEnum> gamemodes;

   for (int i = GameModesEnum::FIRST + 1; i < GameModesEnum::LAST; i++)
      gamemodes.push_back(static_cast<GameModesEnum>(i));

   return gamemodes;
}
