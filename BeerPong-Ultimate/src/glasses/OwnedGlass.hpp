#pragma once

#include <string>
#include <map>

#include "AValueGlass.hpp"


class OwnedGlass : public AValueGlass<Player>
{
public:
   OwnedGlass(QPointF position, float radius, Player owner) :
      AValueGlass<Player>(position, radius, owner) {};

   virtual GroupID get_group_id() const noexcept { return _group_id_manager->get_group_id(get_owner()); }

   inline Player get_owner() const noexcept { return _get_value(); }
   void set_owner(const Player& new_owner) noexcept { _set_value(new_owner); }
};

