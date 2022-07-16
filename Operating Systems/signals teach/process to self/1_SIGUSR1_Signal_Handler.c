#include<stdio.h>
#include<signal.h>

void sig_handler(int signum){
  printf("Inside handler function with num=%d\n",signum);
  
}

int main(){
  signal(SIGUSR1,sig_handler); // Register signal handler. simi you can use SIGUSR2
 // execute kill -l and  see the numbers 10 and 12
  printf("Inside main function\n");
  raise(SIGUSR1);
  
  signal(SIGUSR2,sig_handler); // Register signal handler. simi you can use SIGUSR2
  printf("Inside main function\n");
  raise(SIGUSR2);
  return 0;
}
