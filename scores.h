#ifndef SCORES_H
#define SCORES_H

#include <fstream>
#include <string>
using namespace std;
/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​regist the scores.  // YANG 
*
*/ 

class Scores
{
    string name_;
    int score_;

public:
    Scores(string, int);
    Scores();
    string getName();
    int getScore();
};

#endif // SCORES_H
