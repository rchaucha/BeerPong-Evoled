#include "RandomGM.hpp"

#include <stdlib.h>
#include <time.h>
#include "../glasses/Glass.hpp"

void RandomGM::update_logic(std::map<unsigned long, QRectF>& circles)
{
   for (const auto& [id, rect] : circles)
   {
      QPointF pos = QPointF(rect.x(), rect.y());
      float radius = rect.width();

      if (_glasses.count(id) > 0)
      {
         _glasses[id].set_position(pos);
         _glasses[id].set_radius(radius);
      }
      else
      {
         int i = rand() % _boynton_colors.size();
         _glasses[id] = OwnedGlass(, pos, radius, _boynton_colors[i]);
      }
   }
}

void RandomGM::update_view()
{
}
