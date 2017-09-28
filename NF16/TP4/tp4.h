#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED
#define MAX 10
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Noeud{
    int cle;
    struct Noeud * gauche;
    struct Noeud * droit;
};

typedef struct Noeud Noeud;

Noeud * insererNoeud (int n, Noeud * root);

Noeud * insererNoeud_rec (int n, Noeud * root);

int verifier (Noeud * root);

Noeud * recherche (int n, Noeud * root);

Noeud * recherche_rec (int n, Noeud * root);

int hauteur (Noeud * root);

int somme (Noeud * root);

void afficherDecroissant (Noeud * root);

void afficherStructure (Noeud * root);

Noeud * supprimer (int n, Noeud * root);

void detruire (Noeud * root);

Noeud * construire (int Tab[], int indiceDebut, int indiceFin);

Noeud * creerNoeud(int n);

int maxArbre (Noeud * root);

int minArbre (Noeud * root);

int maximum(int n, int m);

void lire(char *chaine, int longueur);

int testMenu(char* choix);

int testChiffre(char* chaine);

int rechercheArbre(Noeud * root);

#endif // TP4_H_INCLUDED
