#ifndef NUMERIQUE_H_INCLUDED
#define NUMERIQUE_H_INCLUDED

#include "Litterale.hpp"

/*!
 * \brief La classe abstraite Numerique est la classe mère de Reelle, Rationnelle et Entiere.
 *
 * Cette class déclare tous les opérateurs virtuels ainsi que la méthode toString().
 */
class Numerique : public Litterale{

public:
    /*!
     * \brief Constructeur de Numerique.
     */
    Numerique(){}
    /*!
     * \brief Destructeur virtuel de Numerique.
     */
    virtual ~Numerique(){}
    /*!
     * \brief Méthode virtuelle pure définie dans les classes filles.
     *
     * Elle est utilisé pour afficher n'importe quel Numerique sous forme de chaine de caractère.
     */
    virtual std::string toString() const=0;
    /*!
     * \brief Accesseur du numérateur d'un objet Numerique.
     * \return Retourne la valeur du numérateur d'un Numerique.
     */
    double getPartieReelleNum() const{ return getValeur();}
    /*!
     * \brief  Méthode virtuelle pure définie dans les classes filles.
     * \return Retourne la valeur exacte d'un objet Numerique.
     */
    virtual double getValeur() const=0;

    /*!
     * \brief  Fonction qui compare la valeur d'un Numerique à la valeur zero.
     * \return Retourne faux si la valeur du Numerique est différente de zero.
     */
    bool estVrai()const {return getValeur()!=0;}
};

#endif // NUMERIQUE_H_INCLUDED
