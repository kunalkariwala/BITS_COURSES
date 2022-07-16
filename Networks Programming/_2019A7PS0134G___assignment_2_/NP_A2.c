#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
    pid_t pid;
    int status;
    //pipe 1 will be used to share data from parent to child
    int pipe1[2]; // Used to store two ends of first pipe

    //pipe 2 will be used to share data from child to parent
    int pipe2[2]; // Used to store two ends of second pipe


    //error handling with creating the 2 pipes
    if (pipe(pipe1) == -1) {
        perror("ERROR IN CREATING PIPE!");
        return 1;
    }
    if (pipe(pipe2) == -1) {
        perror("ERROR IN CREATING PIPE!");
        return 1;
    }

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
        
        //child process prints its PID and its parent's pid
        printf("From the child process :- process with pid = %d was just created by parent with pid = %d\n",getpid(),getppid());
         // close the writing end of the pipe1 to be used to transfer data from the parent to the child
        close(pipe1[1]);
        char frompar[10];
        read(pipe1[0],frompar,10);
        printf("From the child process : The integer enterred into the parent process is %d\n",atoi(frompar));
        close(pipe1[0]);

        close(pipe2[0]);
        int childread;
        char snum2[10];

        printf("From the child process : Kindly enter an integer:-\n");
        scanf("%d",&childread);
        // itoa(childread, snum2, 10);
        sprintf(snum2, "%d", childread);
        write(pipe2[1],snum2,10);
        close(pipe2[1]);
        exit(2);
    }
    else
    {
        //parent process

        //parent process prints its PID and its child's pid
        printf("From the parent process :- process with pid = %d just created a child with pid = %d\n",getpid(),pid);
        pid_t temp = pid;

        sleep(1);

        // close the reading end of the pipe1 to be used to transfer data from the parent to the child
        close(pipe1[0]);

        //parent reads an integer from the user
        int parentread;
        char snum[10];

        char fromchild[10];

        printf("From the parent process : Kindly enter an integer:-\n");
        scanf("%d",&parentread);
        sprintf(snum, "%d", parentread);
        //writing to the pipe
        write(pipe1[1],snum,strlen(snum)+1);
        close(pipe1[1]);

        //wait for the child to send a string
        wait(NULL);

        //close the writing end of the second pipe
        close(pipe2[1]);

        //read the integer from the child process
        read(pipe2[0],fromchild, 10);

        printf("From the parent process : The integer enterred into the child process is %d\n",atoi(fromchild));

        close(pipe2[0]);


    }
}