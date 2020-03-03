#include <stdio.h>
#include <signal.h>

 void alarm_handler (int);

int main()
{
	int process;
	process=fork();

	if (process<0){
		printf("fork failed");
	}

	else if(process == 0){
		printf("Child process created");
	}

	else if(process>0){
		printf("Only Parent process running");
	}

	signal(SIGALRM, alarm_handler); 
	printf("Setting up Alram\n");
	alarm(5);
	pause();
}

void alarm_handler(int signalBit){
	
	printf("The signal generated from the alarm has been caught");
}
