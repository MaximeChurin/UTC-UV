#include "LitteraleManager.h"
#include "Programme.hpp"
#include "Atome.hpp"
#include "Entiere.h"
#include "Rationelle.h"
#include "Reelle.h"
#include "Complexe.h"
#include "Expression.hpp"
#include "Pile.hpp"

const regex correcteSyntaxeAtome("[[:upper:]][[:upper:][:digit:]]*");
std::map<string,Litterale*> Map;


int PGCD(int a, int b){
    while(b!=0){
        int c=a%b;
        a=b;
        b=c;
    }
    return a;
}

Litterale& bonType(double pReelleNum, double pReelleDen, double pImNum, double pImDen){
    Numerique* pReelle;

    int r  = PGCD(pReelleNum, pReelleDen);
        if (r!=1 && r!=0){
            pReelleNum /= r;
            pReelleDen /= r;
        }

    if((pReelleNum-floor(pReelleNum))==0){//num entier
            if(pReelleDen == pReelleNum || pReelleNum==0 || pReelleDen==1){//pReelle entier
                    if(pReelleNum==pReelleDen)
                        pReelle = new Entiere(1);
                    else
                        pReelle = new Entiere(pReelleNum);
            }
            else
                if((pReelleDen-floor(pReelleDen))==0)//den entier
                    pReelle = new Rationnelle(pReelleNum, pReelleDen);
                else
                    pReelle = new Reelle(pReelleNum/pReelleDen);//den reelle
    }
    else{
        if(pReelleDen == pReelleNum){//num = den
            pReelle = new Entiere(1);
        }
        else
            pReelle = new Reelle(pReelleNum/pReelleDen);
    }

    if (pImNum == 0)//pas complexe
        return *pReelle;
    else{//complexe
         Numerique* pIm;

         if(pReelle->getPartieReelle()<pow(10,-10))
            pReelle = new Entiere(0);

        int ri  = PGCD(pImNum, pImDen);
        if (ri!=1 && ri!=0){
            pImNum /= ri;
            pImDen /= ri;
        }

        if((pImNum-floor(pImNum))==0){//num entier
                if(pImDen == pImNum || pImNum==0 || pImDen==1){//pIm entier
                    if(pImNum==pImDen)
                        pIm = new Entiere(1);
                    else
                        pIm = new Entiere(pImNum);
                }
                else
                    if(pImDen-floor(pImDen)==0)//den entier
                        pIm = new Rationnelle(pImNum, pImDen);
                    else
                        pIm = new Reelle(pImNum/pImDen);//den reelle
        }
        else{ //num reel
            if (pImNum == pImDen)//num = den
                pIm = new Entiere(1);
            else
                pIm = new Reelle(pImNum/pImDen);
        }
        return *new Complexe(*pReelle, *pIm);
    }

}

Litterale& operator+(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Addition impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
        return *new Expression('('+l1.getExpression()+")+("+l2.getExpression()+')');

    return bonType(l1.getPartieReelleNum()*l2.getPartieReelleDen()+l2.getPartieReelleNum()*l1.getPartieReelleDen(),
                   l1.getPartieReelleDen()*l2.getPartieReelleDen(),
                   l1.getPartieImNum()*l1.getPartieImDen()+l2.getPartieImNum()*l1.getPartieImDen(),
                   l1.getPartieImDen()*l2.getPartieImDen());
}

Litterale& operator-(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Soustraction impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
        return *new Expression('('+l1.getExpression()+")-("+l2.getExpression()+')');

    return bonType(l1.getPartieReelleNum()*l2.getPartieReelleDen()-l2.getPartieReelleNum()*l1.getPartieReelleDen(),
                   l1.getPartieReelleDen()*l2.getPartieReelleDen(),
                   l1.getPartieImNum()*l1.getPartieImDen()-l2.getPartieImNum()*l1.getPartieImDen(),
                   l1.getPartieImDen()*l2.getPartieImDen());
}

