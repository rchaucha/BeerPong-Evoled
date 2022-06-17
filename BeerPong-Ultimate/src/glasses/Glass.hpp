#pragma once

#include <QColor>
#include <QVector2D>

class Glass
{
public:
   virtual ~Glass() {}

   inline QVector2D get_position() const noexcept { return _position; }
   inline QColor  get_color() const noexcept { return _color; }

protected:
   Glass(QVector2D position, QColor color = Qt::white) :
      _position(position), _color(color) {};

   Glass(const Glass& orig) = delete;

private:
   QVector2D _position;
   QColor  _color;
};

