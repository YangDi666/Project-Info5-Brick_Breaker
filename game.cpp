#include "game.h"
#include <QWidget>
#include "math.h"
#include <iostream>
#include <fstream>

bool lineIntersectSide(Point A, Point B, Point C, Point D)
{
    // A(x1, y1), B(x2, y2)的直线方程为：
    // f(x, y) =  (y - y1) * (x1 - x2) - (x - x1) * (y1 - y2) = 0
    float fC = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
    float fD = (D.y - A.y) * (A.x - B.x) - (D.x - A.x) * (A.y - B.y);

    if(fC * fD > 0)
        return false;
    return true;
}

bool enterBrick(float brickCenterX,float brickCenterY,Ball *ball){
    if(((ball->getX_before()-brickCenterX)*(ball->getX_()-ball->getX_before())+(ball->getY_before()-brickCenterY)*(ball->getY_()-ball->getY_before()))<=0)
        return true;
    return false;
}

bool sideIntersectSide(Point A, Point B, Point C, Point D)
{
    if(!lineIntersectSide(A, B, C, D))
        return false;
    if(!lineIntersectSide(C, D, A, B))
        return false;
    return true;
}

bool touchCorner(Point corner,Ball* ball){
    if((pow(corner.x-ball->getX_(),2)+pow(corner.y-ball->getY_(),2))<=pow(ball->getRadius_(),2)&&
            (pow(corner.x-ball->getX_before(),2)+pow(corner.y-ball->getY_before(),2))>pow(ball->getRadius_(),2))
        return true;
    return false;
}

Game::Game()
{
   ball_=new Ball(-11.0,-20.0,0.0,1.0,M_PI*1.5/2,0.0);
   brick_=new Brick(12,10);
   platform_=new Platform(-15.0,-21.0,8.0);
   wall_=new Wall(28.0f,-25.0f,-35.0f,35.0f);

   NumberOfBall_=3;
   level_=1;
   score_=0;
   name_="Someone";
}

void Game::afficher() const
{
    ball_->afficher();
    brick_->afficher();
    platform_->display();
    wall_->afficher();
}

void Game::update()
{
    if(ball_->getSpeed_()==0.0)
        ball_->setPos(platform_->getX_()+(platform_->getWidth_())/2,platform_->getY_()+ball_->getRadius_(),0.0);
    else{
        ball_->ballMove();
        collide();
    }
        if(isLostOneBall())
            lostOneBall();
}

Platform* Game::getPlatform_(){
    return platform_;
}

Ball* Game::getBall_(){
    return ball_;
}

