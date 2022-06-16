#pragma once

#include <opencv2\core\mat.hpp>
#include <opencv2\videoio.hpp>
#include <QVector2D>

class RGBCameraInput
{
public:
   RGBCameraInput(RGBCameraInput& other) = delete;
   void operator=(const RGBCameraInput&) = delete;

   static RGBCameraInput* getInstance();

   bool openCamera() { return _cap.open(0); }

   bool isFrameEmpty() const { return _current_frame.rows == 0 || _current_frame.cols == 0; }

   QVector2D getFrameSize() const { return QVector2D(_current_frame.cols, _current_frame.rows); }

   void updateFrame() { _cap >> _current_frame; }
   cv::Mat getFrame() const { return _current_frame; }

private:
   RGBCameraInput() { ; }

   static RGBCameraInput* _instance;

   cv::VideoCapture _cap;
   cv::Mat _current_frame;
};
