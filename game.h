#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "brick.h"
#include "platform.h"
#include "wall.h"
#include "rank.h"
/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​control the process of the game.  // YANG et DU
*
*/ 

using namespace std;

typedef struct point// definition of a struct Point
{
    float x;
    float y;
}Point;

class Game
{
private:
    Ball* ball_;
    Brick* brick_;
    Platform* platform_;
    Wall* wall_;

    int NumberOfBall_;// number of the ball left. (0,1,2,3)
    int level_;// the level of the game
    int score_;// the point got by player
    string name_;// the name of the player
    Rank r_;// the rank of all players(a vector of Socre(name, score))

public:
    Game();//contructor
    void afficher() const;//display the objects in the GLWidget
    void displayWall() const;// display the wall
    void update();//update to the next stats of the process of the game
	//getters
    Platform* getPlatform_();
    Ball* getBall_();
    void collide();
    int getLevel();
    int getScore();
    int getNumberOfBall();
	
	//some methodes for distinguish or control the process of the game
    bool isWin();
    bool isLostOneBall();
    void lostOneBall();
    bool isLose();
    void resetBall();//put the ball on the platform
    void setPlatform(float width);
    void nextLevel();
    void resetGame();
    void saveRank();//save the rank
    void loadRank();
    void setName(string name);
    void clearRank();
    ~Game();//destructor
};

#endif // BRICK_H
