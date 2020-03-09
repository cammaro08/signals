#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

 void alarm_handler (int);
 void generateAlarmWithAlarmHandler();
 void createStatusFile();
 void addToStatusFile(char []);
 void userInterruptHandler(int);
 void mycustom1_handler(int);

int main()
{
	signal(SIGINT,userInterruptHandler);
	signal(SIGUSR1,mycustom1_handler);


	int process;
	int childPID;
	process=fork();
	
	if (process<0){
		printf("fork failed \n");
	}

	else if(process == 0){
		printf("Child process created");
		addToStatusFile("Child Process Created");
		childPID = getpid();
		printf("%d \n",childPID);
		generateAlarmWithAlarmHandler();
		pause();
	}

	else if(process>0){
		printf("Parent process created.");
		addToStatusFile("Parent Process Created");
	}

	
}

void alarm_handler(int signalBit){
	printf("The signal generated from the alarm has been caught");
}

void generateAlarmWithAlarmHandler(){
	signal(SIGALRM, alarm_handler); 
	printf("Setting up Alram\n");
	alarm(5);
}


void createStatusFile(){
	FILE *fPtr;

	if( access( "data/status.txt", F_OK ) != -1 ) {
		printf("\nWooo, file already present.\n");
	} 
	else {
    	fPtr = fopen("data/status.txt", "w");
		printf("\nWooo, file created.\n");
		fprintf(fPtr,"*******Log File*******");

		if(fPtr == NULL){
			printf("\nERROR: Unable to create file.\n");
			exit(-1);
		}
		fclose(fPtr);
	}

}


void addToStatusFile(char inputText [1000]){
	FILE *fPtr;
	time_t clk = time(NULL);

	createStatusFile();
	fPtr = fopen("data/status.txt", "a");
	fprintf(fPtr, "%s: %s",inputText, ctime(&clk));
	fclose(fPtr);
}


void userInterruptHandler(int signo){
	int childPID = getpid();
	printf("\nInterrupt signal has been");
	kill(childPID, SIGUSR1);

}

void mycustom1_handler (int signo)
{
    printf("woo..ctrl-c is pressed..aka TS signal is recieved!\n");   
	return; 
}