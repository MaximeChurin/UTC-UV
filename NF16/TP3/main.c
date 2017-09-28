#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"
# define clear system("cls")

int main(){
    T_Biblio* biblio = NULL;

    char choix[MAX];
    int premier = 0;
    char chaine[MAX];
    char titre[MAX];

    do {
    clear;
    printf("Menu Principal : \n\n");
    printf("1. Creer une bibliotheque\n");
    printf("2. Ajouter un rayon a la bibliotheque\n");
    printf("3. Ajouter un livre dans un rayon\n");
    printf("4. Afficher les rayons de la bibliotheque\n");
    printf("5. Afficher les livres d'un rayon\n");
    printf("6. Retirer un livre\n");
    printf("7. Supprimer un rayon\n");
    printf("8. Rechercher un livre par son titre\n");
    printf("9. Emprunter une liste de livres\n");
    printf("0. Quitter\n\n");
    do{
        if(premier == 0)
            printf("Entrez votre choix : ");
        else
            printf("Entree non valide, veuillez recommencer : ");
        lire(choix, MAX);
        printf("\n");
        fflush(stdin);
        premier = 1;
    }while(testEntree(choix) == 0 || choix[1]!='\0' );
    clear;

    switch (choix[0]){
        case '1' :
            printf("Entrez le nom de la bibliotheque : ");
            lire(chaine, MAX);
            printf("\n");
            if((biblio = creerBiblio(chaine))!=NULL)
                printf("La bibliotheque %s a bien etait creee.",chaine);
            break;
        case '2' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez le nom du rayon : ");
                lire(chaine, MAX);
                printf("\n");
                if(ajouterRayon(biblio, creerRayon(chaine))==0)
                   printf("Rayon deja existant.");
                else
                    printf("Le rayon %s a bien ete cree.",chaine);
            }
            break;
        case '3' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez le nom du rayon du livre : ");
                lire(chaine, MAX);
                printf("\n");
                fflush(stdin);
                if(rechercheRayon(biblio, chaine) != NULL){
                    if(ajouterLivre(rechercheRayon(biblio, chaine),initialisationLivre()) == 0)
                        printf("Desole ce titre existe deja.");
                    else
                        printf("Le livre a bien ete ajoute.");
                }
            }
            break;
        case '4' :
            if(rechercheBiblio(biblio) != 1)
                afficherBiblio(biblio);
            break;
        case '5' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez le nom du rayon : ");
                lire(chaine, MAX);
                printf("\n");
                if(rechercheRayon(biblio, chaine) != NULL)
                    afficherRayon(rechercheRayon(biblio, chaine));
            }
            break;
        case '6' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez le nom du rayon : ");
                lire(chaine, MAX);
                printf("\n");
                fflush(stdin);
                if(rechercheRayon(biblio, chaine) != NULL){
                    printf("Entrez le titre du livre : ");
                    lire(titre, MAX);
                    printf("\n");
                    if(rechercheLivre(rechercheRayon(biblio, chaine), titre)==0)
                        printf("Ce livre n'existe pas dans le rayon.");
                    else
                        if(emprunterLivre(rechercheRayon(biblio, chaine), titre)== 0)
                            printf("Livre deja emprunte.");
                        else
                            printf("L'emprunt c'est bien passe.");
                }
            }
            break;
        case '7' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez le nom du rayon : ");
                lire(chaine, MAX);
                printf("\n");
                if(supprimerRayon(biblio, chaine)==0)
                    printf("Ce Rayon n'existe pas.");
                else
                    printf("Ce rayon a bien ete supprime.");
            }
            break;
        case '8' :
            if(rechercheBiblio(biblio) != 1){
                printf("Entrez la chaine a rechercher dans le titre : ");
                lire(titre, MAX);
                printf("\n");
                rechercherLivres(biblio, titre);
            }
            break;
        case '9' :
            if(rechercheBiblio(biblio) != 1)
                traiterListeEmprunts(biblio);
            break;
        default :
            printf("Au revoir !\n");
    }
    getchar();
    fflush(stdin);
    premier = 0;
    }while(choix[0]>='1' && choix[0]<='9');

    return 0;
}
