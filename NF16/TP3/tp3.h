#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
#define MAX 15

struct Livre{
    char titre[MAX];
    char auteur[MAX];
    char edition[MAX];
    char theme_rayon[MAX];
    int disponible;
    struct Livre *suivant;
};

typedef struct Livre T_Livre;

struct Rayon{
    char theme_rayon[MAX];
    int nombre_livres;
    struct Livre *premier;
    struct Rayon *suivant;
};

typedef struct Rayon T_Rayon;

struct Biblio{
    char nom[MAX];
    struct Rayon *premier;
};

typedef struct Biblio T_Biblio;

T_Livre *creerLivre (char *titre, char *auteur, char *edition, char *theme_rayon);

T_Rayon *creerRayon (char *theme);

T_Biblio *creerBiblio (char *nom);

int ajouterLivre(T_Rayon *rayon, T_Livre *livre);

int ajouterRayon(T_Biblio *biblio, T_Rayon *rayon);

void afficherBiblio(T_Biblio *biblio);

void afficherRayon(T_Rayon *rayon);

int emprunterLivre(T_Rayon *rayon, char* titre);

int supprimerLivre(T_Rayon *rayon, char* titre);

int supprimerRayon(T_Biblio *biblio, char *nom_rayon);

void rechercherLivres(T_Biblio *biblio, char* critereTitre);

void traiterListeEmprunts(T_Biblio *biblio);

T_Livre *initialisationLivre();

int rechercheLivre(T_Rayon *rayon, char* titre);

T_Rayon *rechercheRayon(T_Biblio *biblio, char* theme_rayon);

int rechercheBiblio(T_Biblio *biblio);

void lire(char *chaine, int longueur);

int testEntree(char* choix);

#endif // TP3_H_INCLUDED
