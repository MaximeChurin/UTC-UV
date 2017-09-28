#include "Contexte.hpp"
#include "Programme.hpp"
#include "Controleur.hpp"
#include "Numerique.h"
#include "Expression.hpp"
#include <queue>
#include <string>


/****** REGEX ATOME *****/
regex correcteSyntaxeAtome("[[:upper:]][[:upper:][:digit:]]*");
regex sansMajuscule("[^[:upper:]].*");
regex lettresMinuscule(".*[[:lower:]].*");

/****** REGEX REEL ET ENTIER *****/
regex correcteReel("[[:digit:]]*[.]{1}[[:digit:]]*");
regex correcteEntier("[[:digit:]]+");

bool contientEspace(std::string str){
    int i = 0;
    char c;
    while (str[i])
    {
        c=str[i];
        if (isspace(c)) return true;
        i++;
    }
    return false;

}


std::string dernierOperateur(std::string str){
    string str1 = str;
    string str2 = "";
    const std::string c( 1, str[ str.size() - 1 ] );
    if(EstOperateur(c)){
        str1 = str.substr(0,str.size()-1);
        str2 = str.substr(str.size()-1, str.size());
    }
    return str1 + " " + str2;
}


std::queue<string> stringToQueue(std::string s){

    std::queue<std::string> tokens;
    string chaine = "";

    std::stack<string> pileTmp;//permet l'identification des programmes

    //*** On ne dépile pas si on lit une expression **//
    bool lectureExp = false;

    string str = dernierOperateur(s);

    //**PARCOURS DE LA CHAINE DE CARACTERES*//
    for ( int i = 0; i < (int) str.length(); ++i )
    {
        const std::string c( 1, str[ i ] );

        //** DIFFERENCIATION DES CAS **//

        if(c == "'" && pileTmp.empty()){//si on lit une expression alors on ne push pas avant d'avoir atteint le 2e '
            chaine += c;
            lectureExp = !lectureExp;
            if(lectureExp == false) {
                tokens.push(chaine);
                chaine = "";
                continue;
            }
        }

        else if(c == "[" && !lectureExp){//si on lit un programme alors on ne push pas avant d'avoir atteint le ] correspondant
            //on empile le [ et on continue de lire la chaine jusqu'à arriver à un ] qui ferait dépiler
            if(chaine != "" && pileTmp.empty()) {
                tokens.push(chaine);
                chaine ="";
            }

            pileTmp.push(c);
            chaine += c;
            continue;
        }
        else if(c == "]" && !lectureExp){
            if(pileTmp.empty()) throw ComputerException("vérifiez la syntaxe !");
            pileTmp.pop();
            chaine += c;
            if(pileTmp.empty()) {
                tokens.push(chaine); //si la pile est vide alors on est arrivé à la fin du traitement du programme, on push
                chaine = "";
                continue;
            }
            else continue;
        }
        else if(c == " " && pileTmp.empty() && lectureExp == false){
            //quelque chose est prêt à être pushé, sauf si dans un programme ou expression
            tokens.push(chaine);
            chaine = "";
            continue;
        }
        else {
            chaine += c;
            continue;
        }
    }


    if(!chaine.empty())
        tokens.push(chaine);
    if(!pileTmp.empty())
        throw ComputerException("Erreur syntaxe programme");

    return tokens;

}

std::queue<std::string> vectorToQueue(std::vector<string> pile){
    std::queue<string> file;

    for(auto& f: pile){
        file.push(f);
    }
    return file;
}


std::vector<string> stringToVector(std::string str){

    std::istringstream buf(str);
    std::istream_iterator<std::string> beg(buf), end;
    std::vector<std::string> tokens(beg, end);
    return tokens;


}


std::string retablirEtatLigne(std::queue<std::string> fileTemp, std::string dernierEltraite){

    std::string ligne = dernierEltraite;
    while(!fileTemp.empty()){
        ligne += fileTemp.front();
        fileTemp.pop();
    }
    return ligne;
}

