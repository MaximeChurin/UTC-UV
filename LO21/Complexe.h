#ifndef COMPLEXE_H_INCLUDED
#define COMPLEXE_H_INCLUDED

#include "Numerique.h"

/*!
 * \brief La classe Complexe represente un complexe. Elle utilise 2 objets de type Numerique.
 */
class Complexe : public Litterale{
    /*!
     * \brief Partie reelle de l'objet Complexe.
     *
     * Reference vers un objet Numerique.
     */
    Numerique& reel;
    /*!
     * \brief Partie imaginaire de l'objet Complexe.
     *
     * Reference vers un objet Numerique.
     */
    Numerique& im;
public:
    /*!
     * \brief Constructeur de Complexe.
     *
     * Affecte au Complexe sa partie reelle et sa partie imaginaire.
     * \param r - Initialise la partie reelle.
     * \param i - Initialise la partie imaginaire.
     */
    Complexe(Numerique& r, Numerique& i) : reel(r),im(i){}
    /*!
     * \brief Destructeur de Complexe
     */
    ~Complexe(){}
    /*!
     * \brief Methode utilisé pour afficher un Complexe.
     * \return Retourne un string composé de la partie reelle et imaginaire.
     */
    std::string toString()const;
    /*!
     * \brief Accesseur pour le numerateur de la partie reelle.
     * \return Retourne la valeur du dit attribut.
     */
    double getPartieReelleNum() const{ return reel.getPartieReelleNum();}
    /*!
     * \brief Accesseur pour le denominateur de la partie reelle.
     * \return Retourne la valeur du dit attribut.
     */
    int getPartieReelleDen() const{return reel.getPartieReelleDen();}
    /*!
     * \brief Accesseur pour le numerateur de la partie imaginaire.
     * \return Retourne la valeur du dit attribut.
     */
    double getPartieImNum() const{return im.getPartieReelleNum();}
    /*!
     * \brief Accesseur pour le denominateur de la partie imaginaire.
     * \return Retourne la valeur du dit attribut.
     */
    int getPartieImDen() const{return im.getPartieReelleDen();}
    /*!
     * \brief  Fonction qui compare la valeur de la partie reelle avec la valeur 0 et la valeur de la partie imaginaire avec la valeur 0.
     * \return Retourne faux si egaux a 0, vrai sinon.
     */
    bool estVrai()const;
};

#endif // COMPLEXE_H_INCLUDED
