#ifndef BRICK_H
#define BRICK_H
#include <GL/glu.h>

/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​regist the informations of the bricks.  // YANG et DU
*
*/ 
class Brick
{
private:
    int line_, column_;// the number of the bricks.
    float width_,height_;// size of one brick
    int **b_;// a table 2D for represent the stats of the brick (1 exist, 2 special point,or 0 destucted)

public:  
    Brick(int line, int column);//constructor
    void afficher() const;//display in the GLWidget
    virtual ~Brick();//destructor
	//getters
    int getLine_();
    int getColumn_();
    float getWidth_();
    float getHeight_();
    float getCenterX(int line_i,int column_j) const;
    float getCenterY(int line_i, int column_j) const;
	
    void  brickHited(int line_i,int column_j);//change the brick located in i,j to destroyed
    int   getValofB(int line_i,int column_j);// get the value of the brick located in i,j
    int   brickLeft();// the number of the actuel bricks exist
    void  reset();// reset the values of bricks
};

#endif // BRICK_H
