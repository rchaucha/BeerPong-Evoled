#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGUI.h"

#include <QColor>
#include <vector>

#include "../../glasses/GlassGroupIDManager.hpp"


struct ColoredPlayer {
   Player player;
   QColor color;
};

struct ColoredPoints {
   Points points;
   QColor color;
};


class QtGUI : public QMainWindow
{
   Q_OBJECT

public:
   QtGUI(QWidget *parent = Q_NULLPTR);

   std::vector<ColoredPlayer> get_players() { return _selected_players; }
   std::vector<ColoredPoints> get_points()  { return _selected_points; }

   std::string get_gamemode() { return _ui.gm_selection->currentText().toStdString(); }

signals:


private slots:
   void on_b_settings_clicked();

   void on_gm_selection_currentIndexChanged(int index);

   void on_b_add_player_clicked();
   void on_b_add_points_clicked();
   void on_b_play_clicked();

private:
   Ui::QtGUIClass _ui;

   static const std::vector<QColor> _default_colors;

   QColor _selected_player_color;
   QColor _selected_points_color;

   std::vector<ColoredPlayer> _selected_players;
   std::vector<ColoredPoints> _selected_points;
};
