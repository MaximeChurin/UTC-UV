#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
#include <math.h>

T_Livre *creerLivre (char *titre, char *auteur, char *edition, char *theme_rayon){
    T_Livre *livre = (T_Livre*) malloc (sizeof(T_Livre));

    strncpy(livre->titre, titre, MAX - 1);
    strncpy(livre->auteur, auteur, MAX - 1);
    strncpy(livre->edition, edition, MAX - 1);
    strncpy(livre->theme_rayon, theme_rayon, MAX - 1);

    livre->titre[MAX - 1] = '\0';
    livre->auteur[MAX - 1] = '\0';
    livre->edition[MAX - 1] = '\0';
    livre->theme_rayon[MAX - 1] = '\0';

    livre->disponible = 1;
    livre->suivant = NULL;

    return livre;
}

T_Rayon *creerRayon (char *theme){
    T_Rayon *rayon = (T_Rayon*) malloc (sizeof(T_Rayon));

    strncpy(rayon->theme_rayon, theme, MAX - 1);

    rayon->theme_rayon[MAX - 1] = '\0';

    rayon->nombre_livres = 0;
    rayon->premier = NULL;
    rayon->suivant = NULL;

    return rayon;
}

T_Biblio *creerBiblio (char *nom){
    T_Biblio *biblio  = (T_Biblio*) malloc (sizeof(T_Biblio));

    strncpy(biblio ->nom, nom, MAX-1);

    biblio ->nom[MAX - 1] = '\0';

    biblio->premier = NULL;

    return biblio;
}

int ajouterLivre(T_Rayon *rayon, T_Livre *livre){
    T_Livre *livre_courant = rayon->premier;
    T_Livre *livre_precedent = NULL;
    int cmp = 1;

    while( (livre_courant != NULL) && (cmp = strcmp(livre_courant->titre, livre->titre) ) < 0){
            livre_precedent = livre_courant;
            livre_courant = livre_courant->suivant;
    }
     if ((cmp == 0) && strcmp(livre_courant->theme_rayon, livre->theme_rayon) == 0)
        return 0;
    else{
        livre->suivant = livre_courant;

        if(livre_precedent != NULL)
            livre_precedent->suivant = livre;
        else
            rayon->premier = livre;
        rayon->nombre_livres++;
    }
    return 1;
}

int ajouterRayon(T_Biblio *biblio, T_Rayon *rayon){
    T_Rayon *rayon_courant = biblio->premier;
    T_Rayon *rayon_precedent = NULL;
    int cmp = 1;

    while( (rayon_courant != NULL) && (cmp = strcmp(rayon_courant->theme_rayon, rayon->theme_rayon) ) < 0){
            rayon_precedent = rayon_courant;
            rayon_courant = rayon_courant->suivant;
    }
    if (cmp ==0)
        return 0;
    else{
        rayon->suivant = rayon_courant;

        if(rayon_precedent != NULL)
            rayon_precedent->suivant = rayon;
        else
            biblio->premier = rayon;
    }
    return 1;
}

void afficherBiblio(T_Biblio *biblio){
    T_Rayon *rayon = biblio->premier;
    char nom[]="Nom", nombre[]="Nombre de livres";

    if(rayon == NULL)
        printf("Il n'y a pas de rayon dans cette bibliotheque\n");
    else
        printf("%s%*s \n\n", nom, MAX-strlen(nom)+strlen(nombre), nombre);
    while(rayon != NULL){
        printf("%s%*d \n", rayon->theme_rayon, MAX-strlen(rayon->theme_rayon)+1, rayon->nombre_livres);
        rayon = rayon->suivant;
    }
    printf("\n");
}

void afficherRayon(T_Rayon *rayon){
    T_Livre *livre = rayon->premier;
    int premier = 0;
    char titre[]="Titre", auteur[]="Auteur", edition[]="Edition", disponibilite[]="Disponibilite";

    if(rayon->nombre_livres == 0)
        printf("Il n'y a aucun livre dans ce rayon.");

    while( livre != NULL){
        if (premier ==0)
            printf("%s%*s%*s%*s \n\n", titre, MAX-strlen(titre)+strlen(auteur), auteur, MAX-strlen(auteur)+strlen(edition), edition, MAX-strlen(edition)+strlen(disponibilite), disponibilite);
        printf("%s", livre->titre);
        printf("%*s", MAX-strlen(livre->titre)+strlen(livre->auteur), livre->auteur);
        printf("%*s", MAX-strlen(livre->auteur)+strlen(livre->edition), livre->edition);
        if (livre->disponible == 1)
            printf("%*s\n", MAX-strlen(livre->edition)+3, "Oui");
        else
            printf("%*s\n", MAX-strlen(livre->edition)+3, "Non");

        livre = livre->suivant;
        premier = 1;
    }
    printf("\n");
}

