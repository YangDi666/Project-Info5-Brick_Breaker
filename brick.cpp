#include "brick.h"

Brick::Brick(int line, int column)
{
    line_=line;
    column_=column;
    width_=70.0/column_-1.0;
    height_=30.0/line_-0.5;
    b_=new int*[line_];
    for(int i = 0; i <line_; i++)
        b_[i] = new int[column_];

    for (int j=0;j<column_;j++)
        b_[0][j]=2;

    for (int i=1;i<line_;i++)
    {
        for(int j=0;j<column_;j++)
            b_[i][j]=1;
    }
}

void Brick::afficher() const
{
    GLfloat Cblanc[]={1.0,1.0,1.0,1.0};
    GLfloat PositionLamp[]={0.0,15.0,0.0,0.1};
    glLightfv(GL_LIGHT0,GL_POSITION,PositionLamp);
    glLightfv(GL_LIGHT0,GL_AMBIENT_AND_DIFFUSE,Cblanc);

    for (int i=0;i<line_;i++)
    {
        for(int j=0;j<column_;j++)
        {
            if(b_[i][j]==1)
            {
                glPushMatrix();

                glLoadIdentity();

                GLfloat CBrick[]={1.0, 1.0, 1.0};
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CBrick);

                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);//youshang
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//zuoshang
                glEnd();
                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//youshang
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                glEnd();
                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);// youxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                glEnd();
                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);// youxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);//zuoshang
                glEnd();
                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//youshang
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoshang
                glEnd();
                GLfloat CBrick2[]={0.5, 0.8, 1.0};
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CBrick2);
                glBegin(GL_QUADS);
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);// youxia
                glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                glEnd();

                glPopMatrix();
            }

            else
            {
                if(b_[i][j]==2)
                {
                    glPushMatrix();

                    glLoadIdentity();

                    GLfloat CBrick[]={1.0, 0.5, 0.8};
                    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,CBrick);

                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);//youshang
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//zuoshang
                    glEnd();
                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//youshang
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                    glEnd();
                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, 0.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);// youxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                    glEnd();
                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);// youxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, 0.0);//zuoshang
                    glEnd();
                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, 0.0);// youxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//youshang
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoshang
                    glEnd();
                    glBegin(GL_QUADS);
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);//zuoxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*(i+1)+0.5, -1.0);// youxia
                    glVertex3f(-35.0+70.0/column_*(j+1)-0.5, 28.0-30.0/line_*i, -1.0);//youshang
                    glVertex3f(-35.0+70.0/column_*j+0.5, 28.0-30.0/line_*i, -1.0);//zuoshang
                    glEnd();

                    glPopMatrix();
                }
            }
        }
    }
}

Brick::~Brick()
{
    for (int i = 0; i < line_; i ++)
    {
         delete[] b_[i];
    }
    delete [] b_;
}

int Brick::getLine_()
{
    return line_;
}

int Brick::getColumn_()
{
    return column_;
}

float Brick::getWidth_()
{
    return width_;
}
float Brick::getHeight_()
{
    return height_;
}

float Brick::getCenterX(int line_i,int column_j) const
{
    return 0.5*((-35.0+70.0/column_*column_j+0.5)+(-35.0+70.0/column_*(column_j+1)-0.5));
}

float Brick::getCenterY(int line_i,int column_j) const
{
    return 0.5*((28.0-30.0/line_*(line_i+1)+0.5)+(28.0-30.0/line_*line_i));
}

int Brick::getValofB(int line_i,int column_j)
{
    return b_[line_i][column_j];
}

void  Brick::brickHited(int line_i,int column_j)
{
    if(b_[line_i][column_j]>0)
        b_[line_i][column_j]-=1;
}

int Brick::brickLeft()
{
    int n=0;
    for(int i=0;i<line_;i++)
        for(int j=0;j<column_;j++)
        {
            if(b_[i][j]!=0)
                n++;
        }
    return n;
}

void Brick::reset()
{
    for (int j=0;j<column_;j++)
        b_[0][j]=2;
    for (int i=1;i<line_;i++)
    {
        for(int j=0;j<column_;j++)
            b_[i][j]=1;
    }
}
