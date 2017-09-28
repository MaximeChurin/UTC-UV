#ifndef Atome_hpp
#define Atome_hpp

#include "Litterale.hpp"

/**
\class Atome
\brief Implémentation d'une littérale Atome (identificateur de Litteral) \n
**/
class Atome: public Litterale{
    string nom;
public:
    //! \brief Constructeur d'Atome : affecter le nom de l'atome
    explicit Atome(const string& nom):nom(nom){}
    //! \brief Accessseur pour l'attribut nom d'Atome.
    //! \return Retourne la valeur de l'attribut d'Atome.
    string getNom()const{return nom;}
    //! \brief retourne vrai si la syntaxe du nom correspond à celle définie pour un atome
    bool verifSyntaxe();
    //! \brief Méthode de pour afficher un Litterale Programme
    string toString()const;
    bool estVrai()const{return true;}
};

#endif /* Atome_hpp */
