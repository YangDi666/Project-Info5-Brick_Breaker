#include "ball.h"
#include <math.h>

Ball::Ball(float x, float y, float z,float radius,float direction, float speed)
{
    x_=x;
    y_=y;
    z_=z;
    radius_=radius;
    speed_=speed;
    direction_=direction;//sui ji

    q_=gluNewQuadric();
}

void Ball::afficher() const
{

    glPushMatrix();

    glLoadIdentity();
    glTranslatef(x_,y_,z_);

    GLfloat CBall[]={0.8, 0.5, 0.6};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CBall);
    gluSphere(q_, radius_, 32, 32);

    glPopMatrix();
}

 Ball::~Ball()
 {
    gluDeleteQuadric(q_);
 }

 void Ball::setPos(float x, float y, float z)
 {
        x_=x;
        y_=y;
 }

 void Ball::setSpd(float speed)
 {  if(speed<1.0)
     speed_=speed;
     else
         speed_=1.0;
 }

 void Ball::setRadius_(float radius)
 {
     radius_=radius;
 }

 void Ball::setDirection_(float direction)
 {
     direction_=direction;
 }

 float Ball::getRadius_()
 {
     return radius_;
 }

 void Ball::ballMove()
 {
     x_+=speed_*cos(direction_);
     y_+=speed_*sin(direction_);
 }

 float Ball::getY_()
 {
     return y_;
 }

 float Ball::getY_before()
 {
     return y_-speed_*sin(direction_);
 }

 float Ball::getX_()
 {
     return x_;
 }

 float Ball::getX_before()
 {
     return x_-speed_*cos(direction_);
 }

 void Ball::ballCollide(float normal)
 {
     direction_=2.0*(normal+M_PI*1.0/2)-direction_;
 }

 float Ball::getSpeed_()
 {
     return speed_;
 }

 float Ball::getDirection_()
 {
     return direction_;
 }

void Ball::translation(float x)
{
    x_+=x;
}
