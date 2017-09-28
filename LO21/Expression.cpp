#include <regex>
#include "Expression.hpp"

//REGEX Expression
regex nombreProbleme(".*(([[:digit:]][[:alpha:]]+)|([)][[:alnum:]])).*");
regex operateursProbleme("^.*(([-/+*][+/*])+|([-+/*$][)])+|([(][+/*$])+)+.*$");
regex complexeProbleme(".*[$]([+/*]|[[:digit:]]+[[:alpha:]]+|[[:alpha:]]+)+.*");
regex syntaxeCorrecteExpression("^([[:upper:]]|[[:digit:]]|[-,.$ ()+*/\\[\\]])+$");
regex vide("^[ ]$");
regex petitesLettres(".*([[:lower:]]|[^,.$ ()+*/-\\[\\]])+.*");
regex decimalProbleme("^.*[.]([[:digit:]]*[.])+.*$");

bool precedence(string operateur1, string operateur2){
    //La fonction "precedence" ne doit être appellé que pour comparer le stack avec un opérateur
    //Cette fonction sert également, uniquement à externalier du code, pour la lisibilité
    int valPrec1, valPrec2;

    //Une fonction à toujours la priorité max, (puisque parenthèsée)
    if (EstFonction(operateur2)){
        return true;
    }

    if (EstFonction(operateur1)){
        return false;
    }

    //S'il ne s'agit pas d'un opérateur référencé (ex : parenthèse) il n'y a pas de précédence
    auto recherche1 = operateurs_arithmetiques.find(operateur1);
    auto recherche2 = operateurs_arithmetiques.find(operateur2);
    valPrec1 = recherche1->second;
    valPrec2 = recherche2->second;

    if (recherche1 != operateurs_arithmetiques.end() && recherche2 != operateurs_arithmetiques.end() )
    {
        return valPrec1 <= valPrec2;
    }
    else
    {
        //Il n'y a précédence que si l'operateur1 possède une priorité plus faible ou égal que l'opérateur2
        return false;
    }
}

string Expression::toString() const{//TO DO remplacer toutes les tabs et newline en espace
    stringstream f;
    f<< "'" << this->exp << "'" << endl;;
    return f.str();
}

void Expression::elimineEspace(){
    exp.erase(std::remove_if(exp.begin(),exp.end(),[](char x){return std::isspace(x);}),exp.end());
}

bool Expression::verifSyntaxe(){
    this->elimineEspace();
    if(regex_match (exp, nombreProbleme)){
        throw ComputerException("Expression illégale (nombre invalide)");
        return false;
    }

    if(regex_match (exp, operateursProbleme)){
        throw ComputerException("Expression illégale (problème sur opérateurs)");
        return false;
    }

    else if(regex_match (exp, complexeProbleme)){
        throw ComputerException("Expression illégale (nombre complxe invalide)");
        return false;
    }

    else if(regex_match (exp, vide)){
        throw ComputerException("Expression illégale (expression vide)");
        return false;

    }
    else if(regex_match (exp, decimalProbleme)){
        throw ComputerException("Expression illégale (problème sur décimal)");
        return false;
    }
    else if(regex_match (exp, syntaxeCorrecteExpression)){
        return true;
    }

    else if(regex_match (exp, petitesLettres)){
        throw ComputerException("Expression illégale (petites lettres ou ponctuation interdite)");
        return false;
    }
    else {
        throw ComputerException("Expression illégale (caractère(s) inconnu(s))");
        return false;
    }
}

