#ifndef WALL_H
#define WALL_H
#include <GL/glu.h>

/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​regist the informations of the walls.  // DU
*
*/ 
class Wall
{
private:
    float up_,down_,left_,right_;
    public:

public:
    Wall(float up,float down,float left,float right);
    void afficher() const;
    float getUp_();
    float getDown_();
    float getLeft_();
    float getRight_();
};

#endif // WALL_H
