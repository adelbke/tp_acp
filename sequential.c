#include <stdlib.h>
#include <stdio.h>


int main(){
    int nombretab[10] = {4,2,9,12,4,2,9,12,4,2};

    int resulttab[10];

    for(int i=0; i< 10; i++ ){
        resulttab[i] = nombretab[i]*nombretab[i];
        printf("%d ",resulttab[i]);
    }
    
}

