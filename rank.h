#ifndef RANK_H
#define RANK_H
#include<vector>
#include"scores.h"
/* 
*This​ ​class​ ​is​ ​used​ ​to​ ​put the score into rank // YANG
*
*/ 

class Rank: public vector<Scores>
{
public:
    Rank();
    void load(ifstream &is);
    void save(ofstream &os);
    void addRank(string name, int score);
};

#endif // RANK_H