std::queue<std::string> Expression::shuntingYard(){

    if(!this->verifSyntaxe()) throw ComputerException("Expression incorrecte");

    std::queue<std::string> listeDeSortie; //Utilisé afin de stocker la chaine RPN finale
    std::stack<string> listePile; //Utilisé afin de stocker les opérateurs le temps de l'algorithme

    //Variable permettant de déterminer si l'on doit continuer de parcourir l'élément stack ou non lorsque l'on rencontre un opérateur de calcul
    bool parcoursPile = false;

    //Utilisé pour detecter la précédence d'un nombre (Gestion des nombres négatifs)
    bool precNum = false;

    //Utilisé pour la constitution des token "variable prédéfini"
    string chaineLectureVariable = "";

    //Utilisé pour la constitution des token "nombre double"
    string chaineLecture = "";

    for ( int i = 0; i < (int) exp.length(); ++i )//Parcours des caractères de la chaîne un par un
    {
        const std::string c( 1, exp[ i ] );

        /********************************************************************************
         ********** ETAPE 1 : Creation des tokens de nombres / variables / fonctions ****
         ********************************************************************************/
        //Permet de déterminer s'il s'agit d'un nombre
        if(chaineLectureVariable.empty() && EstNumerique(c))
        {
            chaineLecture += c;
            continue;

        }

        //Variable prédéfinie ou fonction

        if (chaineLecture == "" && !EstOperateur(c) && c != "(" && c != ")" && c != ",")
        {
            //Construction de la variable
            chaineLectureVariable += c;
            //On passe au caractère suivant, puisque le caractère courant a été traité
            continue;
        }
        //Une variable aprÈs une parenthèse est une fonction

        else if (chaineLectureVariable != "" && c == "(")
        {
            //Detection d'une fonction -> on ajoute la fonction au stack comme un opérateur
            if(!EstFonction(chaineLectureVariable)){
                QString erreur(QString::fromStdString(chaineLectureVariable) + " n'est pas une fonction connue !");
                throw ComputerException(erreur);
            }
            else{

                listePile.push(chaineLectureVariable);
                chaineLectureVariable = "";

                //Ajout de la parenthèse et passage à la lecture suivante
                listePile.push(c);
                continue;
            }
        }

        //Si un token de nombre a précédement été constitué on l'ajoute à la queue
        if (chaineLecture != "" && EstNumerique(chaineLecture))
        {
            listeDeSortie.push(chaineLecture);
            //Si un nombre a été détecté, il y a précédence par un nombre, donc opération de calcul sur le symbole '-'
            precNum = true;
            chaineLecture = "";
        }
        else
        {
            //Erreur, un nombre a été mal renseigné (ex nombre decimal incomplet => 3. ou 3.h (avec un caractère)) //TODO 3. est correct, vérifier que ce ne soit pas une lettre
            if (!chaineLecture.empty())
            {
                throw ComputerException("L'un des nombres renseignés est incorrect.");
            }
        }

        //Si un token de variable prédéfinie à précédement été constitué on l'ajoute à la queue
        if (chaineLectureVariable != "")
        {
            listeDeSortie.push(chaineLectureVariable);
            //Si une variable prédéfini a été détecté, il y a précédence par un nombre, donc opération de calcul sur le symbole '-'
            precNum = true;
            chaineLectureVariable = "";
        }

        if (c == ",") //séparateur de fonction
        {
            //L'ensemble des opérateurs doivent être dépilés avant le passage au parametres suivant
            while (listePile.size() > 0 && listePile.top() != "(")
            {
                listeDeSortie.push(listePile.top());
                listePile.pop();
            }

            //Il reste forcement la parenthèse gauche pour identifier le début de fonction, sinon => erreur de parenthèsage
            if (listePile.size() == 0)
                throw ComputerException("Problème de parenthèsage");
            //Lorsque l'on dépile on retombe sur une parenthèse, il n'y a donc pas précédence par un nombre
            precNum = false;

            continue;
        }

        /***********************************************************************************************************
         ****** ETAPE 2 : Creation des tokens operateurs_arithmetiques et de la gestion des nombres negatifs *******
         ***********************************************************************************************************/

        //s'il s'agit d'un opérateur on ajoute au stack
        if (EstOperateur(c))
        {
            if (c == "-" && (!precNum || (listeDeSortie.size() == 0|| (listePile.size() > 0 && listePile.top() == "("))))
            {
                //Gestion des nombres/variables negatifs
                //Si le nombre est écrit au debut de la chaine (ex : -5 + 6) ou suite à une parenthèse (ex : -5*(-6))
                //Dans ce cas on ajoute un zero avant d'ajouter l'operateur (ex: 0 - 5 + 6 // 0-5*(0-6))
                listeDeSortie.push("0");
                listePile.push(c);
                continue;
            }
            if (c == "$" && (listeDeSortie.size() == 0|| (listePile.size() > 0 && !precNum)))
            {
                //Gestion des nombres/variables complexes :
                //Si le nombre est écrit au debut de la chaine (ex : -5 $ 6) ou suite à une parenthèse (ex : -5*($6))
                //Dans ce cas on ajoute un zero avant d'ajouter l'operateur (ex: 0 - 5 6 $// 0-5*(0-6))
                listeDeSortie.push("0");
                listePile.push(c);
                continue;
            }

            else
            {
                parcoursPile = true;
                //Verification de la précédence afin de déterminer si on ajoute l'operateur à la queue ou au stack
                while (parcoursPile)
                {
                    if (listePile.size() > 0 && precedence(c, listePile.top()))
                    {
                        //si la priorite : caractere <= listack.peek()
                        listeDeSortie.push(listePile.top());
                        listePile.pop();
                    }
                    else
                    {
                        //s'il n'y a pas de précédence caractere > listack.peek OU caractere est autre chose qu'un opérateur
                        listePile.push(c); //On ajoute l'opérateur à la liste STack
                        parcoursPile = false; //Arrêt de la boucle de lecture
                    }
                }
            }
            //Si un opérateur a été détecté, il n'y a pas précédence par un nombre
            precNum = false;

            //On passe au record suivant
            continue;
        }

        /**************************************************************************************
         ****** ETAPE 3 : Creation des tokens de parenthèse ET de gestion des fonctions *******
         **************************************************************************************/

        //Dès que l'on  rencontre une parenthèse gauche on la stack, elle servira au dépilement (plus tard dans l'algo)
        if (c == "(")
        {
            listePile.push(c);

            //Si une parenthèse a été détecté, il n'y a pas précédence par un nombre
            precNum = false;

            //On passe au record suivant
            continue;
        }

        //Lorsque l'on trouve une parenthèse fermante on traite l'ensemble du contenu des parenthèses
        if (c == ")")
        {

            //Tant que l'on ne trouve pas de parenthèse gauche on depile les operateurs_arithmetiques dans la file
            while (listePile.size() > 0 && listePile.top() != "(")
            {
                listeDeSortie.push(listePile.top());
                listePile.pop();

            }

            //En sortie de boucle on controle le premier element de la pile
            if (listePile.size() > 0 && listePile.top() == "(")
            {

                listePile.pop(); //On retire la parenthèse ouvrante de la pile, car elle a été traitée
                //On recompte le nombre d'éléments du stack pour s'assurer qu'il ne s'agisse pas d'une parenthèse non attaché à une fonction
               if (listePile.size() > 0 && EstFonction(listePile.top()) == 1)
                {   //Une fois les parametres ajoutés, on peut ajouter la fonction qui utilisera le parametrage
                    listeDeSortie.push(listePile.top());
                    listePile.pop();

                    precNum = true;
                }

                continue;
            }
            else
            {
                throw ComputerException("Problème de parenthèsage");
            }
        }
        //La boucle est pre-interrompue après tout traitement, cette ligne ne doit jamais s'executer sinon => erreur
        //ex : probleme de nombre decimaux incomplets
        throw ComputerException("Une erreur est survenue, problème technique, algorithme mal implémenté.");
    }

    //TRAITEMENT DE LA DERNIERE CHAINE LUE
    //En sortie de boucle il ne peut rester qu'un nombre(ou variable prédéfinie)
    //Si un token de nombre à précédement été constitué on l'ajoute à la queue
    if (chaineLecture != "" && EstNumerique(chaineLecture))
    {
        listeDeSortie.push(chaineLecture); //Ajout à la queue du nombre constitué
    }
    else
    {
        //Erreur, un nombre a été mal renseigné (ex nombre decimal incomplet => 3. ou 3.h (avec un caractère))
        if (chaineLecture != "")
        {
            throw ComputerException("L'un des nombres renseignés est incorrect.");
        }
    }

    //Si un token de variable à précédement été constitué on l'ajoute à la queue
    if (chaineLectureVariable != "")
    {
        listeDeSortie.push(chaineLectureVariable); //Ajout à la queue de la variable identifié
    }

    /**************************************************************************************
     ***** ETAPE 4 : vidage de la pile et ajout de l'ensemble des opérateurs à la file ******
     **************************************************************************************/
    int taille = (int)listePile.size();

    //Ajout de la pile a la file
    for (int index = 0; index < taille; index++)
    {
        if (listePile.top() == "(")
        {
            throw ComputerException("Problème de parenthèsage");
        }
        listeDeSortie.push(listePile.top());
        listePile.pop();
    }

    return listeDeSortie;
}



