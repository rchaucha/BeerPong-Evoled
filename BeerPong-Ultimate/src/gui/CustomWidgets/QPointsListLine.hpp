#pragma once

#include "QListLine.hpp"

#include <QSpinBox>


class QPointsListLine : public QListLine
{
public:
   QPointsListLine(QWidget* parent, Points points, const QPixmap& color_icon);

   Points get_points() { return _points_nb->value(); }

private:
   QSpinBox* _points_nb;
};

