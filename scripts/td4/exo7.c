//EXERCICE 7
/*résolution equation de la chaleure (diffusion de la chaleur , equation de Laplace) par la méthode des différences finies 
une surface MxN sur laquelle on applique des températures de départ (stables) uniquement sur les bords (haut, bas, gauche droite) et 
grace à l'équation de diffusion de la chaleur on essaie de deviner la température qu'il fera à tous les points de la surface de la 
plaque. Pour cela il suffit de résoudre l'équation de Laplace. Cet algorithme permet de trouver les solutions à cette équatin 
en discrétisant l'espace un maillage est réalisé (découpage de la surface globale en plusieurs petits morceaux et on essaie de trouver 
la température aux points d'intersection en utilisant la méthode des différences finies).
il s'aggit ici de paralléliser cet algorithme avec MPI en considérant les cas suivants: 
1-Le nombre de lignes de la matrice est égal au nombre de processus (petite taille)
2-Le nombre de processus <<< taille de la matrice et dans ce cas chaque processus sera en charge de calculer 
plusieurs lignes de la matrice. 
NB. il y a 3 boucles (boucle while des itérations, deux boucles for pur le parcours de la matrice), ici il n'est possible 
de paralléliser que les deux boucles for (ou une seule d'elles) la boucle externe contient des dépendances de données il faut 
terminer avec l'itération i avant de passer à l'itération i+1 donc pas possible de la paralléliser. 

Autre remarque, pour calculer une ligne i, le processus a besoin de la ligne en question à l'itération précédante, et des deux lignes 
adjacentes i+1 et i-1. Donc en cas de découpage en lignes il faut lui envoyer sa ligne et deux autres ligens adjacentes. 
On peut découper aussi par colonne ou alors par petites matrices, mais le découpage par ligne c'est le plus simple et
 celui qui limite aussi les dépendances. 

3-réaliser une comparaison entre la version séquentielle et la version parallèle avec MPI et calculer le speed up et efficacité. 
  
*/

#include <stdio.h>
#include <stdlib.h>
main()
{
    int i, j, k, m, n;
    float **a;
    float l, r, t, b;
    FILE *fp;
    //clrscr();
    fp = fopen("laplace.dat", "w"); //output will be stored in this file
    printf("\t_______________________________________________________________\n");
    printf("\tProgram to solve Laplace's equation by finite difference method\n");

    printf("Donner le nombre des lignes de la matrice A\n");
    scanf("%d", &m);
    printf("Donner le nombre des colonnes de la matrice A\n");
    scanf("%d", &n);

    a = (float **)malloc(m * sizeof(float *));

    for (i = 0; i < m; i++)
        a[i] = (float *)malloc(n * sizeof(float)); //au niveau de chaque ligne n colonnes

    printf("Enter boundary conditions:les valeures de la température sur les bords \n");
    printf("\tValue on left side: ");
    scanf("%f", &l);
    printf("\tValue on right side: ");
    scanf("%f", &r);
    printf("\tValue on top side: ");
    scanf("%f", &t);
    printf("\tValue on bottom side: ");
    scanf("%f", &b);

    

    //remplir les valeures de départ dans la matrice (en ce qui concerne les bords de la plaque
    for (i = 0; i < m; i++) //assigning boundary values begins
    {
        a[i][0] = b;
        a[i][n-1] = t;
    }
    
    for (i = 0; i < n; i++)
    {
        a[0][i] = l;
        a[m-1][i] = r;
    }

    printf("\nHere\n");
    fflush(stdout);
    
    //initialisation des valeures internes par la meme valeure temporaire, n'importe quelle valeure
    for (i = 1; i < m - 1; i++)
        for (j = 1; j < n - 1; j++)
            a[i][j] = t; //initialization of interior grid points by any value ...

    //calculation by Gauss-Seidel Method dans le but de simuler les températures dans tous les points de la plaque aprés la propagation des
    //températures appliquées sur les bords de la plaque, en utilisant la méthode de Gauss Seidel pour résoudre l'équation de la chaleur
    //température(i, j)=la somme des températures sur les 4 points adjacents /4

    for (k = 0; k < 1000; k++) //le nombre d'itération est un paramètre que vous pouvez changer ainsi que la taille de la matrice
    {
        for (i = 1; i < m - 1; i++)
        {
            for (j = 1; j < n - 1; j++)
            {
                a[i][j] = (a[i - 1][j] + a[i + 1][j] + a[i][j - 1] + a[i][j + 1]) / 4;
            }
        }
    }

    //enregistrer le résultat final dans un fichier
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            fprintf(fp, "%.2f\t", a[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("\nData stored\nPress any key to exit...");
    //            getch();

    //libération de l'espace mémoire à la fin du calcul
    for (i = 0; i < m; i++)
        free(a[i]);
    free(a);
}
