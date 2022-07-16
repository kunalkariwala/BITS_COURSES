/*******************************
Creating and Joining Threads
*******************************/
/*
Three functions define the core functionality for creating and managing threads.

1.The pthread_create() function will create and start a new thread inside a process. The third parameter specifies the name of the function to use as the thread’s entry point, just as main() serves as the main thread’s entry point. 

2.The pthread_exit() is used to exit the current thread and optionally return a value.

3.The pthread_join() function is the thread equivalent of the wait() function for processes. That is, calling pthread_join() on a child thread will cause the current (parent) thread to wait until the child finishes and calls pthread_exit().*/

//The following program illustrates how to create a child thread and wait for it to finish.
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

/* Function that will run in the child thread */
void *start_thread (void *args)
{
  printf ("Hello from child\n");
  pthread_exit (NULL);
}

/********************************************
The main() function defines a thread. Specifically, every program begins with a single thread of execution with main() as its entry point. Once the pthread library creates an additional thread, it is important that main() should be treated as a thread. In the simplest terms, this perspective implies that main() needs to end with pthread_exit() instead of the standard return statement. 
**********************************************/
int main ()
{
  pthread_t child_thread;
  
//Syntax:   int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
  
/* Create a child thread running start_thread() */
  assert (pthread_create (&child_thread, NULL, start_thread, NULL) 
          == 0);
 /*
 The arg argument to the pthread_create() function gets passed verbatim as the argument to the start_routine() function. That is, when the thread is created, it begins executing as if the programmer had called start_routine (arg); in their code. The only thing that is different is that the function will begin executing in a different thread.

The prototype for the pthread_create() function can be rather difficult to read if you are not completely comfortable with function pointers. Specifically, this prototype declares that the third parameter must be a pointer to a function that adheres to the following type declaration:

void *start_routine (void *args);

This prototype requirement simplifies the interface specification for thread creation. The trade-off is that passing parameters becomes more complicated. 
*/
/*******************************************************************************/         
//Syntax: int pthread_join (pthread_t thread, void **value_ptr);
//    Join a specified thread.
    
  /* Wait for the child to finish, then exit */
  pthread_join (child_thread, NULL);
/*
The main thread uses pthread_join() function to wait for the thread running start_thread() to call pthread_exit(). The standard thread terminology uses the term joining to mean waiting on a thread to complete. When a thread exits, any resources associated with it (such as its run-time stack) remain allocated until the thread is joined. As such, the pthread_join() and pthread_exit() combination can be used to return a value from the exiting thread to its parent. In this example, nothing is returned, so both of these functions take NULL as an argument.

Creating threads with pthread_create() happens asynchronously. That is, pthread_create() requests the allocation of resources for a new thread and returns 0 if the request is successful. The new thread may or may not begin running by the time pthread_create() returns. In fact, the new thread may have already run to completion by the time pthread_create() returns! The timing for running both the new and existing threads are determined by the system (the pthread library and the kernel). From the programmer’s perspective, this choice is nondeterministic.
*/
/*******************************************************************************/

//Syntax:   void pthread_exit (void *value_ptr);
//    Exit from the current thread.

  pthread_exit (NULL);
  return 0;
}
/*
*****************************************************************************
Bug Warning

1. There are a couple of common mistakes with pthread function parameters. With pthread_create(), the first parameter must point to a pthread_t instance. It is common to (incorrectly) declare the variable as a pthread_t*. Instead, the variable should be a pthread_t and the address of it should be passed as shown above. 

2. Similarly, the first parameter for pthread_join() must be a pthread_t instance, not a pointer.

3. Next, the third parameter to pthread_create() must be the name of the function and must not include (). The parentheses would indicate that the function should be called (before creating the thread) and the function’s return value specifies the address to start at in the new thread. The following code sample illustrates these bugs.

/* WRONG! thread should not be a pointer in this example */
// pthread_t *thread;
/* WRONG! thread is invalid pointer and start should not have () */
// pthread_create (thread, NULL, start (), NULL);
/* WRONG! pthread_join() doesn't take pointer as first parameter */
// pthread_join (thread, NULL); 


