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
      _color_button_manager.add_button(this, color);
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
   _players_lines_color.push_back(_color_button_manager.get_color(_selected_color_button_ind));

   // Remove color button
   _color_button_manager.set_visible(_selected_color_button_ind, false);

   // Add Player in the list
   auto* player_line = new QPlayerListLine((QWidget*)_ui.players_list, _ui.name_text_edit->text().toStdString(),
                     _color_button_manager.get_icon(_selected_color_button_ind)->pixmap(QSize(22, 22)));
   _ui.players_list->layout()->addWidget(player_line);

   connect(player_line, &QListLine::remove, this, &QtGUI::remove_player_line);
}


void QtGUI::on_b_add_points_clicked()
{
   // Add color to vector
   _points_lines_color.push_back(_color_button_manager.get_color(_selected_color_button_ind));

   // Remove color button
   _color_button_manager.set_visible(_selected_color_button_ind, false);

   // Add Player in the list
   auto* points_line = new QPointsListLine((QWidget*)_ui.players_list, _ui.points_value->value(),
                     _color_button_manager.get_icon(_selected_color_button_ind)->pixmap(QSize(22, 22)));
   _ui.points_list->layout()->addWidget(points_line);

   connect(points_line, &QListLine::remove, this, &QtGUI::remove_points_line);
}


void QtGUI::remove_player_line(QWidget* to_be_removed)
{
   int ind = _ui.players_list->layout()->indexOf(to_be_removed);

   assert(ind > 0 && "The widget should be present in the layout.");

   // Show the color button as available
   _color_button_manager.add_button(this, _players_lines_color[ind]);

   // Remove the line
   _players_lines_color.erase(std::next(_players_lines_color.begin(), ind));

   _ui.players_list->layout()->removeWidget(to_be_removed);
   delete to_be_removed;
}


void QtGUI::remove_points_line(QWidget* to_be_removed)
{
   int ind = _ui.points_list->layout()->indexOf(to_be_removed);

   assert(ind > 0 && "The widget should be present in the layout.");

   // Show the color button as available
   _color_button_manager.add_button(this, _points_lines_color[ind]);

   // Remove the line
   _points_lines_color.erase(std::next(_points_lines_color.begin(), ind));

   _ui.points_list->layout()->removeWidget(to_be_removed);
   delete to_be_removed;
}


void QtGUI::ColorButtonsManager::add_button(QtGUI* gui, QColor& color)
{
   // If button already exists, just unhide it
   for (const auto& but : _player_color_buttons)
   {
      if (but->get_color() == color)
      {
         but->setVisible(true);
         return;
      }
   }

   // Otherwise, we create it
   QImage icon_img = QPixmap(":/QtGUI/files/red_color.ico").toImage();
   change_red_pix(icon_img, color);
   QIcon icon(QPixmap::fromImage(icon_img));

   auto* new_player_color_button = new QColorButton(gui->_ui.player_colors_layout, color, icon);
   auto* new_points_color_button = new QColorButton(gui->_ui.points_colors_layout, color, icon);

   connect(new_player_color_button, &QColorButton::toggled, gui, &QtGUI::_select_player_color);
   connect(new_points_color_button, &QColorButton::toggled, gui, &QtGUI::_select_points_color);

   gui->_ui.player_colors_layout->layout()->addWidget(new_player_color_button);
   gui->_ui.points_colors_layout->layout()->addWidget(new_points_color_button);

   _player_color_buttons.push_back(new_player_color_button);
   _points_color_buttons.push_back(new_points_color_button);
}


const std::vector<const QColorButton*> QtGUI::ColorButtonsManager::get_color_buttons() const
{
   std::vector<const QColorButton*> color_buttons;
   std::transform(_player_color_buttons.cbegin(), _player_color_buttons.cend(), color_buttons.begin(),
      [](const QColorButton* b) { return b; });;

   return color_buttons;
}


int QtGUI::ColorButtonsManager::get_ind(const QColorButton* button) const
{
   _assert_same_size();

   for (int ind = 0; ind < _player_color_buttons.size(); ind++)
   {
      if (_player_color_buttons[ind] == button || _points_color_buttons[ind] == button)
         return ind;
   }
   return -1;
}


void QtGUI::ColorButtonsManager::set_visible(int ind, bool is_visible) {
   _assert_same_size();

   if (_player_color_buttons.size() < ind)
   {
      // TODO : raise error
   }

   _player_color_buttons[ind]->setVisible(is_visible);
   _points_color_buttons[ind]->setVisible(is_visible);
}


void QtGUI::_select_color(const QObject* sender, bool checked)
{
   const QColorButton* sender_button = dynamic_cast<const QColorButton*>(sender);

   assert(sender_button && "Sender must be a QColorButton.");

   if (checked)
   {
      _selected_color_button_ind = _color_button_manager.get_ind(sender_button);

      int ind = 0;
      for (const QColorButton* color_button : _color_button_manager.get_color_buttons())
      {
         if (color_button != sender_button)
            _color_button_manager.set_checked(ind, false);

         ind++;
      }
   }
   else
      _selected_color_button_ind = -1; // No color selected
}


void QtGUI::_select_player_color(bool checked)
{ 
   _select_color(QObject::sender(), checked);
   _enable_or_disable_b_add_player();
}


void QtGUI::_select_points_color(bool checked)
{
   _select_color(QObject::sender(), checked);
   _enable_or_disable_b_add_points();
}


void QtGUI::_enable_or_disable_b_add_player()
{
   bool is_player_name_set = _ui.name_text_edit->text().size() != 0;
   bool is_color_chosen = _selected_color_button_ind != -1;

   if (is_player_name_set && is_color_chosen)
      _ui.b_add_player->setDisabled(false);
   else
      _ui.b_add_player->setDisabled(true);
}


void QtGUI::_enable_or_disable_b_add_points()
{
   bool is_points_name_set = _ui.points_value->value() != 0;
   bool is_color_chosen = _selected_color_button_ind != -1;

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