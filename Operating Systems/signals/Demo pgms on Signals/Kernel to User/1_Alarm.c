#include<stdio.h>
#include<unistd.h> //for alarm()
int main()
{   int i=1;
    alarm(3); //schedule an alarm signal in three seconds
    printf("Looping forever...\n");
    while(1)
    	 printf("i=%d\n",i++);
}
