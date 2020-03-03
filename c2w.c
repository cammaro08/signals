#include <stdio.h>
#include <signal.h>

 void alarm_handler (int);
 void generateAlarmWithHandler();

int main()
{
	int process;
	process=fork();

	if (process<0){
		printf("fork failed \n");
	}

	else if(process == 0){
		printf("Child process created \n");
		printf("%d \n",getpid());
		generateAlarmWithHandler();
	}

	else if(process>0){
		printf("Parent process running \n");
	}


}

void alarm_handler(int signalBit){
	printf("The signal generated from the alarm has been caught");
}

void generateAlarmWithHandler(){
	signal(SIGALRM, alarm_handler); 
	printf("Setting up Alram\n");
	alarm(5);
	pause();
}