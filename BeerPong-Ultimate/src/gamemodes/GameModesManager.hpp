#pragma once

#include <vector>
#include <set>
#include <string>

#include "../glasses/GlassGroupIDManager.hpp"

class GameMode;

class GameModesManager
{
public:   
   static GameMode* create_new_gamemode(std::string gamemode_name, std::set<Player>&& players, std::set<Points>&& points);

   static std::string get_description(std::string gamemode_name);

private:
   inline static std::vector<std::string> _gamemodes_names = { "Random" };
};