void Game::collide(){
  if(ball_->getX_()<=(wall_->getLeft_()+ball_->getRadius_())){

        //ball_->ballCollide(0.0f);
           if(cos(ball_->getDirection_())<0){
               ball_->ballCollide(0.0f);
           }
    }
    if(ball_->getX_()>=(wall_->getRight_()-ball_->getRadius_())){
        //ball_->ballCollide(M_PI);
            if(cos(ball_->getDirection_())>0){
                ball_->ballCollide(M_PI);
            }
    }
    if(ball_->getY_()>=(wall_->getUp_()-ball_->getRadius_())){

        //ball_->ballCollide(3.0/2*M_PI);
            if(sin(ball_->getDirection_())>0){
                ball_->ballCollide(3.0/2*M_PI);
            }

    }
    if(ball_->getY_()<=(wall_->getDown_()+ball_->getRadius_())){
       // ball_->ballCollide(1.0/2*M_PI);
    }

    if((ball_->getY_()<platform_->getY_()+ball_->getRadius_()&&ball_->getY_()>platform_->getY_()+ball_->getRadius_()-ball_->getSpeed_())
            &&(ball_->getX_()>=platform_->getX_()&&ball_->getX_()<=platform_->getX_()+platform_->getWidth_())){
        ball_->setDirection_(platform_->reflectBall(ball_->getX_()-platform_->getX_()));
    }

    if(ball_->getY_()>=(brick_->getCenterY(brick_->getLine_()-1,brick_->getColumn_()-1)-1.0/2*brick_->getHeight_()-ball_->getRadius_())){
        int i = 0;
        int j = 0;
        for (i =0;i<brick_->getLine_();i++){
            for(j = 0;j<brick_->getColumn_();j++){
                if(ball_->getX_()<brick_->getCenterX(0,j))
                    break;
            }

            if(ball_->getY_()> brick_->getCenterY(i,0))
                break;
        }
        // i,j 是右下角的砖

         Point posBall1 = { ball_->getX_before(), ball_->getY_before()};
         Point posBall2 = { ball_->getX_(), ball_->getY_()};
         Point vertexLine1 ;
         Point vertexLine2 ;
         Point vertexLine3 ;
         Point vertexLine4 ;
         Point corner;
        if(i!=0){
           // i-1   上面儿的砖
                    if(j!=0){
                       // j-1   左面儿的砖
                        if(brick_->getValofB(i-1,j-1))
                        {         //砖块是否存在
                            vertexLine1={brick_->getCenterX(i-1,j-1),brick_->getCenterY(i-1,j-1)-1.0f/2*brick_->getHeight_()-ball_->getRadius_()};
                            vertexLine2={brick_->getCenterX(i-1,j-1)+1.0f/2*brick_->getWidth_(),brick_->getCenterY(i-1,j-1)-1.0f/2*brick_->getHeight_()-ball_->getRadius_()};
                            vertexLine3={brick_->getCenterX(i-1,j-1)+1.0f/2*brick_->getWidth_()+ball_->getRadius_(),brick_->getCenterY(i-1,j-1)-1.0f/2*brick_->getHeight_()};
                            vertexLine4={brick_->getCenterX(i-1,j-1)+1.0f/2*brick_->getWidth_()+ball_->getRadius_(),brick_->getCenterY(i-1,j-1)};
                            corner     ={brick_->getCenterX(i-1,j-1)+1.0f/2*brick_->getWidth_(),brick_->getCenterY(i-1,j-1)-1.0f/2*brick_->getHeight_()};
                            if(enterBrick(brick_->getCenterX(i-1,j-1),brick_->getCenterY(i-1,j-1),ball_)){
                                if(sideIntersectSide(posBall1, posBall2, vertexLine1, vertexLine2))
                                {     //下边儿

                                    ball_->ballCollide(3.0/2*M_PI);
                                    brick_->brickHited(i-1,j-1);
                                    score_++;

                                }
                                else if(sideIntersectSide(posBall1, posBall2, vertexLine3, vertexLine4))
                                {   //右边儿
                                    ball_->ballCollide(0.0);
                                    brick_->brickHited(i-1,j-1);
                                    score_++;
                                }
                                else if(touchCorner(corner,ball_))
                                {   // 角
                                     //ball_->ballCollide(atan2(ball_->getY_()-corner.y,ball_->getX_()-corner.x));
                                     ball_->ballCollide(-M_PI/4.0);
                                     brick_->brickHited(i-1,j-1);
                                     score_++;
                                }

                            }
                        }
                    }
                    if(j!=brick_->getColumn_()){
                       // j     右面儿的砖
                        if(brick_->getValofB(i-1,j))
                        {
                            vertexLine1={brick_->getCenterX(i-1,j),brick_->getCenterY(i-1,j)-1.0f/2*brick_->getHeight_()-ball_->getRadius_()};
                            vertexLine2={brick_->getCenterX(i-1,j)-1.0f/2*brick_->getWidth_(),brick_->getCenterY(i-1,j)-1.0f/2*brick_->getHeight_()-ball_->getRadius_()};
                            vertexLine3={brick_->getCenterX(i-1,j)-1.0f/2*brick_->getWidth_()-ball_->getRadius_(),brick_->getCenterY(i-1,j)-1.0f/2*brick_->getHeight_()};
                            vertexLine4={brick_->getCenterX(i-1,j)-1.0f/2*brick_->getWidth_()-ball_->getRadius_(),brick_->getCenterY(i-1,j)};
                            corner     ={brick_->getCenterX(i-1,j)-1.0f/2*brick_->getWidth_(),brick_->getCenterY(i-1,j)-1.0f/2*brick_->getHeight_()};
                            if(enterBrick(brick_->getCenterX(i-1,j),brick_->getCenterY(i-1,j),ball_)){
                                if(sideIntersectSide(posBall1, posBall2, vertexLine1, vertexLine2))
                                {     //下边儿

                                    ball_->ballCollide(3.0/2*M_PI);
                                    brick_->brickHited(i-1,j);
                                    score_++;

                                }
                                else if(sideIntersectSide(posBall1, posBall2, vertexLine3, vertexLine4))
                                {   //坐边儿
                                    ball_->ballCollide(M_PI);
                                    brick_->brickHited(i-1,j);
                                    score_++;
                                }
                                else if(touchCorner(corner,ball_))
                                {   // 角
                                     //ball_->ballCollide(atan2(ball_->getY_()-corner.y,ball_->getX_()-corner.x));
                                     ball_->ballCollide(-M_PI*3/4.0);
                                     brick_->brickHited(i-1,j);
                                     score_++;
                                }
                            }
                        }
                    }



        }
        if(i!=brick_->getLine_()){
           // i     下面儿的砖
                    if(j!=0){
                       // j-1   左面儿的砖
                        if(brick_->getValofB(i,j-1))
                        {         //砖块是否存在
                            vertexLine1={brick_->getCenterX(i,j-1),brick_->getCenterY(i,j-1)+1.0f/2*brick_->getHeight_()+ball_->getRadius_()};
                            vertexLine2={brick_->getCenterX(i,j-1)+1.0f/2*brick_->getWidth_(),brick_->getCenterY(i,j-1)+1.0f/2*brick_->getHeight_()+ball_->getRadius_()};
                            vertexLine3={brick_->getCenterX(i,j-1)+1.0f/2*brick_->getWidth_()+ball_->getRadius_(),brick_->getCenterY(i,j-1)+1.0f/2*brick_->getHeight_()};
                            vertexLine4={brick_->getCenterX(i,j-1)+1.0f/2*brick_->getWidth_()+ball_->getRadius_(),brick_->getCenterY(i,j-1)};
                            corner     ={brick_->getCenterX(i,j-1)+1.0f/2*brick_->getWidth_(),brick_->getCenterY(i,j-1)+1.0f/2*brick_->getHeight_()};

                            if(enterBrick(brick_->getCenterX(i,j-1),brick_->getCenterY(i,j-1),ball_)){
                                if(sideIntersectSide(posBall1, posBall2, vertexLine1, vertexLine2))
                                {     //上边儿

                                    ball_->ballCollide(1.0/2*M_PI);
                                    brick_->brickHited(i,j-1);
                                    score_++;

                                }
                                else if(sideIntersectSide(posBall1, posBall2, vertexLine3, vertexLine4))
                                {   //右边儿
                                    ball_->ballCollide(0.0);
                                    brick_->brickHited(i,j-1);
                                    score_++;
                                }
                                else if(touchCorner(corner,ball_))
                                {   // 角
                                     //ball_->ballCollide(atan2(ball_->getY_()-corner.y,ball_->getX_()-corner.x));
                                     ball_->ballCollide(M_PI/4.0);
                                     brick_->brickHited(i,j-1);
                                     score_++;
                                }
                            }
                        }
                    }
                    if(j!=brick_->getColumn_()){
                       // j     右面儿的砖
                        if(brick_->getValofB(i,j))
                        {         //砖块是否存在
                            vertexLine1={brick_->getCenterX(i,j),brick_->getCenterY(i,j)+1.0f/2*brick_->getHeight_()+ball_->getRadius_()};
                            vertexLine2={brick_->getCenterX(i,j)-1.0f/2*brick_->getWidth_(),brick_->getCenterY(i,j)+1.0f/2*brick_->getHeight_()+ball_->getRadius_()};
                            vertexLine3={brick_->getCenterX(i,j)-1.0f/2*brick_->getWidth_()-ball_->getRadius_(),brick_->getCenterY(i,j)+1.0f/2*brick_->getHeight_()};
                            vertexLine4={brick_->getCenterX(i,j)-1.0f/2*brick_->getWidth_()-ball_->getRadius_(),brick_->getCenterY(i,j)};
                            corner     ={brick_->getCenterX(i,j)-1.0f/2*brick_->getWidth_(),brick_->getCenterY(i,j)+1.0f/2*brick_->getHeight_()};
                            if(enterBrick(brick_->getCenterX(i,j),brick_->getCenterY(i,j),ball_)){
                                if(sideIntersectSide(posBall1, posBall2, vertexLine1, vertexLine2))
                                {     //上边儿

                                    ball_->ballCollide(1.0/2*M_PI);
                                    brick_->brickHited(i,j);
                                    score_++;

                                }
                                else if(sideIntersectSide(posBall1, posBall2, vertexLine3, vertexLine4))
                                {   //左边儿
                                    ball_->ballCollide(M_PI);
                                    brick_->brickHited(i,j);
                                    score_++;
                                }
                                else if(touchCorner(corner,ball_))
                                {   // 角
                                     //ball_->ballCollide(atan2(ball_->getY_()-corner.y,ball_->getX_()-corner.x));
                                     ball_->ballCollide(M_PI*3.0/4.0);
                                     brick_->brickHited(i,j);
                                     score_++;
                                }
                            }
                        }
                    }
        }
    }
}

