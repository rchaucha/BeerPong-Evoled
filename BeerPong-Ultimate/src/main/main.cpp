#include <iostream>
#include <execution>

#include <opencv2/highgui.hpp>
#include <QtWidgets/QApplication>
#include <QVector2D>

#include "../Tools/RGBCameraInput.hpp"
#include "../Tools/DetectionTools.hpp"


int main(int argc, char* argv[])
{
   QApplication qt_application(argc, argv);


 
   cv::Rect2d projected_area = cv::selectROI(rgb_cam->getFrame(), false, false);

   return qt_application.exec();
}