#pragma once

#include <QColor>
#include <QRectF>

class ColoredCircle {
public:
   ColoredCircle(QRectF rect, QColor color) : _rect(rect), _color(color) {}

   inline QRectF get_rect() const noexcept { return _rect; }
   inline QColor get_color() const noexcept { return _color; }

private:
   QRectF _rect;
   QColor _color;
};