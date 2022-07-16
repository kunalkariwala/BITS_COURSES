#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int signum){
  printf("\nInside handler function\n");
  signal(SIGINT,SIG_DFL);   
  // Re Register signal handler for default action
  // ? For some time, we change the signal handler to something
  // ? We want, then revert it back to its default action
}

int main(){
  signal(SIGINT,sig_handler); // Register signal handler
  for(int i=1;;i++){    //Infinite loop
    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
  }
  return 0;
}
