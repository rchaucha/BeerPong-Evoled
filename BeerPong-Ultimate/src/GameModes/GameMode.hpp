#pragma once

#include <list>
#include <memory>

#include "../Glasses/Glass.hpp"

class GameMode
{
public:
   GameMode(sf::Vector2f position, sf::Color color = sf::Color::White) {};

   virtual void update_logic() = 0;
   virtual void update_view() = 0;
   virtual void get_circles() = 0;

private:
   std::list<std::shared_ptr<Glass>> _glasses;
};
