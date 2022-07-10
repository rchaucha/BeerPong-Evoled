#include "QtGUI.hpp"

#include "../../gamemodes/RandomGM.hpp"
#include "../../gamemodes/GameModesManager.hpp"

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


QtGUI::QtGUI(QWidget *parent) : QMainWindow(parent)
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
   // Add ColoredPlayer
   ColoredPlayer colored_player;
   colored_player.player = _ui.name_text_edit->text().toStdString();
   colored_player.color = _default_colors[_selected_player_color_ind];
   _selected_players.push_back(colored_player);

   // Remove color button
   _color_buttons[_selected_player_color_ind]->setVisible(false);

   // Add Player in the list
   _ui.scrollAreaWidgetContents->layout()->addWidget();
}


QHBoxLayout* QtGUI::_generate_new_player_line(Player name, QColor color)
{
   QHBoxLayout* new_layout = new QHBoxLayout();
   new_layout->setSpacing(6);
   new_layout->setObjectName(QString::fromUtf8("new_layout"));
   new_layout->setSizeConstraint(QLayout::SetFixedSize);
   label_2 = new QLabel(points_list_layout);
   label_2->setObjectName(QString::fromUtf8("label_2"));
   label_2->setPixmap(QPixmap(QString::fromUtf8(":/QtGUI/files/pink.ico")));

   new_layout->addWidget(label_2);

   lineEdit = new QLineEdit(points_list_layout);
   lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
   lineEdit->setFont(font1);
   lineEdit->setMaxLength(30);
   lineEdit->setFrame(false);

   new_layout->addWidget(lineEdit);

   toolButton_2 = new QToolButton(points_list_layout);
   toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
   toolButton_2->setAutoFillBackground(false);
   toolButton_2->setStyleSheet(QString::fromUtf8("padding: 4;"));
   QIcon icon12;
   icon12.addFile(QString::fromUtf8(":/QtGUI/files/red_cross.ico"), QSize(), QIcon::Normal, QIcon::Off);
   toolButton_2->setIcon(icon12);

   new_layout->addWidget(toolButton_2);

   return QHBoxLayout();
}

void QtGUI::_select_player_color(int color_index, bool checked)
{
   if (checked)
   {
      _selected_player_color = _default_colors[color_index];
      for (int ind = 0; ind < _color_buttons.size(); ind++)
      {
         if (ind != color_index)
            _color_buttons[ind]->setChecked(false);
      }
   }
   else
      _selected_player_color = QColor(0, 0, 0);  // Black = no color

   _enable_or_disable_b_add_player();
}


void QtGUI::_enable_or_disable_b_add_player()
{
   bool is_player_name_set = _ui.name_text_edit->text().size() == 0;
   bool is_color_chosen = _selected_player_color != QColor(0, 0, 0);

   if (is_player_name_set && is_color_chosen)
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