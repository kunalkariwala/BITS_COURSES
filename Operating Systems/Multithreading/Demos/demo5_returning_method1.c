/*
Returning Values from Threads

There are three common ways to get return values back from a thread. All three use techniques that are similar to those used for passing arguments. Code below shows one simple technique, which is to augment the struct declaration to include space for any return values.

// Technique No. 1: Allocating space for a return value as part of the struct passed
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
/* Thread argument struct declaration */
struct numbers {
  int a;
  int b;
  int sum;
};

void *sum_thread (void *_args)
{
  /* Cast the arguments to the usable struct type */
  struct numbers *args = (struct numbers *) _args;

  /* Place the result into the struct itself (on the heap) */
  args->sum = args->a + args->b;
  pthread_exit (NULL);
}
/*
The child thread receives a pointer to the struct instance, using the input parameters as needed. In this case, the values of a and b are added, and the resulting sum is copied back into the struct. The main thread uses pthread_join() to wait until the child thread exits. Once the child finishes, the main thread can retrieve all three values (a, b, and sum) from the struct itself.
*/
int main()
{
pthread_t child;

//The main thread can retrieve the return value from the struct after joining the child thread.

/* Allocate and pass a heap instance of the struct type */
struct numbers *args = calloc (sizeof (struct numbers), 1);
args->a = 5;
args->b = 8;

assert (pthread_create (&child, NULL, sum_thread, args) == 0);

/* Wait for the thread to finish */
pthread_join (child, NULL);
/* The struct is still on the heap, so the result is accessible */
printf ("%d + %d = %d\n", args->a, args->b, args->sum);

/* Clean up the struct instance */
free (args);
args = NULL;

return 0;
}

/*
There are three key observations about this approach:

        The main and the child threads have access to both the input and the output. This fact means that the main thread has information about how this particular child thread was invoked. If the main thread is keeping track of many threads, this additional information may be helpful.
        Responsibility for memory management resides in one location: the main thread. If responsibility is split between the programmer maintaining the main thread and the programmer maintaining the child thread, there is the possibility for miscommunication leading to memory leaks (or worse, premature de-allocation).
        The major disadvantage of this approach is that the input parameters may be kept on the heap for much longer than needed, particularly if the child thread runs for a significant amount of time.

*/
