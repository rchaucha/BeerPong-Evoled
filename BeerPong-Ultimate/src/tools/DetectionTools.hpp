#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <QRectF>
#include <QRectF>

class DetectionTools
{
public:
   DetectionTools(unsigned int r_min = 10, unsigned int r_max = 30, 
                  float dist_between_circles = 0, 
                  double param1 = 100, double param2 = 30);

   std::vector<QRectF> detect_glasses( const cv::Mat src);

   void set_r_min(unsigned int r_min) { _r_min = r_min;}
   void set_r_max(unsigned int r_max) { _r_max = _max(r_max, _r_min);}
   void set_dist_between_circles(float dist_between_circles) { _dist_between_circles = _max(0, dist_between_circles); }
   void set_param1(double param1) { _param1 = param1; }
   void set_param2(double param2) { _param2 = param2; }

private:
   template<class T> 
   const T& _max(const T& a, const T& b)
   { return (b > a) ? b : a; }

   unsigned int   _r_min;
   unsigned int   _r_max; 
   float          _dist_between_circles; 
   double         _param1;
   double         _param2;
};

