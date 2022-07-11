#include "QPointsListLine.hpp"


QPointsListLine::QPointsListLine(QWidget* parent, Points points, const QPixmap& color_icon) :
   QListLine(parent, color_icon)
{
   _points_nb = new QSpinBox((QWidget*)this);
   _points_nb->setObjectName(_name_with_id("_points_nb"));
   _points_nb->setFont(*_default_font);
   _points_nb->setMinimum(-100);
   _points_nb->setMaximum(100);

   _layout->insertWidget(1, _points_nb);
}