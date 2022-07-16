#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t pid;
    int status;
    //parent creates the child process
    pid = fork();
    if(pid == -1){
        //error handling
        perror("Error in creating fork!");
        exit(1);
    }
    else if(pid==0)
    {
        //child process
        
        //child process prints its PID and its parent's pid
        printf("From the child process :- process with pid = %d was just created by parent with pid = %d\n",getpid(),getppid());

        //child exits
        exit(0);
    }
    else
    {
        //parent process

        //parent process prints its PID and its child's pid
        printf("From the parent process :- process with pid = %d just created a child with pid = %d\n",getpid(),pid);

        //send the parent to sleep to check for zombie processes

        
        sleep(60);
    }
}