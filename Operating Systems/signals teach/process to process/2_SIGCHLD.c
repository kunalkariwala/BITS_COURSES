//this is to demonstrate exec which is actually SIGCHILD followed by exit
//execute eg:  ./a.out 1 ps
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int delay;
void childHandler();
int main(argc,argv)
int argc;
char*argv[];
{
    int pid;
    signal(SIGCHLD,childHandler);//Install death-of-child handler
    pid=fork();
    if(pid==0)
    {
        execvp(argv[2],&argv[2]);
    }
    else
    {
        sscanf(argv[1],"%d",&delay);
        sleep(delay);
        printf("child %d exceeded limit and is being killed\n",pid);
        kill(pid,SIGINT);//kill the child
    }
}
void childHandler()
{
    int childPid,childStatus;
    childPid=wait(&childStatus);//Accept child's termination code
    printf("child %d terminated within %d second\n",childPid,delay);
    exit(/*EXITSUCCESS */0);
}
