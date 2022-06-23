#pragma once

#include <QColor>
#include <QPointF>
#include <map>


typedef unsigned long GroupID;

class AGlass
{
public:
   virtual ~AGlass() {}

   virtual GroupID get_group_id() const noexcept = 0;

   inline QPointF get_position() const noexcept { return _position; }
   inline float get_radius() const noexcept { return _radius; }

   inline void set_position(QPointF position) noexcept { _position = position; }
   inline void set_radius(float radius) noexcept { _radius = radius; }

protected:
   AGlass(QPointF position, float radius) :
      _position(position), _radius(radius) {}

   AGlass(const AGlass& orig) = delete;

   GroupID new_group_id() noexcept { return _group_id_count++; }

private:
   static inline GroupID _group_id_count = 0;

   QPointF _position;
   float _radius;
};

