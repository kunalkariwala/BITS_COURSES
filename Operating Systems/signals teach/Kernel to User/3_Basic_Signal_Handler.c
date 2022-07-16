#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_handler(int signum){

  //Return type of the handler function should be void
  printf("\nInside handler function with signal no=%d\n",signum);
}

int main(){
  signal(SIGINT,sig_handler); // Register signal handler // signal() return the signal number. Thus catching the signal
  for(int i=1;;i++){    //Infinite loop
    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
  }
  return 0;
}
