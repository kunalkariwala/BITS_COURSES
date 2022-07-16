#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


//Common signal
// SIGKILL - Terminate process istantly
// SIGSTOP - Stop the execution of process
// SIGCONT - Continue execution of stopped process


void process_1(){
	for(int i = 0;; i++){
		printf("Iteration no.: %d\n", i);
	}
}
 
void process_2(){
	
	sleep(1);
	kill(getppid(), SIGSTOP);

	printf("Start other process again? (y/n)");
	char reply;
	scanf("%c", &reply);
	if(reply == 'y')
	{
		kill(getppid(), SIGCONT);
		sleep(1);
	}

	kill(getppid(), SIGKILL);
	exit(0);	
}

int main(int argc, char *argv[])
{
	int pid1=fork();
	if(pid1==0){
		int pid2 = fork();
		if(pid2==0)
			process_2(); 
		process_1();
	}
	wait(NULL);
	return 0;
}