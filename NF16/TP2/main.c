#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 100
#define NMAX 100
#define PI 3.14159

typedef int matrice[MAX][MAX];

void lire_Matrice(matrice m, int dimension){
    int i,j;
    for (i=0; i<dimension; i++)
            for (j=0; j<dimension; j++){
                printf("Entrez le nombre de la case [%d][%d]: \n",i+1, j+1);
                scanf("%d", &m[i][j]);
            }
}

void afficher_Matrice(matrice m, int dimension){
    int i,j;
    for (i=0; i<dimension; i++){
            for (j=0; j<dimension; j++)
                printf("%d \t",m[i][j]);
    printf("\n");
    }
}

void sous_Matrice(matrice m, matrice sm, int dimension, int indice){
    int i, j;
    for (i=0; i<dimension-1; i++){
                for (j=0; j<indice; j++)
                    sm[j][i]= m[j][i+1];

                for (j=indice+1; j<dimension; j++)
                    sm[j-1][i]= m[j][i+1];
    }
}

int determinant_Matrice(matrice m, int dimension){
    matrice sm;
    int i
    double det=0.0;
    if (dimension==1)
        return m[0][0];

    for(i=0; i<dimension; i++){
        sous_Matrice(m, sm, dimension, i);
        det += pow(-1,i)*m[i][0]*determinant_Matrice(sm, dimension-1);
    }
    return det;
}

int fibo1(int n){
    if (n==0)
        return 0;
    if (n==1)
        return 1;
    if (n>1)
        return fibo1(n-1) + fibo1(n-2);

}

int fibo2(int n){
    if (n==0)
        return 0;
    if (n==1)
        return 1;
    if (n>1){
        if (n%2!=0)
            return fibo2((n-1)/2)*fibo2((n-1)/2)+fibo2(((n-1)/2)+1)*fibo2(((n-1)/2)+1);
        else
            return fibo2(n/2)*fibo2(n/2)+2*fibo2(n/2)*fibo2((n/2)-1);
    }
}

typedef struct{
    int Un_Tableau_Entier[NMAX];
    int ncase = 0;
}tableau;

typedef struct{
    char menu[20][60];
    int n;
}menu;

typedef struct {
    float d;
    float D;
    float L;
    char c[20];
}Tonneau;

void main(){
    /*
    //Exo 1.3
    int dimension, i;
    matrice m;

    printf("Entrez la taille de la matrice a saisir (<100) :\n");
    scanf("%d",&dimension);

    lire_Matrice(m, dimension);
    printf("\n");
    afficher_Matrice(m, dimension);
    printf("Le determinant de la matrice est %d", determinant_Matrice(m, dimension));

    //Exo 1.4
    int n;
    printf("Entrez un entier :\n");
    scanf("%d", &n);
    //printf("%d\n",fibo1(n));;
    printf("%d\n",fibo2(n));

    //Exo 2

    Tonneau T;
    float V;

    printf("Entrez le petit diametre :\n");
    scanf("%f", &T.d);
    printf("Entrez le grand diametre :\n");
    scanf("%f", &T.D);
    printf("Entrez la longueur :\n");
    scanf("%f",&T.L);
    printf("Entrez le contenant :\n");
    scanf("%s",&T.c);
    V = (1/4.0) * PI * (T.L) * (T.d +(2.0/3)*(T.D-T.d)) * (T.d +(2.0/3)*(T.D-T.d));
    printf("Le volume du Tonneau est %f", V);
    */
}

/*void lire_Tonneau(Tonneau T){
    printf("Entrez le petit diametre :\n");
    scanf("%f", &T.d);
    printf("Entrez le grand diametre :\n");
    scanf("%f", &T.D);
    printf("Entrez la longueur :\n");
    scanf("%f",&T.L);
    printf("Entrez le contenant :\n");
    scanf("%s",&T.c);
}*/
