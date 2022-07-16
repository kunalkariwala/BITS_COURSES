#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int main()
{
    int pid1,pid2;
    pid1=fork();
    if(pid1==0)
    {
        while(1)
        {
            printf("pid1 is alive\n");
            sleep(1);
        }
    }
    pid2=fork();
    if(pid2==0)
    {
        while(1)
        {
            printf("pid2 is alive\n");
            sleep(1);
        }
    }
    sleep(3);
    kill(pid1,SIGSTOP);//suspend first child
    sleep(3);
    kill(pid1,SIGCONT);//resume first child
    sleep(3);
    kill(pid1,SIGINT);//kill first child
    kill(pid2,SIGINT);//kill second child
}
