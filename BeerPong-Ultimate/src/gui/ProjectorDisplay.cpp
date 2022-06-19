#include "ProjectorDisplay.hpp"


ProjectorDisplay::ProjectorDisplay(QWidget* parent) : 
   QMainWindow(parent)
{
   this->setStyleSheet("background-color: black;");
}


void ProjectorDisplay::update_circles(std::vector<ColoredCircle>&& circles)
{
   _circles = std::move(circles);

   update();
}


void ProjectorDisplay::paintEvent(QPaintEvent* event)
{
   QPainter painter(this);

   for (const ColoredCircle& circle : _circles)
   {
      painter.setBrush(circle.get_color());
      painter.drawEllipse(circle.get_rect());
   }
}