Litterale& operator*(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Multiplication impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression('('+l1.getExpression()+")*("+l2.getExpression()+')');
    if(typeid(l1) == typeid(Complexe) || typeid(l2) == typeid(Complexe))
        return bonType( (l1.getPartieReelleNum()*l2.getPartieReelleNum()*l1.getPartieImDen()*l2.getPartieImDen()) - (l1.getPartieImNum()*l2.getPartieImNum()*l1.getPartieReelleDen()*l2.getPartieReelleDen()),
                   l1.getPartieReelleDen()*l2.getPartieReelleDen()*l1.getPartieImDen()*l2.getPartieImDen(),
                   (l1.getPartieReelleNum()*l2.getPartieImNum()*l1.getPartieImDen()*l2.getPartieReelleDen()) + (l2.getPartieReelleNum()*l1.getPartieImNum()*l2.getPartieImDen()*l1.getPartieReelleDen()),
                   l1.getPartieReelleDen()*l2.getPartieReelleDen()*l1.getPartieImDen()*l2.getPartieImDen());

    return bonType(l1.getPartieReelleNum()*l2.getPartieReelleNum(),
                   l1.getPartieReelleDen()*l2.getPartieReelleDen(),
                   l1.getPartieImNum()*l2.getPartieImNum(),
                   l1.getPartieImDen()*l2.getPartieImDen());

}

Litterale& operator/(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Division impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression('('+l1.getExpression()+")/("+l2.getExpression()+')');

    if(typeid(l2) == typeid(Complexe)){
        return bonType(l1.getPartieReelle()*l2.getPartieReelle() + l1.getPartieIm()*l2.getPartieIm(),
                        pow(l2.getPartieReelle(),2)+pow(l2.getPartieIm(),2),
                        l2.getPartieReelle()*l1.getPartieIm() - l2.getPartieIm()*l1.getPartieReelle(),
                        pow(l2.getPartieReelle(),2)+pow(l2.getPartieIm(),2));
    }

    if(l2.getPartieReelleNum()==0)
        throw ComputerException("Division par 0 !");

    return bonType(l1.getPartieReelleNum()*l2.getPartieReelleDen(),
                   l1.getPartieReelleDen()*l2.getPartieReelleNum(),
                   l1.getPartieImNum()*l2.getPartieReelleDen(),
                   l1.getPartieImDen()*l2.getPartieReelleNum());
}


Litterale& $(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Expression) ||
            typeid(l2) == typeid(Expression) || typeid(l1) == typeid(Complexe) ||
            typeid(l2) == typeid(Complexe)|| typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Creation de complexe impossible !");

    return bonType(l1.getPartieReelleNum(),
                   l1.getPartieReelleDen(),
                   l2.getPartieReelleNum(),
                   l2.getPartieReelleDen());
}

Litterale& NEG(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Negation impossible !");
    if (typeid(l) == typeid(Expression))
            return *new Expression("NEG("+l.getExpression()+')');
    return bonType(-l.getPartieReelleNum(),
                   l.getPartieReelleDen(),
                   -l.getPartieImNum(),
                   l.getPartieImDen());
}

