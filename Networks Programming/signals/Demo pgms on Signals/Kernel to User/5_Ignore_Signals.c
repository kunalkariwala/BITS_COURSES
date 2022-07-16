#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int main(){
  signal(SIGINT,SIG_IGN); // Register signal handler for ignoring the signal

  for(int i=1;;i++){    //Infinite loop
    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
  }
  // ? If we do not want this set of code to run uniterrupted
  
  return 0;
}
