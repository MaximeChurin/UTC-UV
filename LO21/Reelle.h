#ifndef REELLE_H_INCLUDED
#define REELLE_H_INCLUDED

#include "Numerique.h"

/**
\class Reelle
\brief Implémentation d'une littérale Reelle. \n
**/
class Reelle: public Numerique{    
    /*!
     * \brief Valeur de l'objet Reelle
     */
    double valeur;
public:
    /*!
     * \brief Constructeur de Reelle
     * \param v - initialise la valeur de l'attribut valeur.
     */
    explicit Reelle(double v): valeur(v){}    
    /*!
     * \brief Destructeur de Reelle
     */
    ~Reelle(){}
    /*!
     * \brief Accesseur pour l'attribut valeur
     * \return Retourne la valeur de l'attribut
     */
    double getValeur()const{return valeur;}
    /*!
     * \brief Méthode pour afficher un Reelle
     * \return Retourne une chaine de caractère composée de l'attribut valeur.
     */
    string toString()const;
};

#endif // REELLE_H_INCLUDED
