#include "Reelle.h"

std::string Reelle::toString()const{
    std::stringstream f;
    f<<valeur;
    return f.str();
}