void Contexte::traitementRPN(std::string str, bool traiteProg){

    /****** Trasnformation de la chaine à traiter en tokens, placés ensuite dans une file d'exécution de traitement en RPN*****/
    std::queue<std::string> fileTemp = stringToQueue(str);

    /****** Récupération des instances de la pile et du manager de littéraux*****/
    Pile& Pile = Pile::getInstance(); 
    LitteraleManager& litMng = LitteraleManager::getInstance();

    /****** On parcourt la file en traiant les tokens un à un *****/
    while(!fileTemp.empty()){
        
        std::string s = fileTemp.front();
        fileTemp.pop();

        /****** Reconnaissances du type des tokens *****/

        if(s == " ") continue;//les espaces ne sont pas évalués

        //C'est un réel
        if(EstNumerique(s) && regex_match(s, correcteReel)) {//match un reel
            Pile.push(litMng.ajoutLitterale(&bonType(stof(s))));
            
        }
        //c'est un entier
        else if(EstEntier(s) && regex_match(s,correcteEntier)){// match un entier
            Pile.push(litMng.ajoutLitterale(&bonType(stoul(s))));
            
        }
        //c'est une expression
        else if(regex_match(s,regex("^'.*'$"))){//match une expression
            string s1 = s.substr(1,s.length()-2);
            Expression* exp = new Expression(s1);
            Pile.push(litMng.ajoutLitterale(exp));
        }
        //c'est un programme
        else if(regex_match (s, regex("^\\[.*\\]$"))){//match un programme
            string s1 = s.substr(1,s.length()-2);
            Programme* prog = new Programme(s1);
            prog->verifSyntaxe();
            //si on est déjà en train de traiter un programme, et donc le token en cours est un sous-programme -> on stocke
            if(traiteProg == true) {
                Pile.push(litMng.ajoutLitterale(prog));
            }
            else{
                //sinon on traite le programme en question
                prog->traitementRPN(s1,true);
            }

        }
        //c'est un identificateur de variable, de programme, de fonction ou juste un atome
        else if(regex_match(s, correcteSyntaxeAtome)){
            //match un atome
            
            /****** Cherche si la fonction est déjà prédéfinie *****/
            auto recherche1 = fonctions_unaires.find(s);
            auto recherche2 = fonctions_binaires.find(s);
            auto recherche3 = fonctions_pre_unaires.find(s);
            auto recherche4 = fonctions_pre_binaires.find(s);

            if(recherche1 != fonctions_unaires.end()){
                //C'est une fonction unaire

                if(Pile.getTaille() < 1){
                    throw ComputerException("Pas assez d'arguments dans la pile");
                }
                Litterale& l1 = Pile.top();
                Pile.pop();
                Pile.push(litMng.ajoutLitterale(&fonctions_unaires[s](l1)));
                Pile.setlastOp(s);
                Pile.setlastArg1(&l1);
            }
            //C'est une fonction binaire
            else if(recherche2 != fonctions_binaires.end()){
                if(Pile.getTaille() < 2){
                    throw ComputerException("Pas assez d'arguments dans la pile");
                }
                Litterale& l2 = Pile.top();
                Pile.setlastArg1(&l2);
                Litterale& l1 = Pile.top();
                Pile.pop();
                Pile.push(litMng.ajoutLitterale(&fonctions_binaires[s](l1,l2)));
                Pile.setlastOp(s);
                Pile.setlastArg1(&l1);
                Pile.setlastArg2(&l2);
            }
            //C'est une fonction préféfinie ou un programme
            else if(recherche3 != fonctions_pre_unaires.end()){
                //C'est une fonction unaire prédéfinie
                if(Pile.getTaille() < 1){
                    throw ComputerException("Pas assez d'arguments dans la pile");
                }

                Litterale& l1 = Pile.top();
                Pile.setlastArg1(&l1);
                Pile.pop();
                FnPtrUnPre f = fonctions_pre_unaires[s];
                (*f)(l1);
                Pile.setlastOp(s);
            }

            else if(recherche4 != fonctions_pre_binaires.end()){
                //C'est une fonction binaire prédéfinie
                if(Pile.getTaille() < 2){
                    throw ComputerException("Pas assez d'arguments dans la pile");
                }
                Litterale& l2 = Pile.top();
                Pile.setlastArg1(&l2);
                Pile.pop();
                Litterale& l1 = Pile.top();
                Pile.setlastArg2(&l1);
                Pile.pop();
                FnPtrBinPre f = fonctions_pre_binaires[s];
                (*f)(l1,l2);
                Pile.setlastOp(s);
            }            
            else if(s=="IFT"){
                Pile.IFT();
                Pile.setlastOp(s);
            }
            else if(s=="IFTE"){
                Pile.IFTE();
                Pile.setlastOp(s);
            }
            else if(s=="WHILE"){
                Pile.While();
                Pile.setlastOp(s);
            }
            else if(s=="DUP"){
                Pile.dup();
                Pile.setlastOp(s);
            }
            else if(s=="DROP"){
                Pile.drop();
                Pile.setlastOp(s);
            }
            else if(s=="SWAP"){
                Pile.swap();
                Pile.setlastOp(s);
            }
            else if(s=="lastOp"){
                Pile.setlastOp(s);
                Pile.lastop();
            }
            else if (s=="lastArgS"){
                Pile.lastArgs();
                Pile.setlastOp(s);
            }
            else if (s=="CLEAR"){
                Pile.clear();
                Pile.setlastOp(s);
            }
            else if (s=="UNDO"){
                Controleur::getInstance().undo();
                Pile.setlastOp(s);
            }
            else if(s=="REDO"){
                Controleur::getInstance().redo();
                Pile.setlastOp(s);
            }
            /****** c'est un programme, variable ou une expression*****/
            else{
                extern std::map<string,Litterale*> Map;
                std::map<string,Litterale*>::iterator it;
                /****** cherche si l'identificateur est déjà connu *****/
                it = Map.find(s);
                if (it != Map.end()){
                    Numerique* p = dynamic_cast<Numerique*>(it->second);
                    if (p != 0)//la littérale associée est de type Numérique
                    {
                        Pile.push(litMng.ajoutLitterale(it->second));
                        
                    }
                    else{
                        Expression* p = dynamic_cast<Expression*>(it->second);
                        if (p != 0)//la littérale associée est de type Expression-> évaluer l'expression
                        {
                                EVAL(*p);//évaluation de l'expression
                        }
                        else
                        {
                            Programme* p = dynamic_cast<Programme*>(it->second);
                            if (p != 0)//la littérale associée est de type Programme-> déclencher le programme
                            {
                                EVAL(*p);//évaluation du programme
                            }

                            else {
                                throw ComputerException("Erreur Map Atome Littérale");
                            }

                        }
                    }
                }
                else{//on créé une nouvelle expression avec la chaine de caractère
                    Expression* exp = new Expression(s);
                    Pile.push(litMng.ajoutLitterale(exp));
                    throw ComputerException("Nouvelle Expression créée");
                }
                
            }
        }
        
        else if (EstOperateur(s)){
            //check Taille pile : on ne gère que des opérateurs binaires ici, il y a NEG pour le - unaire
            if(Pile.getTaille() < 2){
                throw ComputerException("Pas assez d'arguments dans la pile");
            }
            Litterale& l2 = Pile.top();
            Pile.pop();
            Litterale& l1 = Pile.top();
            Pile.pop();

            Pile.push(litMng.ajoutLitterale(CalculBinaire(l1,l2,s)));
            
            
        }
        else{//TODO on replace le reste de la pile dans la ligne de commande et on affiche l'erreur
            //match un atome malformé
            if(regex_match(s, sansMajuscule)){
                 throw ComputerException("Mauvais syntaxe : première lettre doit être une majuscule");
             }
             else if(regex_match(s, lettresMinuscule)){
                throw ComputerException("Mauvaise syntaxe : que des lettres majuscules ou chiffres et commencant par majuscule");
            }
            throw ComputerException("Opérande n’est pas correcte syntaxiquement", QString::fromStdString(retablirEtatLigne(fileTemp, s)));           
        }
        if ((s!= "EVAL")&&(s!= "UNDO")&&(s!= "REDO")){
            Controleur::ajoutMemento(Pile.SavePile());}
    }
}


Litterale* CalculBinaire(Litterale& l1, Litterale& l2, string operateur){
    if(operateur == "+"){

        return &(l1 + l2);
    }
    else if(operateur == "-"){

        return &(l1 - l2);
    }
    else if(operateur == "*"){

        return &(l1 * l2);
    }
    else if(operateur == "/"){

        return &(l1 / l2);
    }
    else if(operateur == "$"){

        return &($(l1, l2));
    }
    else if(operateur == "="){

        return &(NOT(l1!=l2));
    }
    else if(operateur == "!="){

        return &(l1!=l2);
    }
    else if(operateur == "<"){

        return &(l1<l2);
    }
    else if(operateur == ">"){

        return &(l1>l2);
    }
    else if(operateur == ">="){

        return &(NOT(l1<l2));
    }
    else if(operateur == "=<"){

        return &(NOT(l1>l2));
    }
    else throw ComputerException("Opérateur incompris");
}
