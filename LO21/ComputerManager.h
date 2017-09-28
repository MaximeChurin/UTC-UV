#ifndef Computer_H
#define Computer_H
#include <QString>
#include "LitteraleManager.h"
#include "Complexe.h"
#include "Expression.hpp"
#include "Programme.hpp"
#include "Atome.hpp"
#include <QObject>
#include <QWidget>
#include "Pile.hpp"



/**
\class ComputerManagerDataContexte
\brief La classe  ComputerManagerDataContexte est une interface des strategies de stockage de ComputerManager \n
**/
class ComputerManagerDataContexte{

protected:
    QString fichier;
    bool bell;
    bool clavier;
    int nbAffiche;
public:
    ComputerManagerDataContexte():fichier(""){}
    //! \brief charge les données de tout les managers de Computer Manager
    virtual void charger(const QString& f) = 0;
     //! \brief sauvegarde dans un fichier les données des managers de Computer Manager
    virtual void sauvegarder(const QString& f = "") = 0;
};

/**
\class ComputerManagerDataXML
\brief La classe ComputerManagerDataXML implémente du design patern strategy avec du XML \n
**/
class ComputerManagerDataXML: public ComputerManagerDataContexte {
friend class MainWindow;
public:
    void charger(const QString& f);
    void sauvegarder(const QString& f = "");

};

/**
\class ComputerManager
\brief La classe ComputerManager est un super manager pour la classe LitteraleManager. Elle gere le stockage. \n

**/
class ComputerManager{
    static ComputerManager* manager;
    ComputerManagerDataContexte* dataContexte;
    LitteraleManager* litMng;
    bool charge;
    ComputerManager(const ComputerManager& a);
    ComputerManager(ComputerManagerDataContexte* _dataContexte): dataContexte(_dataContexte), litMng(0), charge(false) {}


public:
    //! \brief instancie le manager et tous les managers associes.
    static ComputerManager& getManager(){
        if(manager == 0){

            manager = new ComputerManager(new ComputerManagerDataXML());

            manager->litMng = &(LitteraleManager::getInstance());
            //manager->atMng = &(AtomeManager::getInstance());
        }
        return *manager;
    }
    //! \brief libere le manager
    static void libereManager(){
        if(manager != 0)
            delete manager;
        manager = 0;
    }

    //! \brief permet de vérifier l'état du manager
    static bool existeManager(){
        return manager!=0;
    }
    //! \brief Destructeur de ComputerManager
    ~ComputerManager(){
        LitteraleManager::libererInstance();
        Pile::libererInstance();
    }

    //! \brief retourne vrai si un fichier est chargé
    bool estCharge() const { return charge; }
    //! \brief charge la pile, les paramétres, les variables et les programmes
    void charger(const QString& s) { dataContexte->charger(s); charge=true; }
    //! \brief sauvegarde la pile, les paramétrages, les variables et les programmes
    void sauvegarder(const QString& s = "")  const { dataContexte->sauvegarder(s); }

};




#endif // Computer_H
