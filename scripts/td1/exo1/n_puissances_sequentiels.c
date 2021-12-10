#include <stdio.h>
#include <stdlib.h>

// Fonction qui génére un tableau de nombres aléatoires
int* random_array(int length){

    int* list = (int*) malloc(sizeof(int)*length);

    for(int i =0; i < length; i++){
        list[i] = rand() % 25;
    }

    return list;
}

int main(){

    int n = 8;
    int* number_array = random_array(n);

    // calcul de chaque carré d'un nombre
    for(int i = 0; i < n; i++){
        printf("\n (%d) => %d", number_array[i], number_array[i]*number_array[i]);
    }

    return 0;

}