#pragma once

#include <QColor>
#include <QPointF>

class Glass
{
public:
   virtual ~Glass() {}

   inline QPointF get_position() const noexcept { return _position; }
   inline float get_radius() const noexcept { return _radius; }
   inline QColor get_color() const noexcept { return _color; }

protected:
   Glass(QPointF position, float radius, QColor color = Qt::white) :
      _position(position), _radius(radius), _color(color) {};

   Glass(const Glass& orig) = delete;

private:
   QPointF _position;
   float _radius;
   QColor  _color;
};

