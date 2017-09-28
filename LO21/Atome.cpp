#include "Atome.hpp"

using namespace std;

const regex correcteSyntaxeAtome("[[:upper:]][[:upper:][:digit:]]*");
const regex sansMajuscule("[^[:upper:]].*");
const regex lettresMinuscule(".*[[:lower:]].*");

bool Atome::verifSyntaxe(){
    if(regex_match (nom, correcteSyntaxeAtome)){
        //verifie la syntaxe correcte d'un atome : majuscule et chiffre, avec premier caractère majuscule
        return true;
    }
    else if(regex_match (nom, sansMajuscule)){
        //verifie si la premiere lettre n'est pas une majuscule
        throw ComputerException("La première lettre d'un atome doit être une majuscule");
        return false;
    }
    else if(regex_match (nom, lettresMinuscule)){
        //verifie si une des lettres de l'atome est une minuscule
        throw ComputerException("Les minuscules sont interdites dans un atome");
        return false;
    }
    else {
        throw ComputerException("Vérifiez la syntaxe de l'atome");
        return false;
    }
}

string Atome::toString()const{
    stringstream f;
    f<<nom;
    return f.str();
}
