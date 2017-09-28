#include "LitteraleManager.h"

LitteraleManager::~LitteraleManager(){
    for(unsigned int i=0; i<nb; i++) delete lits[i];
    delete[] lits;
}

LitteraleManager::Handler LitteraleManager::handler=LitteraleManager::Handler();


LitteraleManager& LitteraleManager::getInstance(){
    if (handler.instance==0) handler.instance=new LitteraleManager;
    return *handler.instance;
}

void LitteraleManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}
void LitteraleManager::agrandissementCapacite() {
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=lits[i];
    Litterale**  old=lits;
    lits=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}

Litterale& LitteraleManager::ajoutLitterale(Litterale* lit){//TODO check si Litterale existe déjà ou non
    if (nb==nbMax) agrandissementCapacite();
    Litterale* pt=lit;
    lits[nb++]=pt;
    return *lits[nb-1];
}

void LitteraleManager::enleveLitterale(Litterale& e){
    unsigned int i=0;
    while(i<nb && lits[i]!=&e) i++;
    if (i==nb) throw "elimination d'une Litterale inexistante";
    delete lits[i];
    i++;
    while(i<nb) { lits[i-1]=lits[i]; i++; }
    nb--;
}
