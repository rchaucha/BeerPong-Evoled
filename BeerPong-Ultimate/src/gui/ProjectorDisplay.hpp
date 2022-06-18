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
   ProjectorDisplay(QWidget* parent = Q_NULLPTR) : QMainWindow(parent)
   {
      this->setStyleSheet("background-color: black;");
   }

   void update_circles(const std::vector<const ColoredCircle>& circles);

private:
   void paintEvent(QPaintEvent* event) override;

   std::vector<ColoredCircle> _circles;
};

