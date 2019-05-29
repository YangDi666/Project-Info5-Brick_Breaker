#include "platform.h"
#include "math.h"
Platform::Platform(float x, float y, float width)
{
    x_=x;
    y_=y;
    z_=0;
    width_=width;
}

void Platform::display() const
{
    glPushMatrix();

    glLoadIdentity();

    GLfloat CPlatform[]={1.0, 0.65, 0.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CPlatform);

    glTranslatef(x_,y_,z_);
    glBegin(GL_QUADS);
    glVertex3f(0.0,-1.2,0.0);//zuoxia
    glVertex3f(width_,-1.2,0.0);// youxia
    glVertex3f(width_,0.0, 0.0);//youshang
    glVertex3f(0.0,0.0,0.0);//zuoshang
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0,-1.2,-1.0);//zuoxia
    glVertex3f(0.0,-1.2,0.0);// youxia
    glVertex3f(0.0,0.0,0.0);//youshang
    glVertex3f(0.0,0.0,-1.0);//zuoshang
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,0.0);//zuoxia
    glVertex3f(width_,0.0, 0.0);// youxia
    glVertex3f(width_,0.0, -1.0);//youshang
    glVertex3f(0.0,0.0,-1.0);//zuoshang
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(width_,-1.2,0.0);//zuoxia
    glVertex3f(width_,-1.2,-1.0);// youxia
    glVertex3f(width_,0.0, -1.0);//youshang
    glVertex3f(width_,0.0, 0.0);//zuoshang
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0,-1.2,0.0);//zuoxia
    glVertex3f(width_,-1.2,0.0);// youxia
    glVertex3f(width_,-1.2,-1.0);//youshang
    glVertex3f(0.0,-1.2,-1.0);//zuoshang
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(0.0,-1.2,-1.0);//zuoxia
    glVertex3f(width_,-1.2,-1.0);// youxia
    glVertex3f(width_,0.0, -1.0);//youshang
    glVertex3f(0.0,0.0,-1.0);//zuoshang
    glEnd();

    glPopMatrix();

}

void Platform::setPos(float x, float y){
    if(x<=27.0&&x>=-35.0)
    x_=x;
    y_=y;
}

void Platform::setWidth(float width){
    if(width<=50.0)
        if(width>=1.0)
            width_=width;
        else
            width_=1.0;
    else
        width_=50.0;
}

void Platform::movePlatform(float move){
    x_+=move;
    if(x_>35.0-width_)
        x_=35.0-width_;
    if(x_<-35.0)
        x_=-35.0;
}

float Platform::reflectBall(float posofPlatform){
    return M_PI*3.0/4-M_PI*1.0/2*(posofPlatform/width_);
}

float Platform::getX_(){
    return x_;
}

float Platform::getY_(){
    return y_;
}

float Platform::getWidth_(){
    return width_;
}
