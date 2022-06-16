#include "SFMLWindow.hpp"

void SFMLWindow::update(const std::vector<sf::CircleShape>& cicles)
{
   clear(sf::Color::Black);

   for (const auto& circle : cicles)
      draw(circle);

   display();
}
