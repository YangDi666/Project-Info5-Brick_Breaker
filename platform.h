#ifndef PLATFORM_H
#define PLATFORM_H
#include <GL/glu.h>

/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​regist the informations of the platform.  // YANG et DU
*
*/ 
class Platform
{
private:
    float x_,y_,z_;
    float width_;

public:
    Platform(float x, float y, float width);
    void display() const;
    void setPos(float x,float y);
    void setWidth(float width);
    void movePlatform(float move);
    float reflectBall(float posofPlatform);
    float getX_();
    float getY_();
    float getWidth_();
};

#endif // PLATFORM_H
