#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGUI.h"

#include <QColor>
#include <vector>

#include "../../glasses/GlassGroupIDManager.hpp"
#include "../../gui/CustomWidgets/QColorButton.hpp"
#include "../../gamemodes/GameModesManager.hpp"


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

   GameModesManager::GameModesEnum get_gamemode() const 
      { return _gm_manager.get_gamemode(_ui.gm_selection->currentIndex()); }

private slots:
   void on_b_settings_clicked() { /* TODO; */ }

   void on_gm_selection_currentIndexChanged(int index) 
      { _ui.description_label->setText(QString::fromUtf8(_gm_manager.get_description(get_gamemode()))); }

   void on_name_text_edit_textChanged() { _set_enable_add_buttons(); }
   void on_points_value_valueChanged(int i) { _set_enable_add_buttons(); }

   void on_b_add_player_clicked();
   void on_b_add_points_clicked();
   void on_b_play_clicked() { /* TODO; */ }

   void on_b_custom_color_player_toggled(bool checked) { /* TODO; */ }
   void on_b_custom_color_points_toggled(bool checked) { /* TODO; */ }

   void remove_player_line(QWidget* to_be_removed);
   void remove_points_line(QWidget* to_be_removed);

   void select_color(bool checked);

private:
   class ColorButtonsManager {
   public:
      ColorButtonsManager() = default;

      void add_button(QtGUI* gui, QColor& color);

      const std::vector<const QColor> get_color_buttons() const;

      QColor get_color(int ind) const { return _player_color_buttons[ind]->get_color(); }
      const QIcon get_icon(int ind) const { return _player_color_buttons[ind]->icon(); }
      int get_ind(const QColorButton& button) const;

      void set_visible(int ind, bool is_visible);

      void set_checked(int ind, bool is_checked) {
         _player_color_buttons[ind]->setChecked(is_checked);
         //_points_color_buttons[ind]->setChecked(is_checked);
      }

      void set_all_checked_false() {
         _assert_same_size();

         for (int i = 0; i < _player_color_buttons.size(); i++)
            set_checked(i, false);
      }

   private:
      void _assert_same_size() const { assert(_player_color_buttons.size() == _points_color_buttons.size()
                                       && "Both vectors must be of same size."); }

      std::vector<std::unique_ptr<QColorButton>> _player_color_buttons;
      std::vector<std::unique_ptr<QColorButton>> _points_color_buttons;
   };

   friend void ColorButtonsManager::add_button(QtGUI* gui, QColor& color);

   void _set_enable_add_buttons();

   Ui::QtGUIClass _ui;
   ColorButtonsManager _color_button_manager;

   GameModesManager _gm_manager;
   std::vector<GameModesManager::GameModesEnum> _gamemodes_list;

   static const std::vector<QColor> _default_colors;

   int _selected_color_button_ind = -1;

   std::vector<QColor> _players_lines_color;
   std::vector<QColor> _points_lines_color;
};

