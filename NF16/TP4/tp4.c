#include "tp4.h"

Noeud * insererNoeud(int n, Noeud *root){
    Noeud * courant = root;
    Noeud * precedent = NULL;

    if (courant == NULL)
        return creerNoeud(n);

    while (courant != NULL && courant->cle != n){
        if (n > courant->cle){
            precedent = courant;
            courant = courant->droit;
        }
        else{
            precedent = courant;
            courant = courant->gauche;
        }
    }

    if (courant == NULL){
        if (n > precedent->cle)
            precedent->droit = creerNoeud(n);
        else
            precedent->gauche = creerNoeud(n);
    }

    return root;
}

Noeud * insererNoeud_rec (int n, Noeud *root){
    if (root == NULL)
        root = creerNoeud(n);
    if (n > root->cle)
        root->droit = insererNoeud_rec(n, root->droit);
    if (n < root->cle)
        root->gauche = insererNoeud_rec(n, root->gauche);

    return root;
}

int verifier (Noeud *root){
    int tmp;
    if (root == NULL)
        return 1;
    if ((root -> gauche == NULL) && (root ->droit == NULL))
        return 1;
    else{
        if(root -> gauche != NULL){
            if (maxArbre(root->gauche) < root->cle){
                tmp = verifier(root->gauche);
                if(tmp == 0)
                    return 0;
            }
            else
                return 0;
        }
        if(root -> droit != NULL){
            if (minArbre(root->droit) > root->cle){
                tmp = verifier(root->droit);
                if(tmp == 0)
                    return 0;
            }
            else
                return 0;
        }
    }
    return 1;
}

Noeud * recherche (int n, Noeud * root){
    Noeud * courant = root;

    while (courant != NULL && courant->cle != n){
        if (n > courant->cle)
            courant = courant->droit;
        else
            courant = courant->gauche;
    }
    return courant;
}

Noeud * recherche_rec (int n, Noeud * root){
    Noeud * courant = root;
    if ((courant == NULL) || (n == courant->cle))
        return courant;
    if (n > courant->cle)
        recherche_rec(n, courant->droit);
    else
        recherche_rec(n, courant->gauche);
}

int hauteur (Noeud * root){
    Noeud * courant = root;

    if (courant == NULL)
        return -1;
    return 1 + maximum(hauteur(courant->droit), hauteur(courant->gauche));
}

int somme (Noeud * root){
    Noeud * courant = root;

    if (courant == NULL)
        return 0;
    return courant->cle + somme(courant->droit) + somme(courant->gauche);
}

void afficherDecroissant (Noeud * root){
    if(root != NULL){
        afficherDecroissant(root->droit);
        printf("%d ", root->cle);
        afficherDecroissant(root->gauche);
    }
}

void afficherStructure (Noeud * root){
    printf("{");
    if(root != NULL){
        if(root->gauche != NULL){
            if(root->gauche->gauche != NULL || root->gauche->droit != NULL)
                afficherStructure(root->gauche);
            else
                printf("%d", root->gauche->cle);
        }

        if (root ->gauche == NULL)
            printf("_");
        printf(", %d, ", root->cle);
        if (root ->droit == NULL)
            printf("_");


        if(root->droit != NULL){
            if(root->droit->droit != NULL || root->droit->gauche != NULL)
                afficherStructure(root->droit);
            else
                printf("%d", root->droit->cle);
        }
    }
    printf("}");
}

Noeud * supprimer (int n, Noeud * root){
    int c;
    Noeud * courant = root;
    Noeud * precedent = NULL;

    while (courant != NULL && courant->cle != n){
        precedent = courant;
        if (n > courant->cle){
            courant = courant->droit;
            c = 1;
        }
        else{
            courant = courant->gauche;
            c = 0;
        }
    }
    if ((courant == NULL) || (courant->cle != n)){
        printf("\nLa valeur n'existe pas.");
        return root;
    }
    else{
        //aucun fils
        if (courant->droit == NULL && courant->gauche == NULL){
            //Pas la racine
            if(precedent != NULL){
                if (c == 0)
                    precedent->gauche = NULL;
                else
                    precedent->droit = NULL;
                free(courant);
                return root;
            }
            //la racine
            free(courant);
            return NULL;
        }
        if (courant->droit != NULL){
            //un fils droit
            if(courant->gauche == NULL){
                if(precedent != NULL){
                    if (c == 0)
                        precedent->gauche = courant->droit;
                    else
                        precedent->droit = courant->droit;
                }
                else
                    root = courant->droit;
            }
            //deux fils
            else{
                if (hauteur(courant->droit) > hauteur(courant->gauche)){
                    courant->cle = minArbre(courant->droit);
                    courant->droit = supprimer(courant->cle, courant->droit);
                }
                else{
                    courant->cle = maxArbre(courant->gauche);
                    courant->gauche = supprimer(courant->cle, courant->gauche);
                }
            }
            return root;
        }
        //un fils gauche
        if(precedent != NULL){
            if (c == 0)
                precedent->gauche = courant->gauche;
            else
                precedent->droit = courant->gauche;
        }
        else
            root = courant->gauche;
        free(courant);
        return root;
    }
}

void detruire (Noeud * root){
    if (root != NULL){
        if(root->gauche != NULL)
                detruire(root->gauche);
        if(root->droit != NULL)
                detruire(root->droit);
        free(root);
    }
}

Noeud * construire (int Tab[], int indiceDebut, int indiceFin){
    if(indiceDebut<=indiceFin){
        int indice = (indiceDebut+indiceFin)/2;
        Noeud * root = creerNoeud(Tab[indice]);
        root->gauche = construire(Tab, indiceDebut, indice-1);
        root->droit = construire(Tab, indice+1, indiceFin);
        return root;
    }
    else
        return NULL;
}

Noeud * creerNoeud(int n){
    Noeud * noeud = (Noeud*) malloc (sizeof(struct Noeud));

    noeud->cle = n;
    noeud->gauche = NULL;
    noeud->droit = NULL;

    return noeud;
}

int maxArbre (Noeud* root){
    Noeud * noeud = root;
    if (noeud == NULL)
        return -1;
    while (noeud->droit != NULL){
        noeud = noeud->droit;
    }
    return noeud->cle;
}

int minArbre (Noeud* root){
    Noeud * noeud = root;
    if (noeud == NULL)
        return -1;
    while (noeud->gauche != NULL){
        noeud = noeud->gauche;
    }
    return noeud->cle;
}


int maximum(int n, int m){
    if(n>m)
        return n;
    return m;
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

int testMenu(char* choix){
    int i = 0;
    while(i != strlen(choix)){
        if (choix[i]<'0' || choix[i]>'9')
            return 0;
        i++;
    }
    i = atoi(choix);
    if(i<13)
        return 1;
    return 0;
}


int testChiffre(char* chaine){
    int i = 0;
    while(i != strlen(chaine)){
        if (chaine[i]<'0' || chaine[i]>'9')
            return 0;
        i++;
    }
    return 1;
}

int rechercheArbre(Noeud * root){
    if(root == NULL){
        printf("Veuiller d'abord inserer un noeud racine.");
        return 1;
    }
    return 0;
}
