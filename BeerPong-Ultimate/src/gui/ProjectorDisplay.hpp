#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGUI.h"
#include <QPainter>
#include <QColor>
#include "ColoredCircle.h"

class ProjectorDisplay : public QMainWindow
{
   Q_OBJECT

public:
   ProjectorDisplay(QWidget* parent = Q_NULLPTR);

   void update_circles(std::vector<ColoredCircle>&& circles);

private:
   void paintEvent(QPaintEvent* event) override;

   std::vector<ColoredCircle> _circles;
};

