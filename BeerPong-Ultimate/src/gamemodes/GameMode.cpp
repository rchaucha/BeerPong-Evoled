#include "GameMode.hpp"


void GameMode::set_players(std::set<std::string>&& players)
{
   _players = move(players);

   for (const std::string& player : _players)
   {
      // TODO  
   }
}

void GameMode::set_points(std::set<int>&& points)
{
   // TODO  
}

std::vector<CircleInGroup> GameMode::get_glasses() const
{
   std::vector<CircleInGroup> glasses_vec;

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
