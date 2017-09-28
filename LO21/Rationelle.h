#ifndef RATIONELLE_H_INCLUDED
#define RATIONELLE_H_INCLUDED

#include "Numerique.h"
#include "Entiere.h"

/**
\class Rationnelle
\brief Implémentation d'une littérale Rationnelle par 2 objets Entiere : un numérateur et un dénominateur. \n
**/

class Rationnelle: public Numerique{
    /*!
     * \brief Numérateur de l'objet Rationelle.
     */
    Entiere num;
    /*!
     * \brief Dénominateur de l'objet Rationnelle.
     */
    Entiere den;
public:
    /*!
     * \brief Constructeur de Rationnelle.
     *
     * Initialise Rationnelle par initialisation des attributs du numérateur et du dénominateur.
     * \param n - Initialise l'attribut num.
     * \param d - Initialise l'attribut den.
     */
    Rationnelle(int n, int d): num(n),den(d){
        if (den.getValeur()<0){
            num.setValeur(-num.getValeur());
            den.setValeur(-den.getValeur());
        }
    }
    /*!
     * \brief Destructeur de Rationelle.
     */
    ~Rationnelle(){}
    /*!
     * \brief Méthode pour afficher un Rationelle
     * \return Retourne une chaine de caractère composée du numérateur num et du deénominateur den.
     */
    std::string toString()const;
    /*!
     * \brief Accesseur de l'attribut num.
     * \return Retourne la valeur du numérateur.
     */
    double getValeur() const{ return num.getValeur();}
    /*!
     * \brief Accesseur de l'attribut den.
     * \return Retourne la valeur du dénominateur.
     */
    int getPartieReelleDen() const{ return den.getValeur();}
};

#endif // RATIONELLE_H_INCLUDED
