/******************************************************************************
**   A "hello world" Pthreads program which demonstrates another safe way
*   to pass arguments to threads during thread creation.  In this case,
*   a structure is used to pass multiple arguments.
*
******************************************************************************/
/*
The pthread_create() imposes a strict format on the prototype of the function that will run in the new thread. It must take a single void* parameter and return a single void* value. The last parameter of pthread_create() is passed as the argument to the function.

To pass more than one argument, we use structure in c.
In this example, we want to pass more than one argument to the function, so we create a pointer point to a struct we have created, transfer it into (void *) and pass to function.
In function, we transfer the type of pointer to the real type, so that we can properly use it.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#define NUM_THREADS	8

char *messages[NUM_THREADS];

struct thread_data
{
   int	thread_id;
   int  sum;
   char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
   int taskid, sum;
   char *hello_msg;
   struct thread_data *my_data;

   sleep(1);
   my_data = (struct thread_data *) threadarg;
   taskid = my_data->thread_id;
   sum = my_data->sum;
   hello_msg = my_data->message;
   printf("Thread No.= %d: ID= %d PID=%d TID=%lu %s  Sum=%d\n", taskid, gettid(),getpid(),pthread_self(),hello_msg, sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int *taskids[NUM_THREADS];
int rc, t, sum;

sum=0;
messages[0] = "English: Hello World!";
messages[1] = "French: Bonjour, le monde!";
messages[2] = "Spanish: Hola al mundo";
messages[3] = "Klingon: Nuq neH!";
messages[4] = "German: Guten Tag, Welt!"; 
messages[5] = "Russian: Zdravstvytye, mir!";
messages[6] = "Japan: Sekai e konnichiwa!";
messages[7] = "Latin: Orbis, te saluto!";

for(t=0;t<NUM_THREADS;t++) {
  sum = sum + t;
  thread_data_array[t].thread_id = t;
  thread_data_array[t].sum = sum;
  thread_data_array[t].message = messages[t];
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *) 
       &thread_data_array[t]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }

  for(t=0;t<NUM_THREADS;t++)
    {
        printf("joining thread no. %d\n",t);
        pthread_join(threads[t],NULL);
    }
    
pthread_exit(NULL);
printf("This is never printed Thread %d: %s  Sum=%d\n", thread_data_array[0].thread_id, thread_data_array[0].message, thread_data_array[0].sum);

}
