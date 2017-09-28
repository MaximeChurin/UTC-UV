#include "tp4.h"
# define clear system("cls")

int main(){
    Noeud * root = NULL;
    int cle;

    char choix[MAX];
    char chaine[MAX];
    int premier = 0;

    do {
    clear;
    printf("Menu Principal : \n\n");
    printf("1. Inserer un noeud (iteratif)\n");
    printf("2. Inserer un noeud (recursif)\n");
    printf("3. Verifier l'ABR\n");
    printf("4. Rechercher un noeud (iteratif)\n");
    printf("5. Rechercher un noeud (recursif)\n");
    printf("6. Connaitre la hauteur de l'arbre\n");
    printf("7. Faire la somme des noeuds\n");
    printf("8. Afficher les noeuds par ordre decroissant\n");
    printf("9. Afficher la structure\n");
    printf("10. Supprimer un noeud\n");
    printf("11. Supprimer l'arbre\n");
    printf("12. Construire arbre a partir d'un tableau trie\n");
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
    }while(testMenu(choix) == 0);
    clear;

    premier = atoi(choix);

    switch (premier){
        case 1 :
            printf("Entrez la valeur du noeud : ");
            lire(chaine, MAX);
            if (testChiffre(chaine) == 1){
                cle = atoi(chaine);
                root = insererNoeud(cle,root);
                printf("\n");
                printf("Le noeud %s a bien ete inserer.",chaine);
            }
            else
                printf("\nValeur saisie incorrecte. ");
            break;
        case 2 :
            printf("Entrez la valeur du noeud : ");
            lire(chaine, MAX);
            if (testChiffre(chaine) == 1){
                cle = atoi(chaine);
                root = insererNoeud_rec(cle,root);
                printf("\n");
                printf("Le noeud %s a bien ete inserer.",chaine);
            }
            else
                printf("\nValeur saisie incorrecte. ");
            break;
        case 3 :
            if(rechercheArbre(root) != 1){
                if(verifier(root) == 0)
                        printf("Ce n'est pas un ABR.");
                else
                        printf("C'est un ABR.");
            }
            break;
        case 4 :
            if(rechercheArbre(root) != 1){
                printf("Entrez la valeur du noeud : ");
                lire(chaine, MAX);
                if (testChiffre(chaine) == 1){
                    cle = atoi(chaine);
                    printf("\n");
                    if(recherche(cle, root) == NULL)
                        printf("Le noeud %s n'existe pas dans l'ABR.",chaine);
                    else
                        printf("Le noeud %s existe dans l'ABR.",chaine);
                }
                else
                    printf("\nValeur saisie incorrecte. ");
            }
            break;
        case 5 :
            if(rechercheArbre(root) != 1){
                printf("Entrez la valeur du noeud : ");
                lire(chaine, MAX);
                if (testChiffre(chaine) == 1){
                    cle = atoi(chaine);
                    printf("\n");
                    if(recherche_rec(cle, root) == NULL)
                        printf("Le noeud %s n'existe pas dans l'ABR.",chaine);
                    else
                        printf("Le noeud %s existe dans l'ABR.",chaine);
                }
                else
                    printf("\nValeur saisie incorrecte. ");
            }
            break;
        case 6 :
            if(rechercheArbre(root) != 1)
                printf("La hauteur de l'ABR est %d.", hauteur(root));
            break;
        case 7 :
            if(rechercheArbre(root) != 1)
                printf("La somme des noeuds de l'ABR est %d.", somme(root));
            break;
        case 8 :
            if(rechercheArbre(root) != 1)
                afficherDecroissant(root);
            break;
        case 9 :
            if(rechercheArbre(root) != 1)
                afficherStructure(root);
            break;
        case 10 :
            if(rechercheArbre(root) != 1){
                printf("Entrez la valeur du noeud : ");
                lire(chaine, MAX);
                if (testChiffre(chaine) == 1){
                    cle = atoi(chaine);
                    root = supprimer(cle, root);
                    printf("\nLe noeud %d a bien ete supprime.", cle);
                }
                else
                    printf("\nValeur saisie incorrecte. ");
            }
            break;
        case 11 :
            if(rechercheArbre(root) != 1){
                detruire(root);
                root = NULL;
                printf("Arbre supprime.");
            }
            break;
        case 12 :
            if (root != NULL){
                detruire(root);
                root = NULL;
            }
            int t[]={5,10,15,20,25,35,45,60,65};
            root = construire(t, 0, 8);
            printf("Arbre bien creer.");
            break;
        default :
            printf("Au revoir !");
    }
    getchar();
    fflush(stdin);
    premier = 0;
    }while(choix[0] != '0');

    return 0;
}


