#include "QtGUI.hpp"

#include "RandomGM.hpp"


const std::vector<QColor> BPUApp::_default_colors = {
      QColor(255, 255, 255),    // White
      QColor(  0, 191, 255),    // Blue
      QColor(255,   0,   0),    // Red
      QColor(  0, 255,   0),    // Green
      QColor(255, 255,   0),    // Yellow
      QColor(255, 105, 180),    // Pink
      QColor(128, 128, 128),    // Gray
      QColor(139,  69,  19),    // Brown
      QColor(255, 140,   0),    // Orange
};


QtGUI::QtGUI(QWidget *parent) : QMainWindow(parent)
{
   _ui.setupUi(this);
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