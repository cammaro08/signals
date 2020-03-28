#include <stdio.h>
#include <signal.h>

 void alarm_handler (int);

int main()
{
	signal(SIGALRM, alarm_handler); 
	printf("Setting up Alram\n");
	alarm(5);
	pause();
}

void alarm_handler(int signalBit){
	
	printf("The signal generated from the alarm has been caught");
}
