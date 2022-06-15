#pragma once

#include "Glass.hpp"
#include <string>

class OwnedGlass : public Glass
{
public:
   OwnedGlass(std::string owner, sf::Vector2f position, sf::Color color = sf::Color::White) :
      Glass(position, color), _owner(owner) {};

   inline std::string get_owner() const noexcept { return _owner; }

private:
   std::string _owner = "";
};

