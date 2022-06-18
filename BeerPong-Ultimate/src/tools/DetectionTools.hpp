#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <QRectF>

class DetectionTools
{
public:
   static void glasses( const cv::Mat src, 
                        std::vector<QRectF> OUT_rects,
                        unsigned int r_min, 
                        unsigned int r_max, 
                        float dist_between_circles = 0, 
                        double param1 = 100, 
                        double param2 = 30);
};

