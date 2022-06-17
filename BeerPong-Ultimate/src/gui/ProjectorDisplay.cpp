#include "ProjectorDisplay.hpp"


void ProjectorDisplay::update_circles(const std::vector<ColoredCircle>& circles)
{
   _circles = circles;

   update();
}


void ProjectorDisplay::paintEvent(QPaintEvent* event)
{
   QPainter painter(this);

   for (const ColoredCircle& circle : _circles)
   {
      painter.setBrush(circle.color);
      painter.drawEllipse(circle.rect);
   }
}
