/*****************************
Returning Values from Threads
******************************/

// Technique No. 2: to return a value is to pass it as the thread’s exit code.

/*Code below shows an alternative approach for simple scalar return types, which is to reuse the trick of casting to and from the void* type. When a thread calls pthread_exit(), it can specify a pointer to return as an argument.*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
/* Thread argument struct contains only input parameters */
struct numbers {
  int a;
  int b;
};

void *sum_thread (void *_args)
{
  /* Cast the arguments to the usable struct type */
  struct numbers *args = (struct numbers *) _args;

  /* Pass the result back by casting it to the void* */
  pthread_exit ((void *) (args->a + args->b));
  /* Scalar return types as void* with pthread_exit() */
}
/*The main thread calls pthread_join() to retrieve the pointer. Unless the thread has been detached (or it was created with the PTHREAD_CREATE_DETACHED attribute), the pointer returned with pthread_exit() will remain associated with the thread until it is joined.
*/
int main()
{
pthread_t child;

/* The main thread retrievs the child thread’s exit code when it is joined.

* Allocate the struct and pass it to the thread */
struct numbers *args = calloc (sizeof (struct numbers), 1);
args->a = 5;
args->b = 8;

assert (pthread_create (&child, NULL, sum_thread, args) == 0);

/* Wait for thread to finish and retrieve the void* into sum */
void *sum = NULL;
pthread_join (child, &sum);
printf ("%d + %d = %d\n", args->a, args->b, (int)sum);

/* Clean up the struct instance */
free (args);
args = NULL;

return 0;
}


