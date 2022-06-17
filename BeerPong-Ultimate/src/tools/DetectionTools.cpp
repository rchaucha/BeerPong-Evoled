#include "DetectionTools.hpp"

#include <execution>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

// Creation of the rectangle containing the circle
QRectF circlesToRect(cv::Vec3f c)
{
   double radius = c[2];
   double x = c[0] - radius;
   double y = c[1] - radius;

   return QRectF(x, y, 2.0 * radius, 2.0 * radius);
}

// Detect glasses in the image src
void DetectionTools::glasses( const cv::Mat src, std::vector<QRectF> OUT_rects, 
                              unsigned int r_min, unsigned int r_max, 
                              float distance_between_circles, double param1, double param2)
{
   cv::Mat gray;
   if (src.channels() != 1)    // to greyscale
      cvtColor(src, gray, cv::COLOR_BGR2GRAY);
   else
      gray = src;

   medianBlur(gray, gray, 5);

   if (distance_between_circles <= 0)
      distance_between_circles = gray.rows / 9.0;

   std::vector<cv::Vec3f> circles;
   HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
      distance_between_circles,
      param1, param2, r_min, r_max);

   OUT_rects.clear();
   OUT_rects.resize(circles.size());

   std::transform(std::execution::par_unseq, circles.begin(), circles.end(), OUT_rects.begin(), circlesToRect);
}