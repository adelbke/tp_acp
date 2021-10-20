#include <stdio.h>
#include <stdlib.h>


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

    for(int i = 0; i < n; i++){
        printf("\n (%d) => %d", number_array[i], number_array[i]*number_array[i]);
    }

    return 0;

}