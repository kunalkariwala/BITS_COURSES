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
        sleep(10);
        exit(0);
    }
    else
    {
        //parent process

        //parent process prints its PID and its child's pid
        printf("From the parent process :- process with pid = %d just created a child with pid = %d\n",getpid(),pid);
        pid_t temp = pid;
        do{
            temp = waitpid(temp,&status,WNOHANG);
            if(temp == -1){
                perror("Error in checking!");
            }
            if(temp > 0){
                if(WIFEXITED(status)){
                    printf("Child with pid = %d has exited with status of %d\n",pid,WEXITSTATUS(status));
                }
            }
            else{
                printf("Parent Process is still waiting for the child process and can do anything\n");
                sleep(1);
            }

        }while(temp == 0);

    }
}