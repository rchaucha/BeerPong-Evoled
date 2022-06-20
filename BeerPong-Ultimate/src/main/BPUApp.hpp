#pragma once

#include <QApplication>
#include <QVector2D>
#include <map>
#include <opencv2/core/types.hpp>
#include "../gui/ProjectorDisplay.hpp"
#include "../gui/QtGUI.hpp"

class RGBCameraInput;
class GameMode;

class BPUApp : public QApplication
{
   Q_OBJECT

public:
   BPUApp(int& argc, char** argv);
   ~BPUApp();

   int init();

public slots:
   void update_glasses();
   void launch_gamemode(GameMode* gamemode);
   void close_current_gamemode();

   void open_webcam(int id);

   void set_r_min(unsigned int r_min) { _r_min = r_min; }
   void set_r_max(unsigned int r_max) { _r_max = r_max; }
   void set_dist_between_circles(unsigned int dist_between_circles) { _dist_between_circles = dist_between_circles; }
   void set_detection_param1(double detection_param1) { _detection_param1 = detection_param1; }
   void set_detection_param2(double detection_param2) { _detection_param2 = detection_param2; }

private :
   QVector2D _frame2window(const QVector2D frame_coordinates) const;
   int _err_msg(const QString& msg);
   unsigned long _get_corresponding_id(const QRectF& rect);

   QtGUI _main_gui;
   ProjectorDisplay _projector_win;

   GameMode* _game_mode;

   cv::Rect2d _frame_area;
   QSize _window_size, _frame_size;
   RGBCameraInput* _rgb_cam;

   std::map<unsigned long, QRectF> _circles;
   unsigned long _circles_id_count;

   unsigned int _r_min;
   unsigned int _r_max;
   float _dist_between_circles;
   double _detection_param1;
   double _detection_param2;
};

