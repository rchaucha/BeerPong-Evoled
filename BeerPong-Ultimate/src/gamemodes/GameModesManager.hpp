#pragma once

#include <vector>
#include <string>

#include "GameMode.hpp"


enum GameModesEnum { Random };


class GameModeManager
{
public:
   GameModeManager();
   
   GameMode* get_gamemode_from_string(GameModesEnum gamemode_name);

private:

};
