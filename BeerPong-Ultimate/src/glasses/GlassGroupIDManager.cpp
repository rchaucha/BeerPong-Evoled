#include "GlassGroupIDManager.hpp"


GlassGroupIDManager* GlassGroupIDManager::get_instance()
{
   std::lock_guard<std::mutex> lock(_mutex);
   if (_instance == nullptr)
   {
      _instance = new GlassGroupIDManager();
   }

   return _instance;
}

