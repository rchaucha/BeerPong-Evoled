#include "GameMode.hpp"


std::vector<CircleInGroup> GameMode::get_glasses() const
{
   std::vector<CircleInGroup> glasses_vec;

   for (const auto& glass : _glasses)
   {
      QRectF rect(glass.second->get_position(), QSizeF(glass.second->get_radius(), glass.second->get_radius()));
      unsigned long group_id = glass.second->get_group_id();

      glasses_vec.push_back(CircleInGroup(group_id, rect));
   }

   return glasses_vec;
}
