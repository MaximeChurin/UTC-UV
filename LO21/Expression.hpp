#ifndef Expression_hpp
#define Expression_hpp

#include "Atome.hpp"
#include "Contexte.hpp"

using namespace std;

/**
\class Expression
\brief \brief La classe Expression represente une expression. Elle possede un attribut de type string.
**/
class Expression : public Litterale,public Contexte {
    string exp;
public:
    /*!
     * \brief Constructeur d'e Complexe'Expression.
     *
     * Affecte a l'Expression sa chaine de cractere.
     * \param exp - Initialise l'attribut.
     */
    explicit Expression(const string& val){
        // la chaine de caractere donnée en paramètre peut contenir des apostrophes qu'on
        //ne stockera pas mais présents dans l'affichage
        if(regex_match(val, regex("^'.*'$"))) {
            string s1 = val.substr(1,val.length()-2);
            exp = val;
        }
        else exp = val;
        elimineEspace();
    }
    /*!
     * \brief Méthode de mise en forme d'une Expression
     * \return Retourne le string a afficher.
     */
    string toString() const;
    /*!
     * \brief Accesseur de l'attribut d'Expression
     * \return Retourne le string.
     */
    string getExpression() const {return exp;}
    //! \brief Elimine tous les espaces contenus dans l'Expression
    void elimineEspace();
    //! \brief Retourne vrai si l'expression respecte une syntaxe d'expression
    bool verifSyntaxe();
    ~Expression(){}

    /*! \brief permet la transformation d'une notation préfixée en notation RPN
     *
     *  Cette méthode est utilise l'algorithme de shunting yard. Cet algorithme va permettre la transformation en notation RPN de
     * l'expression écrite en notation préfixée, et ceci pour permettre son traitement par la calculatrice qui ne comprend que la notation RPN.
     */
    std::queue<std::string> shuntingYard();
    //! \brief retourne vrai si l'objet est de type Expression
    bool estVrai()const{return true;}

};
/*!
 * \brief Methode pour connaitre la priorite entre deux operateurs
 * \param operateur1 - String correspondant au premier operateur.
 * \param operateur2 - String correspondant au second operateur.
 * \return Retourne true si le secon est plus prioritaire que le second, faux sinon.
 */
bool precedence(string operateur1, string operateur2);


#endif /* Expression_hpp */
