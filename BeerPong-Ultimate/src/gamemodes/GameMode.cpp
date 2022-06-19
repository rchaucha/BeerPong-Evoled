#include "GameMode.hpp"

const std::vector<QColor> GameMode::_boynton_colors = {
      QColor(255, 255, 255),  //White
      QColor(0, 0, 255),      //Blue
      QColor(255, 0, 0),      //Red
      QColor(0, 255, 0),      //Green
      QColor(255, 255, 0),    //Yellow
      QColor(255, 0, 255),    //Magenta
      QColor(255, 128, 128),  //Pink
      QColor(128, 128, 128),  //Gray
      QColor(128, 0, 0),      //Brown
      QColor(255, 128, 0),    //Orange
};

std::vector<ColoredCircle> GameMode::get_glasses() const
{
   std::vector<ColoredCircle> glasses_vec;

   for (const auto& glass : _glasses)
   {
      QRectF rect(glass.second->get_position(), QSizeF(glass.second->get_radius(), glass.second->get_radius()));
      QColor glass_color = _group_color.at(glass.second->get_group_id());

      glasses_vec.push_back(ColoredCircle(rect, glass_color));
   }

   return glasses_vec;
}
