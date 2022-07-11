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

   std::vector<ColoredPlayer> get_players();
   std::vector<ColoredPoints> get_points();

   std::string get_gamemode() { return _ui.gm_selection->currentText().toStdString(); }

private slots:
   void on_b_settings_clicked();

   void on_gm_selection_currentIndexChanged(int index);

   void on_name_text_edit_textChanged();

   void on_b_add_player_clicked();
   void on_b_add_points_clicked();
   void on_b_play_clicked();

   void on_b_white_player_toggled(bool checked) { _select_player_color(0, checked); }
   void on_b_blue_player_toggled(bool checked) { _select_player_color(1, checked); }
   void on_b_red_player_toggled(bool checked) { _select_player_color(2, checked); }
   void on_b_green_player_toggled(bool checked) { _select_player_color(3, checked); }
   void on_b_yellow_player_toggled(bool checked) { _select_player_color(4, checked); }
   void on_b_brown_player_toggled(bool checked) { _select_player_color(5, checked); }
   void on_b_pink_player_toggled(bool checked) { _select_player_color(6, checked); }
   void on_b_gray_player_toggled(bool checked) { _select_player_color(7, checked); }
   void on_b_orange_player_toggled(bool checked) { _select_player_color(8, checked); }
   void on_b_custom_color_player_toggled(bool checked) { /* TODO; */ }

   void on_b_white_points_toggled(bool checked) { _select_points_color(0, checked); }
   void on_b_blue_points_toggled(bool checked) { _select_points_color(1, checked); }
   void on_b_red_points_toggled(bool checked) { _select_points_color(2, checked); }
   void on_b_green_points_toggled(bool checked) { _select_points_color(3, checked); }
   void on_b_yellow_points_toggled(bool checked) { _select_points_color(4, checked); }
   void on_b_brown_points_toggled(bool checked) { _select_points_color(5, checked); }
   void on_b_pink_points_toggled(bool checked) { _select_points_color(6, checked); }
   void on_b_gray_points_toggled(bool checked) { _select_points_color(7, checked); }
   void on_b_orange_points_toggled(bool checked) { _select_points_color(8, checked); }
   void on_b_custom_color_points_toggled(bool checked) { /* TODO; */ }

   void remove_player_line(QWidget* to_be_removed);
   void remove_points_line(QWidget* to_be_removed);

private:
   void _select_color(int color_index, bool checked);
   void _select_player_color(int color_index, bool checked);
   void _select_points_color(int color_index, bool checked);
   void _enable_or_disable_b_add_player();
   void _enable_or_disable_b_add_points();

   
   Ui::QtGUIClass _ui;

   std::vector<QToolButton*> _color_buttons;

   static const std::vector<QColor> _default_colors;

   int _selected_player_color_ind;
   int _selected_points_color_ind;

   QColor _selected_color{ 0,0,0 };

   std::vector<QColor> _players_lines_color;
   std::vector<QColor> _points_lines_color;
};
