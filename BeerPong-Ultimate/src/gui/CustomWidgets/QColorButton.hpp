#pragma once

#include <QToolButton>
#include <QColor>
#include <QIcon>


class QColorButton : public QToolButton
{
   Q_OBJECT

public:
   QColorButton(QWidget* parent, QColor color, QIcon icon) : QToolButton(parent),
      _color(color)
   {
      setMinimumSize(QSize(22, 22));
      setIcon(icon);
      setCheckable(true);
   }

   QColor get_color() const { return _color; }

private:
   QColor _color;
};

