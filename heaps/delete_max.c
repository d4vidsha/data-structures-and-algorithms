#include <stdio.h>
#define DEBUG 1
#define ARRAYSIZE 10

/**
* Excercise, change PQ int array to array of pointer to structs,
* and change deletemax to return pointer to struct instead of int
* Struct can have a string DATA and an int PRIORITY
*/

void downheap(int* PQ, int k, int PQsize)
{
    int j,v;
    v = PQ[k];      	/* value, or priority */
    
    while( k <= PQsize/2 )  	/* A[k] has children */
    {	
        /* point to children*/
        j= k*2; 
        
        /* j set to highest child*/
        if(j < PQsize && PQ[j] <  PQ[j+1]) j++; 	
        
        /* check heap OK */
        if (v >= PQ[j]) break;
        
        /* swap and continue */
        PQ[k] = PQ[j]; 
        k = j; 	
    }  
    /* final position of original A[k] value*/
    PQ[k] = v; 
}

int deletemax(int* PQ, int* PQsize)  
{
       int v = PQ[1];
       *(PQsize)-=1;
       PQ[1] = PQ[*PQsize];
       downheap(PQ, 1, *PQsize);
       return(v);
} 


       /** Swap **/
     //  swap( &(A[i]), &(A[min]) );


int main()
{
    int i = 0;
    int PQsize = ARRAYSIZE;
    int PQ[ARRAYSIZE] = {-1,9,8,7,6,5,4,3,2,1}; 
    
    
    printf("Original PQ: ");
    for( i = 0; i < PQsize; i++)
        printf(" %d", PQ[i]);
    printf("\n");
    
    int max = deletemax(PQ, &PQsize);
    
    printf("Max value deleted: %d\n", max);
    
    printf("new PQ: ");
    for( i = 0; i < PQsize; i++)
        printf(" %d", PQ[i]);

    return 0;

}

