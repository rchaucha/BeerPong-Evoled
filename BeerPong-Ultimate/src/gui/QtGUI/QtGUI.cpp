#include "QtGUI.hpp"

#include <cassert>
#include "../../gamemodes/RandomGM.hpp"
#include "../../gamemodes/GameModesManager.hpp"
#include "../../gui/CustomWidgets/QPlayerListLine.hpp"
#include "../../gui/CustomWidgets/QPointsListLine.hpp"


const std::vector<QColor> QtGUI::_default_colors = {
      QColor(255, 255, 255),    // White
      QColor(  0, 191, 255),    // Blue
      QColor(255,   0,   0),    // Red
      QColor(  0, 255,   0),    // Green
      QColor(255, 255,   0),    // Yellow
      QColor(139,  69,  19),    // Brown
      QColor(255, 105, 180),    // Pink
      QColor(128, 128, 128),    // Gray
      QColor(255, 140,   0),    // Orange
};


QtGUI::QtGUI(QWidget *parent) : QMainWindow(parent),
   _selected_player_color_ind(0),
   _selected_points_color_ind(0)
{
   _ui.setupUi(this);

   _color_buttons.push_back(_ui.b_white_player);
   _color_buttons.push_back(_ui.b_blue_player);
   _color_buttons.push_back(_ui.b_red_player);
   _color_buttons.push_back(_ui.b_green_player);
   _color_buttons.push_back(_ui.b_yellow_player);
   _color_buttons.push_back(_ui.b_brown_player);
   _color_buttons.push_back(_ui.b_pink_player);
   _color_buttons.push_back(_ui.b_gray_player);
   _color_buttons.push_back(_ui.b_orange_player);
}


std::vector<ColoredPlayer> QtGUI::get_players()
{
   assert(_players_lines_color.size() == _ui.players_list->layout()->count() + 1    // + 1 pour le vertical spacer
      && "_players_lines_color and the number of lines must be the same.");
      
   std::vector<ColoredPlayer> colored_players;

   // Gather all names from edit names and colors from the vector
   for (int i = 0; i < _players_lines_color.size(); i++)
   {
      QPlayerListLine* player_line = dynamic_cast<QPlayerListLine*>(_ui.players_list->layout()->itemAt(i)->widget());
      colored_players.push_back({ player_line->get_player_name(), _players_lines_color[i] });
   }

   return colored_players;
}


std::vector<ColoredPoints> QtGUI::get_points()
{
   assert(_points_lines_color.size() == _ui.points_list->layout()->count() + 1    // + 1 pour le vertical spacer
      && "_points_lines_color and the number of lines must be the same.");

   std::vector<ColoredPoints> colored_points;

   // Gather all names from edit names and colors from the vector
   for (int i = 0; i < _points_lines_color.size(); i++)
   {
      QPointsListLine* points_line = dynamic_cast<QPointsListLine*>(_ui.points_list->layout()->itemAt(i)->widget());
      colored_points.push_back({ points_line->get_points(), _points_lines_color[i] });
   }

   return colored_points;
}


void QtGUI::on_gm_selection_currentIndexChanged(int index)
{
   _ui.description_label->setText(QString::fromStdString(GameModesManager::get_description(get_gamemode())));
}


void QtGUI::on_name_text_edit_textChanged()
{
   _enable_or_disable_b_add_player();
}


void QtGUI::on_b_add_player_clicked()
{
   // Add color to vector
   _players_lines_color.push_back(_default_colors[_selected_player_color_ind]);

   // Remove color button
   auto* color_button = _color_buttons[_selected_player_color_ind];
   color_button->setVisible(false);

   // Add Player in the list
   auto* player_line = new QPlayerListLine((QWidget*)_ui.players_list, _ui.name_text_edit->text().toStdString(),
                                             color_button->icon().pixmap(QSize(22, 22)));
   _ui.players_list->layout()->addWidget(player_line);

   connect(player_line, &QListLine::remove, this, &QtGUI::remove_player_line);
}


void QtGUI::on_b_add_points_clicked()
{
   // Add color to vector
   _points_lines_color.push_back(_default_colors[_selected_points_color_ind]);

   // Remove color button
   auto* color_button = _color_buttons[_selected_points_color_ind];
   color_button->setVisible(false);

   // Add Player in the list
   auto* points_line = new QPointsListLine((QWidget*)_ui.players_list, _ui.points_value->value(),
                                             color_button->icon().pixmap(QSize(22, 22)));
   _ui.points_list->layout()->addWidget(points_line);

   connect(points_line, &QListLine::remove, this, &QtGUI::remove_points_line);
}


void QtGUI::remove_player_line(QWidget* to_be_removed)
{
   int ind = _ui.players_list->layout()->indexOf(to_be_removed);
   
   assert(ind > 0 && "The widget should be present in the layout.");

   _players_lines_color.erase(std::next(_players_lines_color.begin(), ind));

   _ui.players_list->layout()->removeWidget(to_be_removed);
   delete to_be_removed;
}


void QtGUI::remove_points_line(QWidget* to_be_removed)
{
   int ind = _ui.points_list->layout()->indexOf(to_be_removed);

   assert(ind > 0 && "The widget should be present in the layout.");

   _points_lines_color.erase(std::next(_points_lines_color.begin(), ind));

   _ui.points_list->layout()->removeWidget(to_be_removed);
   delete to_be_removed;
}


void QtGUI::_select_color(int color_index, bool checked)
{
   if (checked)
   {
      _selected_color = _default_colors[color_index];
      for (int ind = 0; ind < _color_buttons.size(); ind++)
      {
         if (ind != color_index)
            _color_buttons[ind]->setChecked(false);
      }
   }
   else
      _selected_color = QColor(0, 0, 0);  // Black = no color
}


void QtGUI::_select_player_color(int color_index, bool checked)
{
   _select_color(color_index, checked);
   _enable_or_disable_b_add_player();
}


void QtGUI::_select_points_color(int color_index, bool checked)
{
   _select_color(color_index, checked);
   _enable_or_disable_b_add_points();
}


void QtGUI::_enable_or_disable_b_add_player()
{
   bool is_player_name_set = _ui.name_text_edit->text().size() == 0;
   bool is_color_chosen = _selected_color != QColor(0, 0, 0);

   if (is_player_name_set && is_color_chosen)
      _ui.b_add_player->setDisabled(true);
   else
      _ui.b_add_player->setDisabled(false);
}


void QtGUI::_enable_or_disable_b_add_points()
{
   bool is_points_name_set = _ui.points_value->value() != 0;
   bool is_color_chosen = _selected_color != QColor(0, 0, 0);

   if (is_points_name_set && is_color_chosen)
      _ui.b_add_player->setDisabled(true);
   else
      _ui.b_add_player->setDisabled(false);
}



/*

To list all cameras : 

	DeviceEnumerator de;

	devices = de.getVideoDevicesMap();

	for (auto const &device : devices) {
		std::cout << "== VIDEO DEVICE (id:" << device.first << ") ==" << std::endl;
		std::cout << "Name: " << device.second.deviceName << std::endl;
	}

*/