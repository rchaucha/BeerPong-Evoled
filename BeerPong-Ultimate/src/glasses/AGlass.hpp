#pragma once

#include <QColor>
#include <QPointF>
#include <map>


class AGlass
{
public:
   virtual ~AGlass() {}

   inline QPointF get_position() const noexcept { return _position; }
   inline float get_radius() const noexcept { return _radius; }

   inline void set_position(QPointF position) noexcept { _position = position; }
   inline void set_radius(float radius) noexcept { _radius = radius; }

protected:
   AGlass(QPointF position, float radius) :
      _position(position), _radius(radius) {}

   AGlass(const AGlass& orig) = delete;

   unsigned long new_group_id() noexcept { return _goup_id_count++; }

private:
   static unsigned long _goup_id_count;

   QPointF _position;
   float _radius;
};

