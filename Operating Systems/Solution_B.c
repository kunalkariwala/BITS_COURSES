#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define MAXSIZE 10

 
int arr[MAXSIZE];
int foundindex = -1; 
int key;
long foundThreadId = -1;
pthread_t childthreadid[MAXSIZE];
 
void * search(void * threadid) {
    if(foundindex == -1){
        int index = (intptr_t)threadid;
        long taskid = (long)pthread_self();
        if(arr[index] == key){
            foundindex = index;
            foundThreadId = taskid;
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL); 
}

int main()
{
    for(int i = 0 ; i < MAXSIZE;i++){
        arr[i] = i;
    }
 
    for(int i = 0 ; i < MAXSIZE;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
 
    printf("Please Enter the element to be searched between %d and %d \n", 0,MAXSIZE-1);
    scanf("%d",&key);
    printf("Key to be searched is %d \n", key);

    int noofthreads = 0;

    for(int i = 0 ; i <MAXSIZE;i++){
        if(foundindex == -1){
            pthread_create(&childthreadid[i], NULL, search, (void *)(intptr_t)i);
            printf("Created Thread no %d with ID = %ld\n",i,(long)childthreadid[i]);
            noofthreads++;
        }
    }

    for(int i = 0 ; i < noofthreads;i++){
        pthread_join(childthreadid[i], NULL);
    }
 
 
    if(foundindex == -1){
        printf("Not Found! \n");
    }
    else{
        printf("Found at index = %d by thread with ID = %ld\n",foundindex,foundThreadId);
    }

    return 0;
}

/* ===================== ANALYSIS ============================
? Time Complexity : O(N)
Each thread has a time complexity of O(1) because each thread checks its corresponding index in the array and does not loop through any elements.
In Multi threading, it is basically running in parallel so it is almost like the complexity of the entire program is O(1) if we consider all threads
to run parallely 

However, it still takes O(N) time to create N threads. We can optimise this a bit.

? Space Complexity : O(N) where N is the MAXSIZE 
because N threads are created in the worst case and each thread checks its equivalent index in the array
*/


/* ===================== CONCLUSION ==========================

Implementation A should be used when space is a constraint and B should be used when time is a constraint.
In a more general case, we usually prefer optimisation on time because space is available.
In B, we can also optimise further on not creating anymore threads if the element is found before new threads are created.

We may still prefer A since it has O(1) space and O(n) time.

*/
