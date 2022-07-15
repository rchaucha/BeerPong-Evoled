#include "QtGUI.hpp"

#include <cassert>
#include "../../gamemodes/RandomGM.hpp"
#include "../../gamemodes/GameModesManager.hpp"
#include "../../gui/CustomWidgets/QPlayerListLine.hpp"
#include "../../gui/CustomWidgets/QPointsListLine.hpp"
#include "../../gui/CustomWidgets/QColorButton.hpp"


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


void change_red_pix(QImage& img, const QColor& new_color)
{
   for (int y = 0; y < img.height(); ++y)
   {
      QRgb* line = reinterpret_cast<QRgb*>(img.scanLine(y));
      for (int x = 0; x < img.width(); ++x)
      {
         QRgb& rgb = line[x];
         if (qRed(rgb) > 100)
            rgb = new_color.rgb();
      }
   }
}


QtGUI::QtGUI(QWidget *parent) : QMainWindow(parent)
{
   _ui.setupUi(this);

   for (QColor color : _default_colors)
   {
      QImage icon_img = QPixmap(":/QtGUI/files/red_color.ico").toImage();
      change_red_pix(icon_img, color);
      QIcon icon(QPixmap::fromImage(icon_img));

      auto* new_player_color_button = new QColorButton(_ui.points_colors_layout, color, icon);
      auto* new_points_color_button = new QColorButton(_ui.points_colors_layout, color, icon);

      connect(new_player_color_button, &QColorButton::toggled, this, &QtGUI::remove_player_line);
      connect(new_points_color_button, &QColorButton::toggled, this, &QtGUI::remove_player_line);

      _ui.player_colors_layout->layout()->addWidget(new_player_color_button);
      _ui.points_colors_layout->layout()->addWidget(new_points_color_button);

      _player_color_buttons.push_back(new_player_color_button);
      _points_color_buttons.push_back(new_points_color_button);
   }
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

   // Gather all names from spin boxes and colors from the vector
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
   _players_lines_color.push_back(_selected_color);

   // Remove color button
   _selected_player_color_button->setVisible(false);

   // Add Player in the list
   auto* player_line = new QPlayerListLine((QWidget*)_ui.players_list, _ui.name_text_edit->text().toStdString(),
                                          _selected_player_color_button->icon().pixmap(QSize(22, 22)));
   _ui.players_list->layout()->addWidget(player_line);

   connect(player_line, &QListLine::remove, this, &QtGUI::remove_player_line);
}


void QtGUI::on_b_add_points_clicked()
{
   // Add color to vector
   _points_lines_color.push_back(_selected_color);

   // Remove color button
   _selected_points_color_button->setVisible(false);

   // Add Player in the list
   auto* points_line = new QPointsListLine((QWidget*)_ui.players_list, _ui.points_value->value(),
                                          _selected_player_color_button->icon().pixmap(QSize(22, 22)));
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


void QtGUI::_select_color(const QObject* sender, bool checked, std::vector<QColorButton*>& color_buttons)
{
   const QColorButton* sender_button = dynamic_cast<const QColorButton*>(sender);

   assert(sender_button && "Sender must be a QColorButton.");

   if (checked)
   {
      _selected_player_color_button = sender_button;
      for (QColorButton* color_button : _color_buttons)
      {
         if (color_button != sender_button)
            color_button->setChecked(false);
      }
   }
   else
      _selected_player_color_button = nullptr; // No color selected
}


void QtGUI::_select_player_color(bool checked)
{ 
   _select_color(QObject::sender(), checked, _player_color_buttons);
   _enable_or_disable_b_add_player();
}


void QtGUI::_select_points_color(bool checked)
{
   _select_color(QObject::sender(), checked, _points_color_buttons);
   _enable_or_disable_b_add_points();
}


void QtGUI::_enable_or_disable_b_add_player()
{
   bool is_player_name_set = _ui.name_text_edit->text().size() != 0;
   bool is_color_chosen = _selected_player_color_button != nullptr;

   if (is_player_name_set && is_color_chosen)
      _ui.b_add_player->setDisabled(false);
   else
      _ui.b_add_player->setDisabled(true);
}


void QtGUI::_enable_or_disable_b_add_points()
{
   bool is_points_name_set = _ui.points_value->value() != 0;
   bool is_color_chosen = _selected_points_color_button != nullptr;

   if (is_points_name_set && is_color_chosen)
      _ui.b_add_player->setDisabled(false);
   else
      _ui.b_add_player->setDisabled(true);
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