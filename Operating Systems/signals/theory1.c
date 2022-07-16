#include <signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void print_signal_info(){
    printf("Total no of signals defined : \t %d\n",NSIG);
    // printf("Range of supported real time signals : \t [ %d, %d]\n",SIGRTMIN,SIGRTMAX);
}

void handle_signal_0(int sig){
    printf("Hello from signal_handler_0! \n");
}

void handle_signal_1(int sig){
    printf("Hello from signal_handler_1! \n");
}

int main(){
    print_signal_info();

    signal(SIGRTMIN+0, handle_signal_0);
    // here SIGRTMIN+0 is the signal number
    // and handle_signal_0 is the pointer to the user defined handler function
    signal(SIGRTMIN+1, handle_signal_1);
    // here SIGRTMIN+1 is the signal number
    // and handle_signal_1 is the pointer to the user defined handler function
}