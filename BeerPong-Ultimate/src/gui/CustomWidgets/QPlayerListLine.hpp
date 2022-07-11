#pragma once

#include "QListLine.hpp"

#include <QLineEdit>


class QPlayerListLine : public QListLine
{
public:
   QPlayerListLine(QWidget* parent, const Player& player, const QPixmap& color_icon);

   const Player& get_player_name() { return _player_name_edit->text().toStdString(); }

private :
   QLineEdit* _player_name_edit;
};

