#include "scores.h"

using namespace std;

Scores::Scores(string name, int score)
{
    name_=name;
    score_=score;
}

Scores::Scores()
{
    name_="";
    score_=0;
}

int Scores::getScore()
{
    return score_;
}

string Scores::getName()
{
    return name_;
}
