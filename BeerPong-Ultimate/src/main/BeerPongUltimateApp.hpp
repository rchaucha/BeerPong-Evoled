#pragma once

#include <QApplication>
#include <QVector2D>

class RGBCameraInput;

class BeerPongUltimateApp : public QApplication
{
   Q_OBJECT

public:
   BeerPongUltimateApp(int& argc, char** argv);

public slots:
   void detect_glasses() {  }

private :
   QVector2D frame2Window(const QVector2D frame_coordinates) const;

   QSize _window_size, _frame_size;

   RGBCameraInput* _rgb_cam;

   std::vector<QRectF> _circles;
};

