#include "camera.h"
#include "ui_camera.h"
#include <QTime>
#include <QTimer>


#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

Camera::Camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);

    Rect workingRect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
    image_template_move_orig=imread("C://Users//asus//Desktop//bureau//ST//smestre 8//info//ANG Di DU Pingjie//code//code//move.jpg");
    image_template_stop_orig = imread("C://Users//asus//Desktop//bureau//ST//smestre 8//info//ANG Di DU Pingjie//code//code//stop.jpg");

    vectBestBefore=Point(0,0);
    cap.open(0); // open the default camera
    cap.set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!cap.isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;

    }
    else
        cout<<"OPEN!"<<endl;

    // Get frame1
    cap >> frame1;
    // Mirror effect
    cv::flip(frame1,frame1,1);
    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame1,workingRect),frameRect1,COLOR_BGR2GRAY);
    //Mat(frame1,rect).copyTo(frameRect1);
    isFirstTime=true;
}

Camera::~Camera()
{
    delete ui;
}

void Camera::paintEvent(QPaintEvent *event){
    detectGestion();
}

void Camera::detectGestion(){

    Mat frame2,frameRect2,image_template_move,image_template_stop;
    Mat resultImageMove,resultImageStop;    // to store the matchTemplate result

    // Create the matchTemplate image result
    int result_cols =  frame1.cols-templateWidth  + 1;
    int result_rows = frame1.rows-templateHeight + 1;
    resultImageMove.create( result_cols, result_rows, CV_32FC1 );
    resultImageStop.create( result_cols, result_rows, CV_32FC1 );

    Rect workingRect((frameWidth-subImageWidth)/2,frameHeight/2+(frameHeight/2-subImageHeight)/2,subImageWidth,subImageHeight);
    Point workingCenter(workingRect.x+subImageWidth/2,workingRect.y+subImageHeight/2);
    Rect templateRect((workingRect.width-templateWidth)/2,(workingRect.height-templateHeight)/2,templateWidth,templateHeight);

    // Get frame2
    cap >> frame2;
    // Mirror effect
    cv::flip(frame2,frame2,1);
    // Extract working rect in frame2 and convert to gray
    cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

    // Extract template image in frame1
    //Mat templateImage(frameRect1,templateRect);
    cv::cvtColor(image_template_move_orig,image_template_move,COLOR_BGR2GRAY);
    cv::cvtColor(image_template_stop_orig,image_template_stop,COLOR_BGR2GRAY);
    cv::flip(image_template_move,image_template_move,1);
    cv::flip(image_template_stop,image_template_stop,1);

    // Do the Matching between the working rect in frame2 and the templateImage in frame1
    //matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
    matchTemplate( frameRect2, image_template_move, resultImageMove, TM_CCORR_NORMED );
    matchTemplate( frameRect2, image_template_stop, resultImageStop, TM_CCORR_NORMED );

    // Localize the best match with minMaxLoc
    double minValMove; double maxValMove; Point minLocMove; Point maxLocMove;
    double minValStop; double maxValStop; Point minLocStop; Point maxLocStop;
    //minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
    minMaxLoc( resultImageMove, &minValMove, &maxValMove, &minLocMove, &maxLocMove);
    cout<<"Max of move:"<<maxValMove<<endl;
    minMaxLoc( resultImageStop, &minValStop, &maxValStop, &minLocStop, &maxLocStop);
    cout<<"Max of stop:"<<maxValStop<<endl;
    // Compute the translation vector between the origin and the matching rect
    Point vectMove(maxLocMove.x-templateRect.x,maxLocMove.y-templateRect.y);
    //Point vectStop(maxLocStop.x-templateRect.x,maxLocStop.y-templateRect.y);
    // Draw green rectangle and the translation vector
    rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);

    if(maxValMove>0.85||maxValStop>0.85){
        if(maxValMove>maxValStop){

            vectBest=vectMove;
            if(isFirstTime){
            isFirstTime=false;
            }
            else{
                move=(vectBest.x-vectBestBefore.x)/100.0*40.0;
            }

        }
        else{
            vectBest=Point(0,0);
            move=0.0;
            isFirstTime=true;
        }
    }
    else{
        isFirstTime=true;
    }

    Point p(workingCenter.x+vectBest.x,workingCenter.y+vectBest.y);


    arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);


    img = QImage( (const unsigned char*)(frame2.data), frame2.cols, frame2.rows, QImage::Format_RGB888 );
    ui->cameraLabel->setPixmap( QPixmap::fromImage(img));
    ui->cameraLabel->resize( ui->cameraLabel->pixmap()->size());

    swap(frameRect1,frameRect2);

    vectBestBefore=vectBest;


/*
    cap >> frame2;

    // Mirror effect
    cv::flip(frame2,frame2,1);
    // Extract working rect in frame2 and convert to gray
    cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

    // Extract template image in frame1
    Mat templateImage(frameRect1,templateRect);
    // Do the Matching between the working rect in frame2 and the templateImage in frame1
    matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );

    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
    // Compute the translation vector between the origin and the matching rect
    Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);
    move=vect.x/100.0*10.0;
    // Draw green rectangle and the translation vector
    rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
    Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
    arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);

    img = QImage( (const unsigned char*)(frame2.data), frame2.cols, frame2.rows, QImage::Format_RGB888 );
    ui->cameraLabel->setPixmap( QPixmap::fromImage(img));
    ui->cameraLabel->resize( ui->cameraLabel->pixmap()->size());

    swap(frameRect1,frameRect2);
*/
}

float Camera::getMove(){
    return move;
}
