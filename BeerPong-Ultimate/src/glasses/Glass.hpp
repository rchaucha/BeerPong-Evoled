#pragma once

#include <QColor>
#include <QPointF>

class Glass
{
public:
   virtual ~Glass() {}

   inline QPointF get_position() const noexcept { return _position; }
   inline float get_radius() const noexcept { return _radius; }

   inline void set_position(QPointF position) noexcept { _position = position; }
   inline void set_radius(float radius) noexcept { _radius = radius; }

protected:
   Glass(QPointF position, float radius) :
      _position(position), _radius(radius) {};

   Glass(const Glass& orig) = delete;

private:
   QPointF _position;
   float _radius;
};

