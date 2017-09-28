#ifndef Contexte_hpp
#define Contexte_hpp

#include "Litterale.hpp"

/**
\class Contexte
\brief La classe Contexte implémente le design pattern Stratégie pour le traitement RPN \n
**/

using namespace std;

class Contexte{
    
public:
    /*!
    * \brief Evalue le parametre selon la methode RPN.
    * \param s - chaine de caractères.
    * \param b - booleaen.
    */
    void traitementRPN(std::string, bool = false);
    
};

/*!
* \brief Evalue les caractères d'espacement d'une chaine de caractères.
* \param str - chaine de caractères.
* \return Retourne vrai si la chaine de caractere contient des caractères d'espacement.
*/
bool contientEspace(std::string str);
/*!
 * \brief Récupère une chaine de caractères dont le dernier opérateur accolé est séparé.
* \param s - chaine de caractères.
 */
std::string dernierOperateur(std::string s);
/*!
 * \brief Transforme une chaine de caractères en file de chaines de caractères.
* \param str - chaine de caractères qu'on veut placer dans une file.
* \return Retourne une file de chaine de caractères composée de tous les atomes de la chaine passée en paramêtre
 */
std::queue<std::string> stringToQueue(std::string str);
/*!
 * \brief Effectue un calcul binaire sur deux Litterale avec un opérateur defini.
* \param l1 - Premier Litterale sur lequel s'applique l'opérateur.
* \param l2 - Deuxième Litterale sur lequel s'applique l'opérateur.
* \param operateur - Opérateur.
* \return Retourne le résultat de l'opération sous la forme d'un pointeur sur une Litterale
 */
Litterale* CalculBinaire(Litterale& l1, Litterale& l2, string operateur);

#endif /* Contexte_hpp */