bool Game::isWin()
{
    if (brick_->brickLeft()==0)
        return true;
    else
        return false;
}

void Game::lostOneBall()
{
    NumberOfBall_--;
    resetBall();
}

bool Game::isLose()
{
    if(NumberOfBall_==0)
        return true;
    else
        return false;
}

void Game::resetBall()
{
    ball_->setPos(platform_->getX_()+(platform_->getWidth_())/2,platform_->getY_()+ball_->getRadius_(),0.0);
    ball_->setSpd(0.0);
    ball_->setDirection_(M_PI*1.5/2);
}

bool Game::isLostOneBall()
{
    if(ball_->getY_()<-28.0)
        return true;
    else
        return false;
}

void Game::setPlatform(float width)
{
    platform_->setWidth(width);
}

void Game::nextLevel()
{
    level_++;
    brick_->reset();
    resetBall();
}

int Game::getLevel()
{
    return level_;
}

int Game::getScore()
{
    return score_;
}
int Game::getNumberOfBall()
{
    return NumberOfBall_;
}

void Game::resetGame()
{
    saveRank();
    level_=1;
    NumberOfBall_=3;
    score_=0;
    platform_->setWidth(8.0);
    platform_->setPos(-15.0,-21.0);
    resetBall();
    brick_->reset();
}

void Game::saveRank()
{
    r_.addRank(name_,score_);
    ofstream os("C://Users//asus//Desktop//bureau//ST//smestre 8//info//ANG Di DU Pingjie//code//code//Scores.txt");
        if (!os.good())
        {
           cout<<"cant save!"<<endl;
        }
        r_.save(os);
        os.close();
}

void Game::setName(string name)
{
    name_=name;
}

void Game::loadRank()
{
    ifstream is("C://Users//asus//Desktop//bureau//ST//smestre 8//info//ANG Di DU Pingjie//code//code//Scores.txt");
            if (is.good())
            {
                r_.load(is);
                is.close();
            }
           // r_.clear();
}

void Game::clearRank()
{
    r_.clear();
}

Game::~Game(){
    delete ball_;
    delete brick_;
    delete wall_;
    delete platform_;
}