Litterale& POW(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
        throw ComputerException("Puissance impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression("POW("+l1.getExpression()+','+l2.getExpression()+')');
    if(typeid(l2) == typeid(Complexe))
        return EXP(l1*LN(l2));
    if(typeid(l1) == typeid(Complexe))
        return POW(NORM(l1),l2)*($(COS(l2*ARG(l1)), SIN(l2*ARG(l1))));
    if(l1.getPartieReelle()<0)
        return bonType(0,
                       1,
                       pow(-l1.getPartieReelle(),l2.getPartieReelle()));

    if(typeid(l2) == typeid(Entiere))
        return bonType(pow(l1.getPartieReelleNum(), l2.getPartieReelleNum()),
                   pow(l1.getPartieReelleDen(),l2.getPartieReelleNum()));

    return bonType(pow(l1.getPartieReelleNum(), l2.getPartieReelle())/pow(l1.getPartieReelleDen(), l2.getPartieReelle()));
}

Litterale& SIN(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Sinus impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("SIN("+l.getExpression()+')');
    return bonType(sin(l.getPartieReelle())*cosh(l.getPartieIm()),
               1,
               cos(l.getPartieReelle())*sinh(l.getPartieIm()));
}

Litterale& COS(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Cosinus impossible avec cet operateur  !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("COS("+l.getExpression()+')');

    return bonType(cos(l.getPartieReelle())*cosh(l.getPartieIm()),
               1,
               -(sin(l.getPartieReelle())*sinh(l.getPartieIm())));
}

Litterale& TAN(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Cosinus impossible avec cet operateur  !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("TAN("+l.getExpression()+')');

    return SIN(l)/COS(l);
}

Litterale& ARCSIN(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Arc Sinus impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("ARCSIN("+l.getExpression()+')');
    return $(*new Entiere(), *new Entiere(-1)) * LN($(*new Entiere(), *new Entiere(1))*l+POW(*new Entiere(1) + NEG(l * l),*new Reelle(0.5)));
}

Litterale& ARCCOS(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Arc Cosinus impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("ARCCOS("+l.getExpression()+')');
    return *new Reelle(3.1415926/2)+NEG(ARCSIN(l));
}

Litterale& ARCTAN(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Arc Tangente impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("ARCTAN("+l.getExpression()+')');
    if(typeid(l) == typeid(Complexe))
        return *new Reelle(0.5) * ($(*new Entiere(), *new Entiere(1))*(LN(*new Entiere(1) + NEG($(*new Entiere(), *new Entiere(1))*l))+NEG(LN(*new Entiere(1) + ($(*new Entiere(), *new Entiere(1))*l)))));
    return bonType(atan(l.getPartieReelle()));
}

Litterale& EXP(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Exponentielle impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("EXP("+l.getExpression()+')');
    if(typeid(l) == typeid(Complexe))
        return EXP(RE(l))* ($(COS(IM(l)), SIN(IM(l))));
    return bonType(exp(l.getPartieReelle()));
}

Litterale& LN(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Logarithme impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("LN("+l.getExpression()+')');
    if(typeid(l) == typeid(Complexe)){
        if(ARG(l).getPartieReelleNum()==0)
            return LN(NORM(l));
        return $(LN(NORM(l)), ARG(l));
    }

    if (l.getPartieReelle()<0 )
        throw ComputerException("Fonction ln non definie pour les nombres negatifs");

    return bonType(log(l.getPartieReelle()));
}

Litterale& SQRT(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
        throw ComputerException("Racine impossible avec cet operateur !");
    if (typeid(l) == typeid(Expression))
         return *new Expression("SQRT("+l.getExpression()+')');

    return POW(l,*new Reelle(0.5));
}

Litterale& NUM(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("NUM("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere))
        return l;
    if(typeid(l) == typeid(Rationnelle)){
         return *new Entiere(l.getPartieReelleNum());
    }
    throw ComputerException("Recuperation du numérateur impossible !");
}

Litterale& DEN(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("DEN("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere))
        return *new Entiere(1);
    if(typeid(l) == typeid(Rationnelle)){
        return *new Entiere(l.getPartieReelleDen());
    }
    throw ComputerException("Recuperation du denominateur impossible !");
}

Litterale& RE(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("RE("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere) || typeid(l) == typeid(Rationnelle) ||  typeid(l) == typeid(Reelle))
        return l;
    if(typeid(l) == typeid(Complexe))
        return bonType(l.getPartieReelleNum(),
                       l.getPartieReelleDen());
    throw ComputerException("Recuperation de la partie reelle impossible !");
}

Litterale& IM(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("IM("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere) || typeid(l) == typeid(Rationnelle) ||  typeid(l) == typeid(Reelle))
        return *new Entiere();
    if(typeid(l) == typeid(Complexe))
        return bonType(l.getPartieImNum(),
                       l.getPartieImDen());
    throw ComputerException("Recuperation de la partie imaginaire impossible !");
}

Litterale& NORM(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("NORM("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere) || typeid(l) == typeid(Rationnelle) ||  typeid(l) == typeid(Reelle) || typeid(l) == typeid(Complexe))
        return POW(POW(RE(l),*new Entiere(2))+POW(IM(l),*new Entiere(2)), *new Reelle(0.5));
    throw ComputerException("Calcul du module impossible !");
}

Litterale& ARG(Litterale& l){
    if (typeid(l) == typeid(Expression))
         return *new Expression("ARG("+l.getExpression()+')');
    if(typeid(l) == typeid(Entiere) || typeid(l) == typeid(Rationnelle) ||  typeid(l) == typeid(Reelle))
        return ARCTAN(*new Entiere());
    if(typeid(l) == typeid(Complexe))
        return ARCTAN(IM(l)/RE(l));
    throw ComputerException("Calcul de l argument impossible !");
}

Litterale& DIV(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression("DIV("+l1.getExpression()+','+l2.getExpression()+')');
    if (typeid(l1) == typeid(Entiere) && typeid(l2) == typeid(Entiere)){
        int e1 = static_cast<int>(l1.getPartieReelleNum());
        int e2 = static_cast<int>(l2.getPartieReelleNum());
        return *new Entiere(e1/e2);
    }

    else
        throw ComputerException("Calcul de division entiere impossible !");
}

Litterale& MOD(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression("MOD("+l1.getExpression()+','+l2.getExpression()+')');
    if (typeid(l1) == typeid(Entiere) && typeid(l2) == typeid(Entiere)){
        int e1 = static_cast<int>(l1.getPartieReelleNum());
        int e2 = static_cast<int>(l2.getPartieReelleNum());
        return *new Entiere(e1%e2);
    }

    else
        throw ComputerException("Calcul du modulo impossible !");
}

