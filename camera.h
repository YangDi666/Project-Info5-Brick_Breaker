#ifndef CAMERA_H
#define CAMERA_H
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QtConcurrentrun>

#include <cstdio>
#include <iostream>

/* 
*This​ ​class​ ​is​ ​used​ ​to​ contorl the WebCAM.  // DU
*
*/ 
using namespace cv;
using namespace std;

#include <QWidget>

namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = 0);
    ~Camera();
    void paintEvent(QPaintEvent *event);
    void detectGestion();
    float getMove();

private:
    Ui::Camera *ui;
    QImage img;
    Mat image_template_move_orig;
    Mat image_template_stop_orig;

    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=200;
    int subImageHeight=100;
    int templateWidth=50;
    int templateHeight=50;
    Mat frame1,frameRect1;
//    Mat frame1,frame2,frameRect1,frameRect2,image_template_move,image_template_stop;
//    Mat resultImageMove,resultImageStop;    // to store the matchTemplate result
    Point vectBest;
    Point vectBestBefore;
    bool isFirstTime;
    VideoCapture cap;
    float move;
};

#endif // CAMERA_H
