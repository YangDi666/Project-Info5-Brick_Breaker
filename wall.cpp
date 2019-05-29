#include "wall.h"

Wall::Wall(float up,float down,float left,float right)
{
    up_=up;
    down_=down;
    left_=left;
    right_=right;
}

void Wall::afficher() const{
    GLfloat CWall[]={0.0, 0.7, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CWall);

    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex3f(left_,down_,0.0);
    glVertex3f(left_,up_,0.0);
    glVertex3f(left_,up_,0.0);
    glVertex3f(right_,up_,0.0);
    glVertex3f(right_,down_,0.0);
    glVertex3f(right_,up_,0.0);
    glEnd();
    GLfloat CWall1[]={0.0, 1.0, 0.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CWall1);
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glVertex3f(left_,down_,0.0);
    glVertex3f(right_,down_,0.0);
    glEnd();
}

float Wall::getUp_(){
    return up_;
}

float Wall::getDown_(){
    return down_;
}

float Wall::getLeft_(){
    return left_;
}

float Wall::getRight_(){
    return right_;
}