int emprunterLivre(T_Rayon *rayon, char* titre){
    T_Livre *livre = rayon->premier;
    int cmp = 1;

    while( (livre != NULL) && (cmp = strcmp(livre->titre, titre) ) != 0){
            livre = livre->suivant;
    }
    if ( (cmp == 0) && (livre->disponible == 1)){
            livre->disponible = 0;
            return 1;
    }
    return 0;
}

int supprimerLivre(T_Rayon *rayon, char* titre){
    T_Livre *livre_courant = rayon -> premier;
    T_Livre *livre_precedent=NULL;

    int cmp = 1;

    while( (livre_courant != NULL) && (cmp = strcmp(livre_courant->titre, titre) ) != 0){
        livre_precedent=livre_courant;
        livre_courant=livre_courant->suivant;
    }
    if (cmp == 0){
        if(livre_precedent==NULL){
            rayon->premier=livre_courant->suivant;
            free((T_Livre*)livre_courant);
        }
        else{
            livre_precedent->suivant=livre_courant->suivant;
            free((T_Livre*)livre_courant);
        }
        rayon->nombre_livres--;
        return 1;
    }
    return 0;
}

int supprimerRayon(T_Biblio *biblio, char *nom_rayon){
    T_Rayon *rayon_courant = biblio->premier;
    T_Rayon *rayon_precedent = NULL;

    int cmp = 1;

    while( (rayon_courant != NULL) && (cmp = strcmp(rayon_courant->theme_rayon, nom_rayon) ) != 0){
        rayon_precedent=rayon_courant;
        rayon_courant=rayon_courant->suivant;
    }
    if (cmp == 0){
        while (rayon_courant->premier != NULL)
            supprimerLivre(rayon_courant, rayon_courant->premier->titre);
        if(rayon_precedent==NULL){
            biblio->premier=rayon_courant->suivant;
            free((T_Rayon*)rayon_courant);
        }
        else{
            rayon_precedent->suivant=rayon_courant->suivant;
            free((T_Rayon*)rayon_courant);
        }
        return 1;
    }
    return 0;
}

void rechercherLivres(T_Biblio *biblio, char* critereTitre){
    char c[]="tmp", titre[]="Titre", auteur[]="Auteur", edition[]="Edition", disponibilite[]="Disponibilite", Rayon[]="Rayon";

    T_Rayon *rayon = biblio->premier, *tmp = creerRayon(c);
    T_Livre *livre_courant, *livre;

    while(rayon != NULL){
        livre_courant = rayon->premier;
        while(livre_courant != NULL){
            if (strncmp(livre_courant->titre, critereTitre, strlen(critereTitre)) == 0){
                livre = creerLivre(livre_courant->titre,livre_courant->auteur,livre_courant->edition,rayon->theme_rayon);
                ajouterLivre(tmp, livre);
            }
            livre_courant = livre_courant->suivant;
        }
        rayon = rayon->suivant;
    }

    livre = tmp->premier;

    if (tmp->nombre_livres == 0)
        printf("Aucun resultat ne correspond a votre recherche.");
    else{
        printf("%s%*s%*s%*s%*s \n\n", titre, MAX-strlen(titre)+strlen(auteur), auteur, MAX-strlen(auteur)+strlen(edition), edition, MAX-strlen(edition)+strlen(disponibilite), disponibilite, MAX-strlen(disponibilite)+strlen(Rayon), Rayon);
        while( livre != NULL){
            printf("%s", livre->titre);
            printf("%*s", MAX-strlen(livre->titre)+strlen(livre->auteur), livre->auteur);
            printf("%*s", MAX-strlen(livre->auteur)+strlen(livre->edition), livre->edition);
            if (livre->disponible == 1)
                printf("%*s", MAX-strlen(livre->edition)+3, "Oui");
            else
                printf("%*s", MAX-strlen(livre->edition)+3, "Non");
            printf("%*s\n", MAX-3+strlen(livre->theme_rayon), livre->theme_rayon);

            livre = livre->suivant;
        }
    }
}

