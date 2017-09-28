#ifndef LITTERALE_H_INCLUDED
#define LITTERALE_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <stack>
#include <regex>
#include <algorithm>
#include <math.h>
#include <queue>
#include <list>
#include <map>
#include <iterator>
#include <deque>

#include "ComputerException.h"

using namespace std;

/*!
 * \brief La classe abstraite Litterale est parente de la classe Numerique, Complexe, Atome and Programme.
 *
 * Declaration de tous les operateurs et methodes virtuelles.
 */
class Litterale {

public:
    /*!
     * \brief Constructeur de Litterale.
     */
    Litterale(){}
    /*!
     * \brief Destructeur virtuelle de Litterale.
     */
    virtual ~Litterale(){}
    void afficher(std::ostream& f= std::cout) const{f<<toString()<<"\n";}
    /*!
     * \brief Methode virtuelle pure qui doit etre defini dans les classes filles.
     *
     * Utilise pour afficher un Litterale comme un string.
     */
    virtual std::string toString() const=0;
    /*!
     * \brief Methode virtuelle utilise pour afficher un Litterale comme un string et specifiquement les Expression sans ''.
     */
    virtual std::string getExpression() const {return toString();}
    /*!
     * \brief Methode virtuelle pour acceder a la valeur du numerateur de la partie reel d'un Litterale.
     * \return Retourne la valeur du numerateur de la partie reel d'un Litterale.
     */    
    virtual double getPartieReelleNum() const{return 0;}
    /*!
     * \brief Methode virtuelle pour acceder a la valeur du denominateur de la partie reel d'un Litterale.
     * \return Retourne la valeur du denominateur de la partie reel d'un Litterale.
     */
    virtual int getPartieReelleDen() const{return 1;}
    /*!
     * \brief Methode virtuelle pour acceder a la valeur du numerateur de la partie imaginaire d'un Litterale.
     * \return Retourne la valeur du numerateur de la partie imaginaire d'un Litterale.
     */
    virtual double getPartieImNum() const{return 0;}
    /*!
     * \brief Methode virtuelle pour acceder a la valeur du denominateur de la partie imaginaire d'un Litterale.
     * \return Retourne la valeur du denominateur de la partie imaginaire d'un Litterale.
     */
    virtual int getPartieImDen() const{return 1;}
    /*!
    * \brief Methode pour acceder a la valeur de la partie reel d'un Litterale.
    * \return Retourne la valeur de la partie reel d'un Litterale.
    */
    double getPartieReelle() const{return (getPartieReelleNum()/getPartieReelleDen());}
    /*!
     * \brief Methode pour acceder a la valeur de la partie imaginaire d'un Litterale.
     * \return Retourne la valeur de la partie imaginaire d'un Litterale.
     */
    double getPartieIm() const{return (getPartieImNum()/getPartieImDen());}
    /*!
     * \brief  Methode virtuelle pure qui doit etre defini dans les classes filles.
     *
     * \return Retourne le resultat de la comparaison entre la valeur de l'object et la valeur 0.
     */
    virtual bool estVrai()const=0;
};

/*!
 * \brief Methode pour creer le bon objet Litterale selon les parametrs.e
 * \param pReelleNum - Valeur du numerateur de la partie reelle.
 * \param pReelleDen - Valeur du denominateur de la partie reelle
 * \param pImNum - Valeur du numerateur de la partie imaginaire.
 * \param pImDen - Valeur du denominateur de la partie imaginaire.
 * \return Retourne la reference vers un Litteral selon les parametres
 */
Litterale& bonType(double pReelleNum, double pReelleDen=1, double pImNum=0, double pImDen=1);
/*!
 * \brief Methode pour additionner deux Litterale objets.
 * \param l1 - Litterale reference à additionner.
 * \param l2 - Litterale reference à additionner.
 * \return Retourne l'addition de ces deux Litterale objets.
 */
