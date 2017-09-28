#include "Complexe.h"

string Complexe::toString()const{
    stringstream f;
    f<<reel.toString()<<"$"<<im.toString();
    return f.str();
}

bool Complexe::estVrai()const{
    if ((getPartieReelleNum()==0)&&(getPartieImNum()==0))
        return false;
    return true;
    }
