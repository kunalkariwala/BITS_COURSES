#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int alarmFlag=0; //Global alarm flag
void alarmHandler();//forward declaration of alarm handler
int main()
{
    int i=1;
    signal (SIGALRM, alarmHandler); //Install signal handler
    alarm(3); //schedule an alarm signal in three seconds
    
    while(!alarmFlag)//loop until flag set
    {   printf("Looping...%d\n",i++);
        pause();//wait for a signal
    }
    printf("Loop ends due to alarm signal\n");
}
void alarmHandler()
{
  printf("An alarm clock signal was received\n");
  alarmFlag=1;
}
