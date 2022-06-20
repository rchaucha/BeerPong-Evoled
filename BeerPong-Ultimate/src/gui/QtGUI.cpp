#include "QtGUI.hpp"

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