Litterale& operator+(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour soustraire deux Litterale objets.
 * \param l1 - Litterale reference à soustraire.
 * \param l2 - Litterale reference à soustraire.
 * \return Retourne la soustraction de ces deux Litterale objets.
 */
Litterale& operator-(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour multiplier deux Litterale objets.
 * \param l1 - Litterale reference à multiplier.
 * \param l2 - Litterale referenceà multiplier.
 * \return Retourne la multiplication de ces deux Litterale objets.
 */
Litterale& operator*(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour diviser deux Litterale objets.
 * \param l1 - Litterale reference à diviser.
 * \param l2 - Litterale reference à diviser.
 * \return Retourne la division de ces deux Litterale objets.
 */
Litterale& operator/(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour creer un Complexe avec deux Litterale objets.
 * \param l1 - Litterale reference de la partie reelle du Complexe.
 * \param l2 - Litterale reference de la partie imagianaire du Complexe.
 * \return Retourne la bonne Litterale reference selon les parametres.
 */
Litterale& $(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour mettre à la puissance deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne la puissance de ces deux Litterale objets.
 */
Litterale& POW(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour donner l'oppose d'une Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'opposé d'une Litterale object.
 */
Litterale& NEG(Litterale& l);
/*!
 * \brief Methode pour calculer le sinus d'une Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le sinus d'un Litterale objet.
 */
Litterale& SIN(Litterale& l);
/*!
 * \brief Methode pour calculer le cosinus d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le consinus d'un Litterale objet.
 */
Litterale& COS(Litterale& l);
/*!
 * \brief Methode pour calculer la tangente d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne la tangente d'un Litterale objet.
 */
Litterale& TAN(Litterale& l);
/*!
 * \brief Methode pour calculer l'arcsinus d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'arcsinus d'un Litterale objet.
 */
Litterale& ARCSIN(Litterale& l);
/*!
 * \brief Methode pour calculer l'arctangente d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'arctangente d'un Litterale objet.
 */
Litterale& ARCTAN(Litterale& l);
/*!
 * \brief Methode pour calculer l'arccosinus d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'arccosinus d'un Litterale objet.
 */
Litterale& ARCCOS(Litterale& l);
/*!
 * \brief Methode pour calculer l'exponentielle d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'exponentielle d'un Litterale objet.
 */
Litterale& EXP(Litterale& l);
/*!
 * \brief Methode pour calculer le logarithme d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le logarithme d'un Litterale objet.
 */
Litterale& LN(Litterale& l);
/*!
 * \brief Methode pour calculer la racine d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne la racine d'un Litterale objet.
 */
Litterale& SQRT(Litterale& l);
/*!
 * \brief Methode pour acceder au numerateur d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le numerateur d'un Litterale objet.
 */
Litterale& NUM(Litterale& l);
/*!
 * \brief Methode pour acceder au denominateur d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le denominateur d'un Litterale objet.
 */
Litterale& DEN(Litterale& l);
/*!
 * \brief Methode pour acceder à la partie reelle d'un Litterale objets.
 * \param l - Litterale reference.
 * \return Retourne la partie reelle d'un Litterale objet.
 */
Litterale& RE(Litterale& l);
/*!
 * \brief Methode pour acceder a la partie imaginaire d'un Litterale objets.
 * \param l - Litterale reference.
 * \return Retourne la partie imaginaire d'un Litterale objet.
 */
Litterale& IM(Litterale& l);
/*!
 * \brief Methode pour calculer le module d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne le module d'un Litterale objet.
 */
Litterale& NORM(Litterale& l);
/*!
 * \brief Methode pour calculer l'argument d'un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne l'argument d'un Litterale objet.
 */
Litterale& ARG(Litterale& l);
/*!
 * \brief Methode pour calculer la partie entiere de la division de deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne la partie entiere de la division de deux Litterale objets.
 */
Litterale& DIV(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour calculer le reste de la division de deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne le reste de la division de deux Litterale objets.
 */
Litterale& MOD(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour comparer avec operateur different deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& operator!=(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour comparer avec operateur < deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& operator<(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour comparer avec l'operateur > deux Litterale objects.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& operator>(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour faire un and logique avec deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& AND(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour faire un or logique avec deux Litterale objets.
 * \param l1 - Litterale reference.
 * \param l2 - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& OR(Litterale& l1, Litterale& l2);
/*!
 * \brief Methode pour faire un not logique avec un Litterale objet.
 * \param l - Litterale reference.
 * \return Retourne une Litterale reference selon le resultat de la comparaison : Entiere(1) si true, Entiere(0) sinon.
 */
Litterale& NOT(Litterale& l);
/*!
 * \brief Methode pour evaluer un Litterale objet.
 * \param l - Litterale reference qui sera evalué.
 */
void EVAL(Litterale&);
/*!
 * \brief Methode pour stocker un Litterale objet avec son identificateur.
 * \param l1 - Litterale reference qui sera stocker.
 * \param l2 - Litterale reference qui servira d'identificateur pour l1.
 */
void STO(Litterale&,Litterale&);
/*!
 * \brief Map avec tous les operateurs arithmetiques et leurs priorités.
 */
static std::map<string, int> operateurs_arithmetiques = {{ "+", 2 },{ "-", 2 },{ "*", 3 },{ "/", 3 }, {"$",4}};
/*!
 * \brief Map avec toutes les fonctions unaires.
 * Utilisé pour affecter la bonne fonction selon la valeur dans la ligne de commande et stocker les identificateurs reservés.
 */
typedef Litterale& (*FnPtrUn)(Litterale&);
static std::map<string, FnPtrUn> fonctions_unaires = {
    {"NEG", NEG},
    {"SIN", SIN},
    {"COS", COS},
    {"TAN", TAN},
    {"ARCSIN", ARCSIN},
    {"ARCTAN", ARCTAN},
    {"ARCCOS", ARCCOS},
    {"EXP", EXP},
    {"LN", LN},
    {"NUM", NUM},
    {"DEN", DEN},
    {"RE", RE},
    {"IM", IM},
    {"NORM", NORM},
    {"ARG", ARG},
    {"SQRT",SQRT},
    {"NOT",NOT}
};
/*!
 * \brief Map avec toutes les fonctions binaires.
 * Utilisé pour affecter la bonne fonction selon la valeur dans la ligne de commande et stocker les identificateurs reservés.
 */
typedef Litterale& (*FnPtrBin)(Litterale&, Litterale&);
static std::map<string, FnPtrBin> fonctions_binaires ={{"POW", POW}, {"AND", AND}, {"OR", OR}, {"MOD",MOD},{"DIV",DIV}};
/*!
 * \brief Map avec toutes lesfonctions unaires predefinies.
 * Utilisé pour affecter la bonne fonction selon la valeur dans la ligne de commande et stocker les identificateurs reservés.
 */
typedef void (*FnPtrUnPre)(Litterale&);
static std::map<string, FnPtrUnPre> fonctions_pre_unaires ={{"EVAL", EVAL}};
/*!
 * \brief Map avec toutes les fonctions binaires predefinies.
 * Utilisé pour affecter la bonne fonction selon la valeur dans la ligne de commande et stocker les identificateurs reservés.
 */
typedef void (*FnPtrBinPre)(Litterale&, Litterale&);
static std::map<string, FnPtrBinPre> fonctions_pre_binaires ={{"STO",STO}};
/*!
 * \brief Liste avec tous les operateurs de Pile.
 * Utilisé pour stocker les identificateurs reservés.
 */
static std::list<string> fonctions_pile ={"REDO", "UNDO","CLEAR","SWAP", "IFT", "WHILE","IFTE", "DUP", "DROP", "lastOp", "lastArgS", "FORGET"};
/*!
 * \brief Methode pour verifier si le parametre est connu comme fonction.
 * \param caractere - string qui sera comparé avec tous les noms de fonction.
 * \return Retourne true si la fonction est connu, faux sinon.
 */
bool EstFonction(string caractere);
/*!
 * \brief Methode pour verifier si le parametre est connu comme operateur.
 * \param chaine - string qui sera comparé avec tous les noms d'operateur.
 * \return Retourne true si l'operator est connu, faux sinon.
 */
bool EstOperateur(string chaine);
/*!
 * \brief Methode pour verifier si le parametre est connu comme operateur.
 * \param c - char qui sera comparé avec tous les noms d'operateur.
 * \return Retourne true si l'operator est connu, faux sinon.
 */
bool EstOperateur(char c);
/*!
 * \brief Methode pour verifier si le parametre est un Entiere.
 * \param s - string qui sera évalué.
 * \return Retourne true si interpretable comme un entier, faux sinon.
 */
bool EstEntier(string s);
/*!
 * \brief Methode pour verifier si le parametre est un Numerique.
 * \param c - char qui sera évalué.
 * \return Retourne true si interpretable comme un Numerique, faux sinon.
 */
bool EstNumerique(char c);
/*!
 * \brief Methode pour verifier si le parametre est un Numerique.
 * \param string - s qui sera évalué.
 * \return Retourne true si interpretable comme un Numerique, faux sinon.
 */
bool EstNumerique(string s);

#endif // LITTERALE_H_INCLUDED
