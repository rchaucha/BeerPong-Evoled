#include "RandomGM.hpp"

#include "../Glasses/OwnedGlass.hpp"


RandomGM::RandomGM() 
{
   std::random_device rd; // Used to get initial value of random sequence
   _random_engine = std::make_unique<std::mt19937>(rd()); // The random sequence generator, initialised using the rd
}


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
         std::uniform_int_distribution<int> distribution(0, _players.size()-1);
         const int i = distribution(*_random_engine);
         auto player_it = _players.begin();
         std::advance(player_it, i);

         _glasses[id] = std::make_unique<OwnedGlass>(pos, radius, *player_it);
      }
   }
}


void RandomGM::update_view()
{
}