/*
 ____  _                   _   _____      _             _       _ 
/ ___|(_) __ _ _ __   __ _| | |_   _|   _| |_ ___  _ __(_) __ _| |
\___ \| |/ _` | '_ \ / _` | |   | || | | | __/ _ \| '__| |/ _` | |
 ___) | | (_| | | | | (_| | |   | || |_| | || (_) | |  | | (_| | |
|____/|_|\__, |_| |_|\__,_|_|   |_| \__,_|\__\___/|_|  |_|\__,_|_|
         |___/                                                   

Reading material: 
    $ man signal
    https://man7.org/linux/man-pages/man7/signal.7.html
*/

/* 
What are signals?
- Signals are software interrupts delivered to a process by the operating system. 
- Can be used for inter-process communication (IPC)
- When a process or thread has received a signal, the process or thread will stop what it is doing and take some action.

Signals in C
- Standard signals are defined in signals.h header file. [Try to find it!]
- These are macro constants, each signal having a unique int value.
- Signal name format: "SIG" followed by a short description of the signal
- But we always use the name of the signal and not the number. [Why is this?]
- Some other macros are also present like NSIG which gives the number of defined signals.
*/

#include<signal.h>  // <=====
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
Types of signals
- Standard signals
    - SIGSTOP - stops the process, can be collected by WUNTRACED option in waitpid()
    - SIGCONT - continues the process
    - SIGTERM - gracefully kills the process
    - SIGKILL - kills the process immediately
    - SIGINT  - Interrupt the process
    ...
- Real time signals
    - The range of supported real-time signals is defined by the macros SIGRTMIN and SIGRTMAX.
    - Linux kernel supports a range of 33 different real-time signals, numbered 32 to 64.
*/

void print_signal_info(){
    printf("Total number of signals defined:\t%d\n", NSIG);
    printf("Range of supported real-time signals:\t[%d, %d]\n", SIGRTMIN, SIGRTMAX);
}

/*
However, the glibc POSIX threads implementation internally uses two (for NPTL) or three (for LinuxThreads) real-time signals (see pthreads(7)), and adjusts the value of SIGRTMIN suitably (to 34 or 35).  Because the range of available real-time signals varies according to the glibc threading implementation (and this variation can occur at run time according to the available kernel and glibc), and indeed the range of real-time signals varies across UNIX systems, programs should never refer to real-time signals using hard-coded numbers, but instead should always refer to real-time signals using the notation SIGRTMIN+n, and include suitable (run-time) checks that SIGRTMIN+n does not exceed SIGRTMAX.
*/

/* 
SIGNAL Handling
- Each signal has a default action based on its type: 
    - terminate
    - terminate and produce a core dump file
    - ignore
    - stop
    - continue.
- Choice of action
    - If the specified action is ignores, then ignore the signal
    - If handler function is specified, it will be executed
    - If neither, the default action will take place
- The default action for an unhandled real-time signal is to terminate the receiving process.
- SIGKILL and SIGABRT signal’s default action cannot be changed or ignored.
*/

/* 
SIGNAL HANDLER
User defined handler function pointer: void(*)(int)
- return type is void and one argument of type int
*/

void handle_signal_0(int sig){
    printf("Hello from signal handler 0!\n");
}
void handle_signal_1(int sig){
    printf("Hello from signal handler 1!\n");
}
void handle_signal_sigint(int sig);
void handle_signal_sigtstp(int sig);


int main(){

    print_signal_info();

    /*
    Trapping events using signal() function.

    signal(): 
        void (*signal(int sig, void (*func)(int)))(int)
        
        Arguments:
        - arg1: an integer representing signal number
        - arg2: one of the following
            - pointer to the signal-handling function
            - SIG_DFL: default action for that particular signal.
            - SIG_IGN: signal is ignored.

        Return value:
        On success, previous value of the signal handler, or SIG_ERR on error
    */

    signal(SIGRTMIN+0, handle_signal_0);
    signal(SIGRTMIN+1, handle_signal_1);

    /*
    Sending a signal

    The following system calls and library functions allow the caller to send a signal: 
        raise(), kill(), pidfd_send_signal(), killpg(), pthread_kill(), tgkill(),
        sigqueue() - Sends a real-time signal with accompanying data to a specified process.

    kill()
        int kill(pid_t pid, int sig);

        The kill() system call can be used to send any signal to any
        process group or process.

        Arguments:
        - arg1: pid
            - If pid is positive, then signal sig is sent to the process with the ID specified by pid.
            - If pid equals 0, then sig is sent to every process in the process group of the calling process.
            - If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below.
            - If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.
        - arg2: signal number
            - If sig is 0, then no signal is sent, but existence and permission checks are still performed; this can be used to check for the existence of a process ID or process group ID that the caller is permitted to signal.

        Return value:
        - On success (at least one signal was sent), zero is returned.
        - On error, -1 is returned, and errno is set to indicate the error.
    */

    // printf("\nSending signal to the process %d using kill()\n", getpid());
    // kill(getpid(), SIGRTMIN+0);
    // printf("Back to main function()\n");

    /*
    raise()
        int raise(int sig);

        The raise() function sends a signal to the calling process or thread.  
        In a single-threaded program it is equivalent to
            kill(getpid(), sig);
        In a multithreaded program it is equivalent to
            pthread_kill(pthread_self(), sig);
        If the signal causes a handler to be called, raise() will return only after the signal handler has returned.

        Arguments:
        - arg1: signal number

        Return value:
            raise() returns 0 on success, and nonzero for failure.
    */

    // printf("\nSending signal to the calling process using raise()\n");
    // raise(SIGRTMIN+1);
    // printf("Back to main function()\n");

    // printf("\nThe process terminates on receiving an unknown signal\n");
    // raise(SIGRTMIN+2);
    // printf("Back to main function()\n");

    // signal(SIGRTMIN+0, SIG_IGN);
    // printf("\nSending signal to the process %d using kill()\n", getpid());
    // kill(getpid(), SIGRTMIN+0);
    // printf("Back to main function()\n");

    // signal(SIGRTMIN+0, SIG_DFL);
    // printf("\nSending signal to the process %d using kill()\n", getpid());
    // kill(getpid(), SIGRTMIN+0);
    // printf("Back to main function()\n");

    // signal(SIGINT, handle_signal_sigint);
    // signal(SIGTSTP, handle_signal_sigtstp);
    // while(1);

    return 0;
}






// Standard signal handler definitions
void handle_signal_sigint(int sig){
    printf("\nYou can't ctrl+c me! I am stronger than you think.\n");
}
void handle_signal_sigtstp(int sig){
    printf("\nOk, you win :/\n");
    exit(0);
}