#include "rank.h"

Rank::Rank()
{

}

void Rank::load(ifstream &is)
{
    int n;
    int val;
    string name;

    clear();
    is>>n;
    for (int i=0; i<n; i++)
    {
        is>>val;
        is>>name;
        push_back(Scores(name, val));
    }
}

void Rank::save(ofstream &os)
{
    os<<size()<<endl;
    for (int i=0; i<(int) size(); i++) {
        os<<at(i).getScore()<<endl;
        os<<at(i).getName()<<endl;
    }
}

void Rank::addRank(string name, int score)
{
    Scores s(name,score);
    push_back(s);
    for(int i = 0;i <(int) size();i++){
            for(int j = 0;j <(int) size()-i-1;j++){
                if(at(j).getScore() < at(j+1).getScore()){
                    Scores t = at(j);
                    at(j) = at(j+1);
                    at(j+1) = t;
                }
            }
    }
}
