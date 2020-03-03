#include <stdio.h>
#include <time.h>
#include <signal.h>

 void alarm_handler (int);
 void generateAlarmWithAlarmHandler();
 void addToStatusFile(char []);

int main()
{
	time_t clk = time(NULL);
	int process;
	int childPID;
	process=fork();

	if (process<0){
		printf("fork failed \n");
	}

	else if(process == 0){
		printf("Child process created at %s",ctime(&clk));
		childPID = getpid();
		printf("%d \n",childPID);
		generateAlarmWithAlarmHandler();
	}

	else if(process>0){
		printf("Parent process running at %s\n",ctime(&clk));
		addToStatusFile("jlmoasdsdsd");
	}


}

void alarm_handler(int signalBit){
	printf("The signal generated from the alarm has been caught");
}

void generateAlarmWithAlarmHandler(){
	signal(SIGALRM, alarm_handler); 
	printf("Setting up Alram\n");
	alarm(5);
	pause();
}

void addToStatusFile(char input [1000]){
	printf("got this input %s\n", input);
	return ;
}