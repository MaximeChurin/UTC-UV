#ifndef Programme_hpp
#define Programme_hpp

#include "Contexte.hpp"

 /**
 \class Programme
 \brief Implémentation d'une littérale Programme \n
 **/

class Programme : public Litterale, public Contexte{//Contexte -> traitementRPN
    /*!
     * \brief Contenu de l'objet Programme.
     */
    std::string contenu;
public:
    /*!
     * \brief Constructeur de Programme.
     *
     * Initialise Programme par initialisation du contenu.
     * \param s - Initialise l'attribut contenu.
     */
    Programme(std::string s):contenu(s){}
    /*!
     * \brief Destructeur de Rationelle.
     */
    ~Programme(){}
    /*!
    * \brief Accesseur pour l'attribut contenu.
    * \return Retourne la suite d'opérandes qui constitue le Programme.
    */
    std::string getContenu()const {return contenu;}
    /*!
    * \brief Vérifie la syntaxe d'un Programme
    * \return Retourne vrai si le Programme a une syntaxe correcte.
    */
    bool verifSyntaxe()const ;
    /*!
     * \brief Méthode pour afficher un Programme
     * \return Retourne une chaine de caractère composée du contenu du Programme.
     */
    std::string toString() const;
    //TODO vérifier la pertinence de estVrai
    inline bool estVrai()const{return true;}
};


#endif /* Programme_hpp */
