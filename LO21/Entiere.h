#ifndef ENTIERE_H_INCLUDED
#define ENTIERE_H_INCLUDED

#include "Numerique.h"

/*!
 * \brief La classe Entiere represente un entier. Elle possede un attribut de type entier.
 */
class Entiere: public Numerique{
    /*!
     * \brief Valeur de l'objet Entiere.
     */
    int valeur;
public:
    /*!
     * \brief Constructeur d'un Entier.
     * \param v - Initialise la valeur de l'attribut.
     */
    Entiere(int v=0):valeur(v){}
    /*!
     * \brief Destructeur d'Entiere.
     */
    ~Entiere(){}
    /*!
     * \brief Affecte à l'objet Entiere une nouvelle valeur.
     * \param v - nouvelle valeur de l'attribut.
     */
    void setValeur(int v){valeur=v;}
    /*!
     * \brief Methode utilisé pour afficher la valeur de l'attribut.
     * \return Retourne un string contenant la valeur de l'attribut.
     */
    std::string toString()const;
    /*!
     * \brief Acceseur pour l'attribut de l'objet Entiere.
     * \return Retourne la valeur de l'attribut.
     */
    double getValeur() const{ return valeur;}
};

#endif // ENTIERE_H_INCLUDED
