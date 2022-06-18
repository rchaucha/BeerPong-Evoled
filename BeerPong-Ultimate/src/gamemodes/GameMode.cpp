#include "GameMode.hpp"

std::vector<const ColoredCircle> GameMode::get_glasses() const
{
   std::vector<const ColoredCircle> glasses_vec;

   for (const auto& glass : _glasses)
   {
      QRectF rect(glass.second.get_position(), QSizeF(glass.second.get_radius(), glass.second.get_radius()));
      glasses_vec.push_back(ColoredCircle(rect, glass.second.get_color()));
   }

   return glasses_vec;
}
