#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int zomb;
static void child_dead(int sig, siginfo_t *si, void *uap)
{
    pid_t pid;
    int status;
    if(zomb==0)
    {
        pid = waitpid(-1, &status, WNOHANG);
        printf("Child has exited, its pid is %d \n", pid);
    }
    else
    {
        printf("Child has exited and is a zombie process with pid %d . You can see its entry as defunct by pausing (press Ctrl+Z) and entering ps \n", si->si_pid);
    }
    unsigned int microsecond = 1000000;
    usleep(3 * microsecond);
}
int main()
{   
    printf("If you want to see zombie process, enter 1. Else, enter 0 \n");
    scanf("%d", &zomb);
    struct sigaction sa;

    sa.sa_sigaction=child_dead;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, 0) == -1)
    {
        perror(0);
        exit(1);
    }
    int forked_pid = fork();
    if (forked_pid == 0)
    {   
 
        int child_pid = getpid();
        int parent_pid = getppid();
        printf("In child process \n");
        printf("Child pid: %d \n", child_pid);
        printf("Parent pid: %d \n", parent_pid);
        exit(0);
    }
    else if (forked_pid==-1)
    {
        perror("Error in making child!");
        return 0;
    }
    else
    {   
        unsigned int microsecond = 1000000;
        usleep(3 * microsecond);
        int child_pid = forked_pid;
        int parent_pid = getpid();
        printf("In parent process \n");
        printf("Child pid: %d \n", child_pid);
        printf("Parent pid: %d \n", parent_pid);
    }
 
    return 0;
}