Litterale& operator!=(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme) || typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
        throw ComputerException("Operation logique impossible entre ces operateurs !");
    if(typeid(l1) == typeid(Complexe) || typeid(l2) == typeid(Complexe)){
        if(l1.getPartieReelle()!=l2.getPartieReelle() || l1.getPartieIm()!=l2.getPartieIm())
            return *new Entiere(1);
        else
            return *new Entiere(0);
    }

    if (l1.getPartieReelle() != l2.getPartieReelle())
        return *new Entiere(1);
    else
        return *new Entiere(0);
}

Litterale& operator<(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme) || typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
         throw ComputerException("Operation logique impossible entre ces operateurs !");
    if(typeid(l1) == typeid(Complexe) || typeid(l2) == typeid(Complexe)){
            if(typeid(l1) == typeid(Complexe) && typeid(l2) == typeid(Complexe))
                if(l1.getPartieReelle()<l2.getPartieReelle() && l1.getPartieIm()==l2.getPartieIm())
                    return *new Entiere(1);
                else
                    return *new Entiere(0);
            else
                throw ComputerException("Operation impossible !");
    }

    if (l1.getPartieReelle() < l2.getPartieReelle())
        return *new Entiere(1);
    else
        return *new Entiere(0);
}

Litterale& operator>(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme) || typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
         throw ComputerException("Operation logique impossible entre ces operateurs !");
    if(typeid(l1) == typeid(Complexe) || typeid(l2) == typeid(Complexe)){
            if(typeid(l1) == typeid(Complexe) && typeid(l2) == typeid(Complexe))
                if(l1.getPartieReelle()>l2.getPartieReelle() && l1.getPartieIm()==l2.getPartieIm())
                    return *new Entiere(1);
                else
                    return *new Entiere(0);
            else
                throw ComputerException("Operation impossible !");
    }

    if (l1.getPartieReelle() > l2.getPartieReelle())
        return *new Entiere(1);
    else
        return *new Entiere(0);
}

