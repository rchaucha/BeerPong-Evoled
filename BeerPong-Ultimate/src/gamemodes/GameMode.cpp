#include "GameMode.hpp"

using namespace std;

void GameMode::set_players(set<string>&& players)
{
   _players = move(players);

   for (const string& player : _players)
   {
      // TODO  
   }
}

void GameMode::set_points(set<int>&& points)
{
   // TODO  
}

vector<CircleInGroup> GameMode::get_glasses() const
{
   vector<CircleInGroup> glasses_vec;

   for (const auto& glass : _glasses)
   {
      CircleInGroup circle_in_group;

      circle_in_group.rect = QRectF(glass.second->get_position(),
                                    QSizeF(glass.second->get_radius(), glass.second->get_radius()));
      circle_in_group.group_id = glass.second->get_group_id();

      glasses_vec.push_back(circle_in_group);
   }

   return glasses_vec;
}
