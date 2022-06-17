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

private :
   QVector2D frame2Window(const QVector2D frame_coordinates) const;

   QSize _window_size, _frame_size;

   RGBCameraInput* _rgb_cam;

   std::map<unsigned long, QRectF> _circles;

   unsigned long _circles_id_count = 0;
};

