/*
The pthread_create() imposes a strict format on the prototype of the function that will run in the new thread. It must take a single void* parameter and return a single void* value. The last parameter of pthread_create() is passed as the argument to the function.

When passing multiple arguments to a child thread, the standard approach is to group the arguments within a struct declaration.
In this example, we want to pass more than one argument to the function, so we create a pointer point to a struct we have created, transfer it into (void *) and pass to function.
In function, we transfer the type of pointer to the real type, so that we can properly use it.

The address of the struct instance gets passed as the arg to pthread_create(). The new thread’s entry point receives a void* parameter that can then be cast into the struct type.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct args {
    char* name;
    int age;
};

void *hello(void *_input) {
/* Using the convention of casting _input to input i.e;
cast input into a meaningful pointer type that we can use */
  struct args *input = (struct args *) _input;
  
    printf("name: %s\n", input->name);
    printf("age: %d\n", input->age);
    
/* Do not forget to free the struct used for arguments */
  free (input);
  pthread_exit (NULL);
}

int main() {
    struct args *Allen = (struct args *)malloc(sizeof(struct args));
    char allen[] = "Allen";
    Allen->name = allen;
    Allen->age = 20;
/* Note that the data structure resides on the heap */

    pthread_t tid;
    pthread_create(&tid, NULL, hello, (void *)Allen);
    pthread_join(tid, NULL);
    
  
    //Bug Warning
/*
//A common mistake with passing arguments in this manner is to declare the struct instance as a local variable instead of using dynamic allocation. The problem, again, is the asynchronous nature of pthread_create(). Consider this sample code:
//Create a local instance on the current thread's stack 
    struct args Bob;
    Bob.age = 5;
    strcpy(Bob.name,"Bob");
    // Pass a reference to the local instance 
    pthread_create(&tid, NULL, hello, &Bob);
    pthread_join(tid, NULL);
    //Parent thread exits, but the child thread may not have run yet
pthread_exit (NULL); // Future references to Allen and Bob are invalid!
/*
If the child thread runs immediately before pthread_create() returns, then everything would be fine. However, there is no guarantee that this happens. Instead, it is just as likely that pthread_create() returns and the parent thread exits. Once that happens, all data on the parent thread’s stack (including the struct args instance) become invalid. The child thread now has a dangling pointer to potentially corrupted data. This is another example of a race condition that can happen with threads.
*/
    return 0;
}



 

