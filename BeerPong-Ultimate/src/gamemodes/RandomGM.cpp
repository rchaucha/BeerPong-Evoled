#include "RandomGM.hpp"

#include <stdlib.h>
#include <time.h>
#include "../Glasses/OwnedGlass.hpp"


void RandomGM::update_logic(std::map<GlassID, QRectF>& circles)
{
   for (const auto& [id, rect] : circles)
   {
      QPointF pos = QPointF(rect.x(), rect.y());
      float radius = rect.width();

      // If the glass is recognized, we update its properties
      if (_glasses.count(id) > 0)
      {
         _glasses[id]->set_position(pos);
         _glasses[id]->set_radius(radius);
      }
      else
      {
         int i = rand() % _players.size();
         auto player_it = _players.begin();
         std::advance(player_it, i);

         _glasses[id] = std::make_unique<OwnedGlass>(pos, radius, *player_it);
      }
   }
}

void RandomGM::update_view()
{
}
