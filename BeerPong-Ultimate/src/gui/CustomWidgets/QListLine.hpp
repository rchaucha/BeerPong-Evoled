#pragma once

#include <memory>
#include <QWidget>

#include "../../glasses/GlassGroupIDManager.hpp"

class QListLine: public QWidget
{
   Q_OBJECT

public:
   QListLine(QWidget* parent, const QPixmap& color_icon);
   QListLine(QWidget* parent, const Points points, const QPixmap& color_icon);

/*
public signals:
   void remove();


private slots:
   void remove_button_cliked() { emit remove(); }
   */

protected:
   QString _name_with_id(std::string base_name) const { return QString::fromUtf8(base_name + std::to_string(_id)); }
   std::unique_ptr<QFont> _default_font;
   QHBoxLayout* _layout;

private:
   inline static long _id_count = 0;
   const long _id;
};