void traiterListeEmprunts(T_Biblio *biblio){
    char emprunt[MAX], chaine[MAX], titre[MAX];
    char Titre[]="Titre", disponibilite[]="Disponibilite", vide[]="", Rayon[]="Rayon";

    T_Rayon *rayon, *tmp = creerRayon(vide);
    T_Livre* livre = NULL;

    do{
        printf("Entrez le nom du rayon : ");
        lire(chaine, MAX);
        printf("\n");
        fflush(stdin);
        rayon = rechercheRayon(biblio, chaine);
        if(rayon != NULL){
            printf("Entrez le titre du livre : ");
            lire(titre, MAX);
            printf("\n");
            if(rechercheLivre(rayon, titre)==0)
                    printf("Ce livre n'existe pas dans le rayon. \n\n");
            else{
                livre = creerLivre(titre, vide, vide, rayon->theme_rayon);
                livre->disponible = emprunterLivre(rayon, titre);
                if (ajouterLivre(tmp, livre) == 0)
                    printf("Livre deja dans la liste d'emprunt.\n\n");
            }
        }

        printf("Voulez vous poursuivre les emprunts (1 pour continuer) ? ");
        lire(emprunt, MAX);
        printf("\n");
        fflush(stdin);
    }while (emprunt[0]=='1' && emprunt[1]=='\0');

    if (tmp->nombre_livres != 0){
        printf("%s%*s%*s \n\n", Titre, MAX-strlen(Titre)+strlen(Rayon), Rayon, MAX-strlen(Rayon)+strlen(disponibilite), disponibilite);
        livre = tmp->premier;
        while (livre != NULL){
            printf("%s", livre->titre);
            printf("%*s", MAX-strlen(livre->titre)+strlen(livre->theme_rayon), livre->theme_rayon);
            if (livre->disponible == 1)
                printf("%*s\n", MAX-strlen(livre->theme_rayon)+3, "Oui");
            else
                printf("%*s\n", MAX-strlen(livre->theme_rayon)+3, "Non");
            livre = livre->suivant;
        }
    }
    else
        printf("Vous n'avez pas empruntez de livre.");
}

T_Livre *initialisationLivre(){
            char titre[MAX], auteur[MAX], edition[MAX], theme_rayon[]="";
            printf("Entrez le titre du livre : ");
            lire(titre, MAX);
            fflush(stdin);
            printf("\n");
            printf("Entrez l'auteur du livre : ");
            lire(auteur, MAX);
            fflush(stdin);
            printf("\n");
            printf("Entrez l'edition du livre : ");
            lire(edition, MAX);
            printf("\n");

            return creerLivre(titre, auteur, edition, theme_rayon);
}

int rechercheLivre(T_Rayon *rayon, char* titre){
    T_Livre *livre = rayon->premier;
    int cmp = 1;

    while( (livre != NULL) && (cmp = strcmp(livre->titre, titre) ) != 0)
        livre = livre->suivant;

     if (cmp == 0)
        return 1;
    return 0;
}

T_Rayon *rechercheRayon(T_Biblio *biblio, char* theme_rayon){
     T_Rayon *rayon = biblio->premier;
     int cmp = 1;

    while( (rayon != NULL) && (cmp = strcmp(rayon->theme_rayon, theme_rayon) ) != 0)
        rayon = rayon->suivant;

     if (cmp == 0)
            return rayon;
    printf("Ce Rayon n'existe pas. \n\n");
    return NULL;
}

int rechercheBiblio(T_Biblio *biblio){
    if(biblio == NULL){
        printf("Veuiller d'abord creer une bibliotheque.");
        return 1;
    }
    return 0;
}

void lire(char *chaine, int longueur){
    char *positionEntree = NULL;
    int i = 0;
    do{
        if (i != 0)
            printf("\nEntree non valide, veuillez recommencer : ");
        if (fgets(chaine, longueur, stdin) != NULL){
            positionEntree = strchr(chaine, '\n');
            if (positionEntree != NULL)
                *positionEntree = '\0';
            i = 1;
        }
    }
    while((chaine[0]=='\0')||(chaine[0]==' '));
    fflush(stdin);
}

int testEntree(char* choix){
    if (choix[0]>='0' && choix[0]<='9')
        return 1;
    return 0;
}
