#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

void ex4_4();
void ex5_1();
void ex5_2();
void ex5_3();

void main(){
    //ex4_4();
    //ex5_1();
    //ex5_2();
    ex5_3();
}

void ex4_4(){
    int n,i,*tmp;
    int **tab;

    printf("Entrez le nombre de nombres a saisir :\n");
    scanf("%d",&n);

    tab = malloc(n * sizeof(int*));

    for (i=0; i<n; i++){
            tab[i] = malloc (1 * sizeof(int));
            printf("Entrez le %d eme nombre : \n",i+1);
            scanf("%d", tab[i]);
    }

    tmp = tab[0];
    for (i=0; i<n-1; i++)
        tab[i] = tab[i+1];
    tab[n-1] = tmp;

    for (i=0; i<n; i++){
             printf("%d \n", tab[i][0]);
    }

    for (i=n-1; i>0; i--)
        tab[i] = tab[i-1];
    tab[0] = tmp;

    for (i=0; i<n; i++){
        printf("%d \n", tab[i][0]);
    }
}

void ex5_1(){
    char c[MAX], sc[MAX];
    int i, j, x, fois=0;
    printf("Entrez une chaine de caracteres (<100) :\n");
    scanf("%s", c);
    printf("Entrez la sous chaine a rechercher (<100) :\n");
    scanf("%s", sc);

    for (i=0; i<strlen(c); i++){
            j = 0;
            x = 0;
            while ((c[i]==sc[j]) && (i != strlen(c))){
                i++;
                j++;
                x += 1;
            }
            if (x == strlen(sc)){
                fois += 1;
                printf("La sous chaine est presente pour la %d fois a partir de la position %d\n", fois, i-x+1);
            }
            i -= x;
    }
}

void ex5_2(){
    char c[MAX];
    int i;
    printf("Entrez une chaine de caracteres (<100) :\n");
    scanf("%s", c);
    printf("%s\n",c);
    for (i=0; i<strlen(c); i++)
            if (c[i]>='a' && c[i]<='z')
                c[i] -= 'a' - 'A';
    printf("%s\n",c);
}

void ex5_3(){
    char c[MAX], x[25];
    int i, j = 0, z, gagne, test;
    printf("Entrez un mot (<100) : ");
    scanf("%s", c);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (i=0; i<strlen(c); i++)
        printf("*");

    while (gagne != -1 && j < 10){
        gagne = 0;
        fflush(stdout);
        fflush(stdin);
        printf("\ncaractere ? ");
        x[j] = getchar();
        for (i=0; i<strlen(c); i++){
            test =0;
            for (z=0; z<strlen(x); z++){
                if (x[z] == c[i]){
                    printf("%c", c[i]);
                    test = 1;
                    gagne += 1;
                }
            }
            if (test == 0)
                printf("*");
        }
        j++;
        if (gagne == strlen(c))
            gagne = -1;
    }
    if (gagne == -1)
        printf("\n\n    VOUS AVEZ GAGNE\n");
    else
        printf("\n\n    VOUS AVEZ PERDU\n");
}

