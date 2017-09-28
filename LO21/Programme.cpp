#include "Programme.hpp"

/****** REGEX PROGRAMME *****/
const regex lettresMinuscule(".*[[:lower:]].*");
const regex legalCar(".*([[:alnum:]]|[,.$ ()+*\\[\\]]/-)+.*");

bool Programme::verifSyntaxe()const{

    if(regex_match (contenu, lettresMinuscule)){//match des atomes avec syntaxe interdite dans le programme
        throw ComputerException("Opérandes interdites dans programme : pas de minuscules");
        return false;
    }
    else if(regex_match (contenu, legalCar)){
        return true;

    }
    else {
        throw ComputerException("Opérandes interdites dans programme");
        return false;
    }

}

std::string Programme::toString()const{//TO DO remplacer toutes les tabs et newline en espace
    stringstream f;
    std::string str(this->contenu);
    str.erase( std::remove(str.begin(), str.end(), '\t' ), str.end() ) ;
    str.erase( std::remove(str.begin(), str.end(), '\n' ), str.end() ) ;
    f<< "[ " << str << " ]";
    return f.str();
}
