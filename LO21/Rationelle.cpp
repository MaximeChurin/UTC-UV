#include "Rationelle.h"

std::string Rationnelle::toString()const{
    std::stringstream f;
    f<<num.getValeur()<<"/"<<den.getValeur();
    return f.str();
}
