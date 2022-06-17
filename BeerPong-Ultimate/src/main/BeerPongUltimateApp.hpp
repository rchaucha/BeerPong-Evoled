#pragma once

#include <QApplication>
#include <QVector2D>
#include <map>

class RGBCameraInput;

class BeerPongUltimateApp : public QApplication
{
   Q_OBJECT

public:
   BeerPongUltimateApp(int& argc, char** argv);

public slots:
   void update_glasses();

   void set_r_min(unsigned int r_min) { _r_min = r_min; }
   void set_r_max(unsigned int r_max) { _r_max = r_max; }
   void set_dist_between_circles(unsigned int dist_between_circles) { _dist_between_circles = dist_between_circles; }
   void set_detection_param1(double detection_param1) { _detection_param1 = detection_param1; }
   void set_detection_param2(double detection_param2) { _detection_param2 = detection_param2; }

private :
   QVector2D frame2Window(const QVector2D frame_coordinates) const;

   QSize _window_size, _frame_size;
   RGBCameraInput* _rgb_cam;
   std::map<unsigned long, QRectF> _circles;
   unsigned long _circles_id_count = 0;
   unsigned int _r_min;
   unsigned int _r_max;
   float _dist_between_circles = 0;
   double _detection_param1 = 100;
   double _detection_param2 = 30;
};

