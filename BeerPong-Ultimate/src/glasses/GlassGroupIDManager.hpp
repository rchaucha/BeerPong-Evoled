#pragma once

#include <map>
#include <string>
#include <mutex>


typedef unsigned long GroupID;
typedef int Points;
typedef std::string Player;


/* Singleton */
class GlassGroupIDManager
{
public:
   static GlassGroupIDManager* get_instance();

   GlassGroupIDManager(GlassGroupIDManager& other) = delete;
   void operator=(const GlassGroupIDManager& other) = delete;

   bool do_attr_exist(const Player& player) { return _player_to_ID.count(player) > 0; }
   bool do_attr_exist(const Points& points) { return _points_to_ID.count(points) > 0; }

   GroupID get_group_id(const Player& player) { return _get_or_set_group_id<Player>(player, _player_to_ID); }
   GroupID get_group_id(const Points& points) { return _get_or_set_group_id<Points>(points, _points_to_ID); }

private:
   inline static GlassGroupIDManager* _instance = nullptr;
   inline static std::mutex _mutex;

   GlassGroupIDManager() {}
   ~GlassGroupIDManager() {}

   // If attr doesn't exist, create new group id and returns it. Otherwise, returns the existing.
   template <class T_attr>
   GroupID _get_or_set_group_id(const T_attr& attr, std::map<T_attr, GroupID>& map)
   {
      if (map.count(attr) == 0)
         map[attr] = _new_group_id();

      return map.at(attr);
   }

   GroupID _new_group_id() noexcept { return _group_id_count++; }

   GroupID _group_id_count = 0;

   std::map<Player, GroupID> _player_to_ID;
   std::map<Points, GroupID> _points_to_ID;
};
