#ifndef BALL_H
#define BALL_H
#include <GL/glu.h>

/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​regist the informations of the ball.  // YANG et DU
*
*/ 
class Ball
{
private:
    float x_,y_,z_,direction_, speed_,radius_;//The position, direction the radius and the speed of the ball.
    GLUquadric* q_;//The quadric (ball) in QGLWidget

public:
    Ball(float x, float y, float z, float radius, float direction, float speed);// Constructor
    void afficher() const;//Display the ball in GLWidget
    virtual ~Ball();  //Destructor
	//setters
    void setPos(float x,float y,float z=0.0);
    void setSpd(float speed);
    void setRadius_(float radius);
    void setDirection_(float direction);
	//getters
    float  getRadius_();
    float getY_();
    float getX_();
    float getY_before();
    float getX_before();
    float getSpeed_();
    float getDirection_();
	
    void ballMove();//move the ball by change its position x et y
    void ballCollide(float normal);//change the ball's direction by the normal direction of the reflective interface
    void translation(float x);//the ball move x horizontally
	};

#endif // BALL_H
