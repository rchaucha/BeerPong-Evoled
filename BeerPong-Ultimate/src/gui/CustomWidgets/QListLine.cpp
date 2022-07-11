#include "QListLine.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>


QListLine::QListLine(QWidget* parent, const QPixmap& color_icon) :
   QWidget(parent),
   _id(_id_count++)
{
   setObjectName(_name_with_id("list_line"));

   _layout = new QHBoxLayout((QWidget*)this);
   _layout->setSpacing(6);
   _layout->setObjectName(_name_with_id("list_line_layout"));
   _layout->setSizeConstraint(QLayout::SetFixedSize);

   QLabel* color_icon_img = new QLabel((QWidget*)this);
   color_icon_img->setObjectName(_name_with_id("color_icon"));
   color_icon_img->setPixmap(color_icon);

   _layout->addWidget(color_icon_img);

   QToolButton* remove_button = new QToolButton((QWidget*)this);
   remove_button->setObjectName(_name_with_id("remove_button"));
   remove_button->setAutoFillBackground(false);
   remove_button->setStyleSheet(QString::fromUtf8("padding: 4;"));
   QIcon red_cross_icon;
   red_cross_icon.addFile(QString::fromUtf8(":/QtGUI/files/red_cross.ico"), QSize(), QIcon::Normal, QIcon::Off);
   remove_button->setIcon(red_cross_icon);

   _layout->addWidget(remove_button);
   
   _default_font = std::make_unique<QFont>();
   _default_font->setFamilies({ QString::fromUtf8("Century Gothic") });
   _default_font->setPointSize(11);
   _default_font->setBold(true);
}