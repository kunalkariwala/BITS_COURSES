#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    pid_t pid;
    int * a;
    *a = 2;
    int status;
    //error handling with creating the 2 pipes

    //parent creates the child process
    pid = fork();
    if(pid < 0){
        //error handling
        perror("Error in creating fork!");
        exit(1);
    }
    else if(pid==0)
    {
        //child process
        printf("From the child process :- %d\n",*a);
        //child process prints its PID and its parent's pid
        printf("From the child process :- process with pid = %d was just created by parent with pid = %d\n",getpid(),getppid());
         // close the writing end of the pipe1 to be used to transfer data from the parent to the child
        exit(2);
    }
    else
    {
        //parent process

        //parent process prints its PID and its child's pid
        printf("From the parent process :- process with pid = %d just created a child with pid = %d\n",getpid(),pid);
        pid_t temp = pid;

        sleep(1);

        //wait for the child to send a string
        wait(NULL);

        printf("From the parent : %d\n",*a);


    }
}