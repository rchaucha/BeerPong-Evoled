#pragma once

#include <QToolButton>
#include <QColor>
#include <QIcon>


class QColorButton : public QToolButton
{
   Q_OBJECT

public:
   QColorButton(QWidget* parent, QColor color, QIcon icon) : QToolButton(parent),
      _color(color),
      _ID(_id_count++)
   {
      setMinimumSize(QSize(22, 22));
      setIcon(icon);
      setCheckable(true);
   }

   bool operator==(const QColorButton& b) { return _ID == b._ID; }

   QColor get_color() const { return _color; }

private:
   inline static unsigned long _id_count = 0;

   const unsigned long _ID;

   QColor _color;
};

