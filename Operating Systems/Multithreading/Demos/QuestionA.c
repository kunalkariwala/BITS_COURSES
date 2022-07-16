#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
 
#define MAXSIZE 15
 
struct indexes {
  int start;
  int stop;
};
 
int arr[MAXSIZE];
int foundindex = -1; 
int key;
long foundThreadId = -1;
pthread_t childthread, childthread2;
 
void * search(void * threadid) {
    struct indexes *indexesfn = (struct indexes *) threadid;
    long taskid = (long)pthread_self();
    for(int i = indexesfn->start; i < indexesfn->stop;i++){
        if(foundindex != -1) {
            break;
        }
        if(arr[i] == key){
            foundindex = i;
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
 
    struct indexes *args = calloc (sizeof (struct indexes), 1);
    args->start = 0;
    args->stop = MAXSIZE/2;
    pthread_create(&childthread, NULL, search, args);
    printf("Created Thread with ID = %ld\n",(long)childthread);
 
    struct indexes *args2 = calloc (sizeof (struct indexes), 1);
    args2->start = MAXSIZE/2;
    args2->stop = MAXSIZE;
    pthread_create(&childthread2, NULL, search, args2);
    printf("Created Thread with ID = %ld\n",(long)childthread2);
 
    pthread_join(childthread, NULL);
    pthread_join(childthread2, NULL);
 
 
    if(foundindex == -1){
        printf("Not Found! \n");
    }
    else{
        printf("Found at index = %d by thread with ID = %ld\n",foundindex,foundThreadId);
    }
 
    return 0;
}
 