Litterale& AND(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
         throw ComputerException("Operation logique impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression("AND("+l1.getExpression()+','+l2.getExpression()+')');
    if(l1.getPartieReelle()==0 || l2.getPartieReelle()==0)
        return *new Entiere(0);
    else
        return *new Entiere(1);
}

Litterale& OR(Litterale& l1, Litterale& l2){
    if (typeid(l1) == typeid(Atome) || typeid(l2) == typeid(Atome) || typeid(l1) == typeid(Programme) || typeid(l2) == typeid(Programme))
         throw ComputerException("Operation logique impossible entre ces operateurs !");
    if (typeid(l1) == typeid(Expression) || typeid(l2) == typeid(Expression))
            return *new Expression("OR("+l1.getExpression()+','+l2.getExpression()+')');
    if(l1.getPartieReelle()==0 && l2.getPartieReelle()==0)
        return *new Entiere(0);
    else
        return *new Entiere(1);
}

Litterale& NOT(Litterale& l){
    if (typeid(l) == typeid(Atome) || typeid(l) == typeid(Programme))
         throw ComputerException("Operation logique avec cet operateur impossible !");
    if (typeid(l) == typeid(Expression))
            return *new Expression("NOT("+l.getExpression()+')');
    if(l.getPartieReelle()==0)
        return *new Entiere(1);
    else
        return *new Entiere(0);
}

void STO(Litterale& l,Litterale& ep){//l'expression déjà présente dans la pile est sans guillemets
    Expression* e = dynamic_cast<Expression*>(&ep);
    if(e == 0) throw ComputerException("Le deuxième argument doit être une expression");
    else{
        //****EXPRESSION NE DOIT PAS ETRE OPERATEUR PREDEFINI****////TODO vérifiez avec opérateurs logiques

        string atome = e->getExpression();
        string lit = l.getExpression();
        auto recherche1 = fonctions_unaires.find(lit);
        auto recherche2 = fonctions_binaires.find(lit);
        auto recherche3 = fonctions_pre_unaires.find(lit);
        auto recherche4 = fonctions_pre_binaires.find(lit);
        auto recherche5 = find (fonctions_pile.begin(), fonctions_pile.end(), lit);

        if(recherche1 != fonctions_unaires.end() || recherche2 != fonctions_binaires.end() ||
                recherche3 != fonctions_pre_unaires.end() || recherche4 != fonctions_pre_binaires.end() ||
                recherche5 != fonctions_pile.end()){
            //TODO verifier pas reservé
            throw ComputerException("Erreur : Identificateur réservé");

        }
        else{

            if(regex_match(atome, correcteSyntaxeAtome)){
                Numerique* p = dynamic_cast<Numerique*>(&l);
                Expression* p1 = dynamic_cast<Expression*>(&l);
                Programme* p2 = dynamic_cast<Programme*>(&l);
                if (p != 0 || p1 != 0 || p2 != 0){
                    Map[atome] = &l;
                    //on écrase ou on créé une nouvelle valeur
                }
                else {
                    Pile::getInstance().push(LitteraleManager::getInstance().ajoutLitterale(&l));
                    throw ComputerException("Littérale impossible à stocker (Complexe, Atome...)");
                }
           }
           else {
            Pile::getInstance().push(LitteraleManager::getInstance().ajoutLitterale(&l));
            throw  ComputerException("Erreur Atome");
           }
        }
     }
}

void EVAL(Litterale& l){
    Expression* lp = dynamic_cast<Expression*>(&l);
    if(lp != 0) {
        std::string chaineResult="";
        std::queue<string> Result = lp->shuntingYard();
        while(!Result.empty()) {chaineResult+=Result.front() + " ";Result.pop();}
        //Equivalent de traitementLigne(chaineResult);
        lp->traitementRPN(chaineResult);

    }
    else{
            Programme* lp = dynamic_cast<Programme*>(&l);
            if(lp!=0){
                lp->traitementRPN(lp->getContenu(),true);
            }
            else {
                Pile& Pile = Pile::getInstance();
                LitteraleManager& litMng = LitteraleManager::getInstance();
                Pile.push(litMng.ajoutLitterale(&l));
                throw ComputerException("EVAL ne peut pas être appliquée");
            }
    }


}


/// <summary>
/// Indique si un nombre est numerique
/// </summary>
/// <param name="s">Chaine en entrée</param>
/// <returns>Vrai si la chaine est un numérique avec un séparateur '.' </returns>
bool EstNumerique(string s)
{

    for ( int c = 0; c < (int) s.length(); ++c ) {
        if(!isdigit(s[c]) && s[c] != '.') return false;

    }
    return true;
}
/// <summary>
/// Indique si un caractere fait parti des caractère acceptés pour construire un numerique
/// </summary>
/// <param name="s">Caractère en entrée</param>
/// <returns>Vrai si le caractère est un numérique ou un séparateur '.' </returns>
bool EstNumerique(char c)
{
    if (isdigit(c) || c == '.')
    {
        return true;
    }
    return false;
}
/// <summary>
/// Indique si un nombre est un entier
/// </summary>
/// <param name="s">Chaine en entrée</param>
/// <returns>Vrai si le caractère est un entier</returns>
bool EstEntier(string s)
{
    for ( int i = 0; i < (int) s.size(); ++i )
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}


/// <summary>
/// Permet de déterminer si la chaine correspond à un opérateur
/// </summary>
/// <param name="chaine">Chaine à tester</param>
/// <returns>Vrai s'il s'agit d'un opérateur référencé, Faux sinon</returns>
bool EstOperateur(string chaine)
{
    if(chaine.length() > 1) return false;
    else{
        auto recherche = operateurs_arithmetiques.find(chaine);
        return recherche != operateurs_arithmetiques.end();
    }
}
/// <summary>
/// Permet de déterminer si la chaine correspond à une fonction UNIQUEMENT SI LA CHAINE VIENT DU STACK
/// Cette FCT Factorise simplement du code, rien de plus
/// </summary>
/// <param name="chaine">Chaine en entrée à identifier</param>
/// <returns>Vrai s'il s'agit d'une fonction, Faux sinon</returns>
/// <remarks>Cette fonction permet uniquement de factoriser du code</remarks>
bool EstFonction(string caractere)//TODO ajouter fonctions manipulation e pile
{

    auto recherche1 = fonctions_unaires.find(caractere);
    auto recherche2 = fonctions_binaires.find(caractere);
    auto recherche3 = fonctions_pre_unaires.find(caractere);
    auto recherche4 = fonctions_pre_binaires.find(caractere);
    auto recherche5 = find (fonctions_pile.begin(), fonctions_pile.end(), caractere);
    return (!EstOperateur(caractere) && caractere != "(" && caractere != ")" && caractere != "," &&
            caractere != "." && (recherche1 != fonctions_unaires.end() || recherche2 != fonctions_binaires.end() ||
            recherche3 != fonctions_pre_unaires.end() || recherche4 != fonctions_pre_binaires.end() ||
            recherche5 != fonctions_pile.end()));
}
