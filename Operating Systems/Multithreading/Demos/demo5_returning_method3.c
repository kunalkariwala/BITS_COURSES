/*****************************
Returning Values from Threads
******************************/

// Technique No. 3: Allocate separate struct for return values. 
//The child can dynamically allocate space for the return values.
/*
Code belowshows a third approach to returning values from the thread. In this style, the child thread allocates a separate struct dynamically to hold the return values. This technique allows a thread to return multiple values rather than a single scalar. For instance, consider the following calculator thread. It receives two int values as input and returns the results of five simple arithmetic operations.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
/* struct for passing arguments to the child thread */
struct numbers {
  int a;
  int b;
};

/* struct for returning results from the child thread */
struct results {
  int sum;
  int difference;
  int product;
  int quotient;
  int modulus;
};

void *calculator (void *_args)
{
  /* Cast the args to the usable struct type */
  struct numbers *args = (struct numbers *) _args;

  /* Allocate heap space for this thread's results */
  struct results *results = calloc (sizeof (struct results), 1);
  results->sum        = args->a + args->b;
  results->difference = args->a - args->b;
  results->product    = args->a * args->b;
  results->quotient   = args->a / args->b;
  results->modulus    = args->a % args->b;
  /* De-allocate the input instance and return the pointer to
     results on heap */
  free (args);
  pthread_exit (results);
}
/*
It is critical to note that the struct instance here must be allocated dynamically. Once the thread calls pthread_exit(), everything on its stack becomes invalid. A thread should never pass a pointer to a local variable with pthread_exit().

Retrieving the returned data can be accomplished with pthread_join(). In the following example, the main thread creates five separate instances of the calculator thread. Each of these child threads gets a pointer to a unique struct args instance with the corresponding parameters. Each child then allocates its own struct results instance on the heap. This allows the data to persist after the thread has finished. In the code below, the main thread gets each thread’s pointer one at a time, with a separate call to pthread_join(). Since the child thread has already finished at this point, the main thread must bear the responsibility for calling free() to de-allocate the struct results instance.
*/
int main()
{
/* 
   The main thread passes arguments to the child threads and frees the results
 */

/* Create 5 threads, each calling calculator() */
pthread_t child[5];

/* Allocate arguments and create the threads */
struct numbers *args[5] = { NULL, NULL, NULL, NULL, NULL };
for(int i = 0; i < 5; i++)
  {
    /* args[i] is a pointer to the arguments for thread i */
    args[i] = calloc (sizeof (struct numbers), 1);

    /* thread 0 calls calculator(1,1)
       thread 1 calls calculator(2,4)
       thread 2 calls calculator(3,9)
       and so on... */
    args[i]->a = i + 1;
    args[i]->b = (i + 1) * (i + 1);
    assert (pthread_create (&child[i], NULL, calculator, args[i]) 
            == 0);
  }

/* Allocate an array of pointers to result structs */
struct results *results[5];
for (int i = 0; i < 5; i++)
  {
    /* Passing results[i] by reference creates (void **) */
    pthread_join (child[i], (void **)&results[i]);

    /* Print each of the results and free the struct */
    printf ("Calculator (%d, %2d) ==> ", i+1, (i+1) * (i+1));
    printf ("+:%3d;   ", results[i]->sum);
    printf ("-:%3d;   ", results[i]->difference);
    printf ("*:%3d;   ", results[i]->product);
    printf ("/:%3d;   ", results[i]->quotient);
    printf ("%%:%3d\n", results[i]->modulus);
    free (results[i]);
  }
return 0;
}

/*NOTE:
All of the functions for creating threads, passing arguments, and getting return values involve a lot of pointers. Furthermore, the pointers are dereferenced and manipulated asynchronously because of the nature of multithreading. It is vital to remember the types and lifetimes of each pointer and the corresponding data structure.

        The first parameter for pthread_create() is a pthread_t*. The argument should typically be an existing pthread_t passed by reference with the & operator.
        The final parameter to pthread_create() must either be a scalar (cast as a pointer) or a pointer to data that persists until the child thread runs. That is, the target of the pointer must not be modified by the main thread until the child thread has been joined (to guarantee the child has run).
        The parameter to pthread_exit() must be a scalar value (cast as a pointer) or a pointer to non-stack data. The data must be guaranteed to be valid even after the thread has been completely destroyed.
        The final parameter to pthread_join() must be a pointer that is passed by reference. That is, pthread_join() will change this pointer to point to the returned data structure.

*/

