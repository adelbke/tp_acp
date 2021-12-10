#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define RAND_MAX 50

typedef struct Node Node;
struct Node
{
    int info;
    Node* next;
};

Node* random_node(){
    Node* p = malloc(sizeof(Node));

    p->info = rand();
    p->next = NULL;

    return p;
}

Node* create_node(int info){
    Node* p = malloc(sizeof(Node));

    p->info = info;
    p->next = NULL;

    return p;
}

int fib(int n){
    if(n <= 2){
        return 1;
    }
    return fib(n-1) + fib(n-2);
}


int main(int argc, char const *argv[])
{
    omp_set_num_threads(2);


    Node* p =NULL;
    int length =50;

    p = random_node();
    Node* q =p;
    for (int i = 1; i < length; i++)
    {
        q->next = random_node();
        q = q->next;
    }


    Node* result = create_node(-1);

    Node* resultq = result;

    q = p;
    

    #pragma omp parallel
    {
        #pragma omp master
        {
            while(p != NULL){

                #pragma omp task
                resultq->next = create_node(fib(q->info));
                
                resultq = resultq->next;
                q = q->next;
            }
        }
    }

    return 0;
}
