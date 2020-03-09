#include <stdio.h> 
#include <signal.h> 


void sigintHandler(int sig_num) 
{ 
    /* Reset handler to catch SIGINT next time. 
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler); 
    printf("\n Cannot be terminated using Ctrl+C \n"); 
    // fflush(stdout); 
} 

void mycustom1_handler (int signo)
{
    printf("woo..ctrl-c is pressed..aka TS signal is recieved!\n");   
	return; 
}


int main () 
{ 
    /* Set the SIGINT (Ctrl-C) signal handler to sigintHandler  
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler); 
    signal(SIGUSR1,mycustom1_handler);
    /* Infinite loop */
    while(1) 
    {         
    } 
    return 0; 
} 


