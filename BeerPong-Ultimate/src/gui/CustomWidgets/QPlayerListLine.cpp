#include "QPlayerListLine.hpp"

#include <QHBoxLayout>
#include <string>



QPlayerListLine::QPlayerListLine(QWidget* parent, const Player& player, const QPixmap& color_icon) :
   QListLine(parent, color_icon)
{
   _player_name_edit = new QLineEdit((QWidget*)this);
   _player_name_edit->setObjectName(_name_with_id("player_name_edit"));
   _player_name_edit->setFont(*_default_font);
   _player_name_edit->setMaxLength(30);
   _player_name_edit->setFrame(false);
   _player_name_edit->setText(QString::fromStdString((std::string)player));

   _layout->insertWidget(1, _player_name_edit);
}
