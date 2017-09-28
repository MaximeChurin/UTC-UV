#ifndef LITTERALEMANAGER_H
#define LITTERALEMANAGER_H

#include "Litterale.hpp"

/**
\class LiteraleManager
\brief La classe LitteraleManager implémente de la gestion des objets Litterale
**/

class LitteraleManager {// pattern singleton
    /*!
     * \brief Tableau de pointeurs de Litterale.
     */
    Litterale** lits;
    /*!
     * \brief Nombre d'objets Litterale stockés dans le LitteraleManager.
     */
    unsigned int nb;
    /*!
     * \brief Nombre maximum d'objets Litterale pouvant être stockés dans le LitteraleManager.
     */
    unsigned int nbMax;
    /*!
     * \brief Méthode permettant l'aggrandissement de la capacité de stockage dans le LitteraleManager.
     *
     * L'utilisateur ne doit pas pouvoir accéder cette méthode qui est donc placée dans la partie privée de LitteraleManager
     */
    void agrandissementCapacite();
    /*!
     * \brief Constructeur de LitteraleManager.
     *
     * Le design pattern Singleton impose de mettre le constructeur en privé
     */
    LitteraleManager():lits(0),nb(0),nbMax(0){}
    /*!
     * \brief Destructeur de LitteraleManager
     */
    ~LitteraleManager();
    /*!
     * \brief Constructeur de recopie de LitteraleManager
     *
     * Le design pattern Singleton impose de mettre le constructeur de recopie en privé
     */
    LitteraleManager(const LitteraleManager& m);
    /*!
     * \brief Surcharge de l'opérateur d'affectation =
     *
     * Le design pattern Singleton impose de mettre l'opérateur d'affectation en privé
     */
    LitteraleManager& operator=(const LitteraleManager& m);
    /*!
     * \brief Implémentation du desing pattern Singleton
     *
     * Le Handler impose l'unicité de l'instance de LitteraleManager
     */
    struct Handler{
        LitteraleManager* instance;
        Handler():instance(0){}
        ~Handler(){ delete instance; }
    };
    /*!
     * \brief Déclaration d'un attribut d'une structure Handler
     */
    static Handler handler;
public:
    /*!
     * \brief Méthode qui ajoute un objet Litterale dans le LitteraleManager
     * \param lit - Pointeur vers le Litterale à ajouter.
     */
    Litterale& ajoutLitterale(Litterale* lit);
    /*!
     * \brief Méthode qui supprime un objet Litterale du LitteraleManager
     * \param e - Pointeur vers le Litterale à supprimer.
     */
    void enleveLitterale(Litterale& e);
    /*!
     * \brief Accesseur de l'attribut nb
     */
    unsigned int getNb(){return nb;}
    /*!
     * \brief Méthode qui permet de récupérer l'instance unique de LitteraleManager
     * \return Retourne une référence vers l'unique instance d'objet LitteraleManager.
     */
    static LitteraleManager& getInstance();
    /*!
    * \brief Libere le pointeur vers l'unique instance d'objet LitteraleManager.
    */
    static void libererInstance();
    /**
    \class iterator
    \brief Implémentation du design pattern iterator
    **/
    class iterator {
        /*!
         * \brief Iterateur courant de iterator
         *
         * Pointeur vers un pointeur d'objet Litterale
         */
        Litterale** current;
        /*!
         * \brief Constructeur de recopie de iterator
         *
         * Initialise l'itérateur courant sur le Litterale passé en paramètre
         * \param u - Initialise l'attribut current.
         */
        iterator(Litterale** u):current(u){}
        /*!
         * \brief Déclaration d'une amitié avec la classe LitteraleManager
         */
        friend class LitteraleManager;
    public:
        /*!
         * \brief Constructeur de iterator
         *
         * Initialise l'itérateur courant à zéro.
         */
        iterator():current(0){}
        /*!
         * \brief Déréférencement de l'itérateur courant
         * \return Retourne une référence sur le Litterale pointé par l'itérateur courant.
         */
        Litterale& operator*() const { return **current; }
        /*!
         * \brief Surcharge de l'opérateur différent ou égal
         * \param it - iterator sur lequel on souhaite appliquer l'opérateur !=.
         * \return Retourne vrai si l'itérateur courant est différent de celui passé en paramètre.
         */
        bool operator!=(iterator it) const { return current!=it.current; }
        /*!
         * \brief Surcharge de l'opérateur ++
         * \return Retourne une référence sur l'iterator suivant
         */
        iterator& operator++(){ ++current; return *this; }
    };
    /*!
     * \brief Méthode permettant de se positionner sur le premier élément de LitteraleManager.
     * \return Retourne un iterator sur le premier élément de LitteraleManager.
     */
    iterator begin() { return iterator(lits); }
    /*!
     * \brief Méthode permettant de se positionner sur le dernier élément de LitteraleManager.
     * \return Retourne un iterator sur le dernier élément de LitteraleManager.
     */
    iterator end() { return iterator(lits+nb); }
    /**
    \class const_iterator
    \brief Implémentation du design pattern iterator sur objet constant
    **/
    class const_iterator {
        /*!
         * \brief Iterateur courant de iterator constant
         *
         * Pointeur vers un pointeur d'objet Litterale
         */
        Litterale** current;
        /*!
         * \brief Constructeur de recopie de const_iterator
         *
         * Initialise l'itérateur courant sur le Litterale passé en paramètre.
         * \param u - Initialise l'attribut current.
         */
        const_iterator(Litterale** u):current(u){}
        /*!
         * \brief Déclaration d'une amitié avec la classe LitteraleManager
         *
         * Permt d'utiliser les méthodes de const_iterator sur un objet LitteraleManager
         */
        friend class LitteraleManager;
    public:
        /*!
         * \brief Constructeur de const_iterator
         *
         * Initialise l'itérateur courant à zéro.
         */
        const_iterator():current(0){}
        /*!
         * \brief Déréférencement de l'itérateur courant
         * \return Retourne une référence sur le Litterale pointé par l'itérateur courant.
         */
        Litterale& operator*() const { return **current; }
        /*!
         * \brief Surcharge de l'opérateur différent ou égal
         * \param it - const_iterator sur lequel on souhaite appliquer l'opérateur !=.
         * \return Retourne vrai si l'itérateur courant est différent de celui passé en paramètre.
         */
        bool operator!=(const_iterator it) const { return current!=it.current; }
        /*!
         * \brief Surcharge de l'opérateur ++
         * \return Retourne une référence sur le const_iterator suivant
         */
        const_iterator& operator++(){ ++current; return *this; }
    };
    /*!
     * \brief Méthode permettant de se positionner sur le premier élément de LitteraleManager.
     * \return Retourne un const_iterator sur le premier élément de LitteraleManager.
     */
    const_iterator begin() const { return const_iterator(lits); }
    /*!
     * \brief Méthode permettant de se positionner sur le dernier élément de LitteraleManager.
     * \return Retourne un const_iterator sur le dernier élément de LitteraleManager.
     */
    const_iterator end() const { return const_iterator(lits+nb); }
};



#endif // LITTERALEMANAGER_H
