#pragma once

#include <vector>
#include <set>
#include <string>
#include <memory>

#include "../glasses/GlassGroupIDManager.hpp"
#include "RandomGM.hpp"

class GameMode;

class GameModesManager
{
public:   
   GameModesManager();

   enum GameModesEnum { FIRST, Random, LAST};

   std::unique_ptr<GameMode> get_gamemode(GameModesEnum gamemode, std::set<Player>&& players, std::set<Points>&& points);

   std::string get_name(GameModesEnum gamemode_name);
   std::string get_description(GameModesEnum gamemode_name);

   std::vector<GameModesEnum> get_gamemodes() const;
   GameModesEnum get_gamemode(int ind) const { return static_cast<GameModesEnum>(ind + 1); } // Add one to skip "FIRST" 

private:
   std::map<GameModesEnum, std::unique_ptr<GameMode>> _gamemode_instances;

   void _assert_gamemode_added(GameModesEnum gamemode_name) const {
      assert(_gamemode_instances.find(gamemode_name) != _gamemode_instances.end() 
         && "Gamemode not added in the map.");
   }
};
