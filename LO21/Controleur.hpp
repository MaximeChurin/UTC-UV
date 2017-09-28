#ifndef Controleur_hpp
#define Controleur_hpp

#include "Contexte.hpp"
#include "Pile.hpp"

/*!
 * \brief La classe Controleur gère les differents états de la pile grâce à un vecteur d'objets Memento.
 */
class Controleur : public Contexte{
    /*!
     * \brief design pattern singleton, pointeur vers l'instance unique du controleur.
     */
    static Controleur* instance;
    /*!
     * \brief Constructeur de la classe Controleur.
     */
    Controleur(){}
    /*!
     * \brief Destructeur de la classe Controleur.
     */
    ~Controleur();
    /*!
     * \brief Vecteur d'objets Memento, c'est donc une liste de tous les états de la pile.
     */
    static vector<Memento*> mementoListe;
    /*!
     * \brief Compteur permettant de parcourir le vecteur de memento.
     */
    static unsigned int IndexMemento;
    /*!
     * \brief Declaration de l'operateur d'affectation dûe au pattern singleton.
     */
    Controleur& operator=(const Controleur&);
    /*!
     * \brief Declaration du constructeur par recopie dûe au pattern singleton.
     */
    Controleur (const Controleur&);
public:
     /*!
     * \brief Accesseur retournant la réference vers l'instance unique du controleur. Crée l'instance si elle n'existe pas.
     */
    static Controleur& getInstance();
     /*!
     * \brief Méthode supprimant l'instance si elle existe.
     */
    static void libererInstance();
     /*!
     * \brief Méthode ajoutant un objet Memento à la liste de Memento
     *
     * Ajoute à la fin de la liste un objet Memento en passant un pointeur vers ce dernier en paramètre.
     * \param mem - Pointeur vers l'objet Memento que l'on souhaite ajouter.
     */
    static void ajoutMemento(Memento* mem);
     /*!
      * \brief Méthode permetant de retourner la pile à son état précedent stocké dans la liste de Memento.
      */
    void undo();
     /*!
     * \brief Méthode permettant d'annuler un UNDO grâce à la liste de Memento.
     */
    void redo();
};

#endif /* Controleur_hpp */

