#ifndef Pile_hpp
#define Pile_hpp

#include "LitteraleManager.h"
#include <QObject>

/**
\class Memento
\brief Implémentation du desgin pattern Memento pour restaurer un état précédent de la pile \n
**/
class Memento{
    /*!
     * \brief Liste des états de la pile qui ont été sauvegardés.
     */
     std::deque<Litterale*> etatPile;
public:
     /*!
      * \brief Constructeur du Memento.
      *
      * Initialise l'objet Memento par initialisation de la liste des états.
      * \param s - Initialise l'attribut etat.
      */
    Memento(std::deque<Litterale*> p):etatPile(p){}
    /*!
    * \brief Accesseur pour l'attribut etatPile.
    * \return Retourne la liste de tous les états sauvegardés de la pile.
    */
    std::deque<Litterale*> getEtatPile() {return etatPile;}
};

class Pile :  public QObject {
    Q_OBJECT
    /*!
     * \brief Déclaration de Memento comme classe amie.
     *
     *  Déclaration qui permet l'usage des méthodes de Memento à l'intérieur de la classe Pile
     */
    friend class Memento;
    /*!
     * \brief Récupération de l'instance Pile existante.
     *
     * Implémentation du design pattern Singleton.
     */
    static Pile* instance;
    /*!
     * \brief Pile d'objets Litterale.
     */
    std::deque<Litterale*> pile;
    /*!
     * \brief Message destiné à l'affichage dans la Mainwindow.
     */
    QString message;
    /*!
     * \brief Nombre maximum d'objets affichés par la Pile.
     */
    unsigned int maxAffiche;
    /*!
     * \brief Dernier opérateur utilisé.
     */
    std::string lastOp;
    /*!
     * \brief L'un des derniers arguments utilisés par la calculatrice.
     *
     * Cet argument est toujours utilisé pour stocker le dernier argument dépilé par un opérateur unaire, binaire ou ternaire.
     */
    Litterale* lastArg1;
    /*!
     * \brief L'un des derniers arguments utilisés par la calculatrice.
     *
     * Cet argument est uniquement utilisé pour stocker le dernier argument dépilé par un opérateur binaire ou ternaire.
     */
    Litterale* lastArg2;
    /*!
     * \brief L'un des derniers arguments utilisés par la calculatrice.
     *
     * Cet argument est uniquement utilisé pour stocker le dernier argument dépilé par un opérateur ternaire.
     */
    Litterale* lastArg3;
    /*!
     * \brief Constructeur de Pile.
     */
    Pile();
    /*!
     * \brief Destructeur de Pile.
     */
    ~Pile();
    /*!
     * \brief Surcharge de l'opérateur d'affectation =.
     */
    Pile& operator=(const Pile&) = delete;
    /*!
     * \brief Constructeur de recopie.
     */
    Pile (const Pile&) = delete;
  public:
    /*!
     * \brief Accesseur de l'attribut instance.
     * \return Retourne une référence vers l'unique instance d'objet Pile.
     */
    static Pile& getInstance();
    /*!
    * \brief Libere le pointeur vers l'unique instance d'objet Pile.
    */
    static void libererInstance();
    /*!
     * \brief Affecte la dernière opération à l'attribut dernierOp.
     */
    void setlastOp(const string& s){lastOp=s;}
    /*!
     * \brief Accesseur de l'attribut lastOp.
     * \return Retourne une chaine de caractere composée de l'attribut lastOp.
     */
    string getlastOp()const{return lastOp;}
    /*!
     * \brief Affecte un pointeur vers un objet Litterale à l'attribut lastArg1 représentant l'un des derniers arguments utilisés pour une opération.
     */
    void setlastArg1(Litterale* l){lastArg1=l;}
    /*!
     * \brief Affecte un pointeur vers un objet Litterale à l'attribut lastArg2 représentant l'un des derniers arguments utilisés pour une opération.
     */
    void setlastArg2(Litterale* l){lastArg2=l;}
    /*!
     * \brief Affecte un pointeur vers un objet Litterale à l'attribut lastArg3 représentant l'un des derniers arguments utilisés pour une opération.
     */
    void setlastArg3(Litterale* l){lastArg3=l;}
    /*!
     * \brief Accesseur de l'attribut lastArg1.
     * \return Retourne un pointeur vers un objet Litterale.
     */
    Litterale* getlastArg1()const{return lastArg1;}
    /*!
     * \brief Accesseur de l'attribut lastArg1.
     * \return Retourne un pointeur vers un objet Litterale.
     */
    Litterale* getlastArg2()const{return lastArg2;}
    /*!
     * \brief Accesseur de l'attribut lastArg1.
     * \return Retourne un pointeur vers un objet Litterale.
     */
    Litterale* getlastArg3()const{return lastArg3;}
    /*!
     * \brief Accesseur de l'attribut message.
     * \return Retourne une chaine de caractère composée du message.
     */
    QString getMessage() const;
    /*!
     * \brief Affecte une chaine de caractère à l'attribut message.
     */
    void setMessage(const QString& msg);
    /*!
     * \brief Accesseur de l'attribut MaxAffiche.
     * \return Retourne le nombre d'objets Litterale affichés au maximum par la Pile.
     */
    unsigned int getMaxAffiche() const;
    /*!
     * \brief Affecte un nombre à l'attribut MaxAffiche.
     */
    void setMaxAffiche(unsigned int);
    /*!
     * \brief  Donne le nombre d'éléments actuellement empilés.
     * \return Retourne le nombre d'objets Litterale présents dans la Pile.
     */
    unsigned int getTaille() const;
    /*!
     * \brief Annonce si la Pile est vide.
     * \return Retourne vrai si aucun élément n'est empilé sur la Pile.
     */
    bool estVide();
    /*!
     * \brief Empile un objet Litterale au sommet de la Pile.
     */
    void push(Litterale& l);
    /*!
     * \brief Dépile l'objet Litterale placé au sommet de la Pile.
     */
    void pop();
    /*!
     * \brief Récupère l'objet Litterale présent au sommet  de la Pile.
     * \return Retourne une référence sur l'objet Litterale en haut de la Pile.
     */
    Litterale& top() const;
    /*!
     * \brief Place un itérateur constant sur le sommet de la Pile.
     * \return Retourne un itérateur constant sur le premier élément de la Pile.
     */
    std::deque<Litterale*>::const_iterator getIteratorBegin() const;
    /*!
     * \brief Place un itérateur constant sur le dernier élément de la Pile.
     * \return Retourne un itérateur constant sur le dernier élément de la Pile.
     */
    std::deque<Litterale*>::const_iterator getIteratorEnd() const;
    /*!
     * \brief Sauvegarde l'état de la Pile par la création d'un objet Memento.
     * \return Retourne un pointeur vers l'objet Memento qui gère les états de la Pile.
     */
    Memento* SavePile(){return new Memento(pile);}
    /*!
     * \brief Empile un nouveal objet Litterale identique à celui du sommet de la Pile.
     */
    void dup();
    /*!
     * \brief Dépile l'objet Litterale au sommet de la Pile.
     */
    void drop();
    /*!
     * \brief Intervertit les deux derniers éléments empilés dans la Pile.
     */
    void swap();
    /*!
     * \brief Applique le dernier opérateur utilisé.
     */
    void lastop();
    /*!
     * \brief Empile les objets Litterale utilisées pour la dernière opération.
     */
    void lastArgs();
    /*!
     * \brief Vide tous les éléments de la Pile.
     */
    void clear(){pile.clear();}
    /*!
     * \brief Rétablit un état précédent de la Pile.
     * \param mem - Pointeur sur un objet Memento.
     */
    void reinstateMemento(Memento* mem);
    /*!
     * \brief Exécution conditionnelle.
     *
     * Si la valeur de ce test est vrai, le 2e argument est évalué sinon il est abandonné.
     */
    void IFT();
    /*!
     * \brief Exécution conditionnelle.
     *
     * Le dernier argument dépilé est un test logique. Si la valeur de ce test est vrai, le 2e argument est évalué et le 3e argument est abandonné
     * sinon le 3e argument est évalué et le 2e argument est abandonné.
     */
    void IFTE();
    /*!
     * \brief Exécution conditionnelle.
     *
     * Le 1er (i.e. le dernier dépilé) est un test logique. Tant que le test est vrai, le deuxième argument est évalué.
     */
    void While();
    /*!
     * \brief Efface la variable ou le programme associé à l'atome proposé en argument.
     * \param str - Chaine de caractère correspondant à l'atome.
     */
    void FORGET(std::string str);

  signals:
    /*!
     * \brief Envoie un signal lors de la modification de l'état de la Pile.
     */
    void modificationEtat();
    void atomeAdded();
    void atomeRemoved();
};

#endif
