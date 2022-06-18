#include <iostream>
#include <execution>

#include <QtWidgets/QApplication>
#include <QVector2D>

#include "../Tools/RGBCameraInput.hpp"
#include "../Tools/DetectionTools.hpp"
#include "BeerPongUltimateApp.cpp"


int main(int argc, char* argv[])
{
   BeerPongUltimateApp qt_application(argc, argv);
   qt_application.init();

   return qt_application.exec();
}