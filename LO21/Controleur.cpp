#include "Controleur.hpp"
#include "Pile.hpp"

namespace patch{
    template < typename T > std::string to_string( const T& n ){
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Controleur* Controleur::instance = nullptr;
vector<Memento*> Controleur::mementoListe;
unsigned int Controleur::IndexMemento = -1;

Controleur& Controleur::getInstance() {
    if(!instance) {
        instance = new Controleur();
    }

    return *instance;
}

void Controleur::libererInstance() {
    if (instance)
        delete instance;
}

Controleur::~Controleur() {
    libererInstance();
}

void Controleur::undo() {
    if (IndexMemento == 0) {
        throw ComputerException("Undo impossible!!");
    }
    Pile& pile = Pile::getInstance();
    pile.reinstateMemento(mementoListe[--IndexMemento]);
}

void Controleur::redo() {
    if (IndexMemento == mementoListe.size() - 1) {
        throw ComputerException("Redo impossible!");
    }
    Pile& pile = Pile::getInstance();
    pile.reinstateMemento(mementoListe[++IndexMemento]);
}

void Controleur::ajoutMemento(Memento* mem){
    if (IndexMemento != mementoListe.size() - 1) {
        for (unsigned int i=IndexMemento+1;i<mementoListe.size();i++){
            delete mementoListe[i];
        }
    }
    mementoListe.push_back(mem);
    IndexMemento++;
    }

