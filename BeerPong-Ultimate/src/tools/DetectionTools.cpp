#include "DetectionTools.hpp"

#include <execution>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


DetectionTools(unsigned int r_min, unsigned int r_max, float dist_between_circles, 
                  double param1, double param2) :
   _r_min(r_min),
   _r_max(r_max),
   _dist_between_circles(dist_between_circles), 
   _param1(param1),
   _param2(param2)
{}


// Creation of the rectangle containing the circle
QRectF circlesToRect(cv::Vec3f c)
{
   double radius = c[2];
   double x = c[0] - radius;
   double y = c[1] - radius;

   return QRectF(x, y, 2.0 * radius, 2.0 * radius);
}


// Detect glasses in the image src
void DetectionTools::glasses( const cv::Mat src, )
{
   std::vector<QRectF> OUT_rects;

   cv::Mat gray;
   if (src.channels() != 1)    // to grayscale
      cvtColor(src, gray, cv::COLOR_BGR2GRAY);
   else
      gray = src;

   medianBlur(gray, gray, 5);

   if (dist_between_circles <= 0)
      dist_between_circles = gray.rows / 9.0;

   std::vector<cv::Vec3f> circles;
   HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,
      _dist_between_circles,
      _param1, _param2, _r_min, _r_max);

   OUT_rects.resize(circles.size());

   std::transform(std::execution::par_unseq, circles.begin(), circles.end(), OUT_rects.begin(), circlesToRect);

   return OUT_rects;
}