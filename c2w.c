#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

 void alarm_handler (int);
 void generateAlarmWithAlarmHandler();
 void createStatusFile();
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
		printf("Parent process running at %s",ctime(&clk));
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


void createStatusFile(){
	FILE *fPtr;

	if( access( "data/status.txt", F_OK ) != -1 ) {
		printf("wooo, file already present.\n");
	} 
	else {
    	fPtr = fopen("data/status.txt", "w");
		printf("wooo, file created.\n");

		if(fPtr == NULL){
			printf("Unable to create file.\n");
			exit(-1);
		}
		fclose(fPtr);
	}

}


void addToStatusFile(char input [1000]){
	createStatusFile();
	return ;
}

