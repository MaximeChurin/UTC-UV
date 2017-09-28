#include "Pile.hpp"
#include "Controleur.hpp"

Pile* Pile::instance = nullptr;
Pile::Pile(): message(""), maxAffiche(0) {

}

Pile::~Pile() {
    libererInstance();
}

Pile& Pile::getInstance() {
    if (!instance)
        instance = new Pile();

    return *instance;
}

void Pile::libererInstance() {
    if (instance)
        delete instance;
}

QString Pile::getMessage() const {
    return message;
}

void Pile::setMessage(const QString& msg) {
    message = msg;
}

void Pile::setMaxAffiche(unsigned int i) {
    maxAffiche = i;
}

unsigned int Pile::getMaxAffiche() const {
    return maxAffiche;
}

void Pile::push(Litterale& l) {
    pile.push_back(&l);
    emit modificationEtat();
}


void Pile::pop() {
    if(getTaille() == 0)
        throw ComputerException("Erreur : Pile vide");
     pile.pop_back();
}

Litterale& Pile::top() const {
    if(getTaille() == 0)
        throw ComputerException("Erreur : Pile vide");
    else
        return *pile.back();
}

unsigned int Pile::getTaille() const {
    return pile.size();
}

bool Pile::estVide() {
    return pile.empty();
}

deque<Litterale*>::const_iterator Pile::getIteratorBegin() const {
    deque<Litterale*>::const_iterator i = pile.cbegin();
    return i;
}

deque<Litterale*>::const_iterator Pile::getIteratorEnd() const {
    deque<Litterale*>::const_iterator i = pile.cend();
    return i;
}

void Pile::dup() {
    if(getTaille() < 1){
        throw ComputerException("Pas assez d'arguments dans la pile");
    }
    setlastArg1(pile.back());
    pile.push_back(pile.back());
}

void Pile::drop() {
    if(getTaille() < 1){
        throw ComputerException("Pas assez d'arguments dans la pile");
    }
    setlastArg1(pile.back());    
    pile.pop_back();
}

void Pile::swap(){
    if(getTaille() < 2){
        throw ComputerException("Pas assez d'arguments dans la pile");
    }
    Litterale& it1= top();
    setlastArg1(&it1);
    pop();
    Litterale& it2= top();
    setlastArg2(&it2);
    pop();
    push(it1);
    push(it2);
}

void Pile::reinstateMemento(Memento* mem) {
    pile = mem->getEtatPile();
}

void Pile::lastop(){
    LitteraleManager& litMng = LitteraleManager::getInstance();

    auto recherche1 = fonctions_unaires.find(lastOp);
    auto recherche2 = fonctions_binaires.find(lastOp);
    auto recherche3 = fonctions_pre_unaires.find(lastOp);
    auto recherche4 = fonctions_pre_binaires.find(lastOp);
    if(recherche1 != fonctions_unaires.end()){
        //C'est une fonction unaire
        if(getTaille() < 1){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
        Litterale& l1 = this->top();
        pop();
        push(fonctions_unaires[lastOp](l1));

    }

    else if(recherche2 != fonctions_binaires.end()){
        //C'est une fonction binaire
        if(getTaille() < 2){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
        Litterale& l2 = top();
        pop();
        Litterale& l1 = top();
        pop();
        push(fonctions_binaires[lastOp](l1,l2));

    }
    else if(recherche3 != fonctions_pre_unaires.end()){
        if(getTaille() < 1){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
        Litterale& l1 = top();
        pop();
        FnPtrUnPre f = fonctions_pre_unaires[lastOp];
        (*f)(l1);
    }
    else if(recherche4 != fonctions_pre_binaires.end()){
        if(getTaille() < 2){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
        Litterale& l2 = top();
        pop();
        Litterale& l1 = top();
        pop();
        fonctions_pre_binaires[lastOp](l1,l2);
    }
    else if(lastOp=="IFT"){
        IFT();
    }
    else if(lastOp=="IFTE"){
        IFTE();
    }
    else if(lastOp=="WHILE"){
        While();
    }
    else if(lastOp=="DUP"){
        dup();
    }
    else if(lastOp=="DROP"){
        drop();
    }
    else if(lastOp=="SWAP"){
        swap();
    }
    else if(lastOp=="lastOp"){
        lastop();
    }
    else if (lastOp=="lastArgS"){
        lastArgs();
    }
    else if (lastOp=="CLEAR"){
        clear();
    }
    else if (lastOp=="UNDO"){
        Controleur::getInstance().undo();
    }
    else if(lastOp=="REDO"){
        Controleur::getInstance().redo();
    }
    else if(lastOp=="FORGET"){
        throw ComputerException("Impossible de refaire l'opération FORGET");
    }
    else
        throw ComputerException("Dernier operateur inconnu");
}

void Pile::lastArgs(){
    auto recherche1 = fonctions_unaires.find(lastOp);
    auto recherche2 = fonctions_binaires.find(lastOp);
    auto recherche3 = fonctions_pre_unaires.find(lastOp);
    auto recherche4 = fonctions_pre_binaires.find(lastOp);
    if(recherche1 != fonctions_unaires.end() || recherche3 != fonctions_pre_unaires.end() ||
            lastOp == "DUP" || lastOp == "DROP" || lastOp=="FORGET"){
                push(*lastArg1);
    }
    else if(recherche2 != fonctions_binaires.end() || recherche4 != fonctions_pre_binaires.end() ||
            lastOp == "IFT" || lastOp == "WHILE" || lastOp == "IFT" || lastOp == "SWAP" || lastOp=="REDO" ){
            Controleur::getInstance().redo();

            push(*lastArg1);
    }
    else
        throw ComputerException("Aucun argument de la derniere operation n'est disponible");
}

void Pile::IFT(){//TODO demander exécution
    if(this->getTaille() < 2){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
    Litterale& arg1=this->top();
    setlastArg1(&arg1);
    pop();
    Litterale& arg2=this->top();
    setlastArg2(&arg2);
    pop();
    if(arg2.estVrai()){
        EVAL(arg1);
    }
}

void Pile::IFTE(){//TODO demander exécution
    if(this->getTaille() < 3){
            throw ComputerException("Pas assez d'arguments dans la pile");
        }
    Litterale& arg1=top();
    setlastArg1(&arg1);
    pop();
    Litterale& arg2=top();
    setlastArg2(&arg2);
    pop();
    Litterale& arg3=top();
    setlastArg3(&arg3);
    pop();
    if(arg3.estVrai())
        EVAL(arg2);
    EVAL(arg1);
}

void Pile::While(){//TODO demander exécution
    Litterale& arg1=top();
    setlastArg1(&arg1);
    pop();
    Litterale& arg2=top();
    setlastArg2(&arg2);
    pop();
    while(arg2.estVrai())
        EVAL(arg1);
    }

void FORGET(std::string str){
    extern std::map<string,Litterale*> Map;
    Map.erase(str);
}
