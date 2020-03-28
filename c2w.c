
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int);
void generateAlarmWithAlarmHandler();
void createStatusFile();
void addToStatusFile(char[]);
void userInterruptHandler(int);
void mycustom1_handler(int);
void doChildThing(int);
void parentHandler(int);

int main()
{

	int process;
	int childPID;
	int parentPID;

	printf("Main Parent Process Starting\n");

	// printf("Process Forked, process = %d \n", process);
	// if (process < 0)
	// {
	// 	printf("fork failed \n");
	// 	return -1;
	// }

	// else if(process == 0){
	// 	childPID = getpid();
	// 	parentPID = getppid();
	// 	printf("PARENT PID = %d , CHILD PID = %d, Child process created.", parentPID, childPID);
	// 	//addToStatusFile("Child Process Created");

	// 	//printf("%d \n",childPID);
	// 	//generateAlarmWithAlarmHandler();
	// }

	if ((process = fork()) == 0)
	{
		// parentPID = getppid();
		childPID = getpid();
		// printf("PARENT PID = %d, CHILD PID = %d, Child process created.", parentPID, childPID);
		printf("CHILD PID: %d CHILD PROCESS CONTINUES\n", childPID);
		// doChildThing(childPID);
		signal(SIGINT, &userInterruptHandler);
	}
	else
	{
		parentPID = getpid();
		printf("PARENT PID: %d PARENT PROCESS CONTINUES\n", parentPID);
		signal(SIGINT, &parentHandler);
	}

	//addToStatusFile("Parent Process Created");
	//signal(SIGUSR1,mycustom1_handler);
	for (;;)
		;

	return 0;
}

void parentHandler(int signo)
{
	printf("PARENT HANDLER INVOKED");
}

void userInterruptHandler(int signo)
{
	//signal(SIGINT, userInterruptHandler);
	int childPID = getpid();
	int parentPID = getppid();
	printf("\n Interrupt signal has been caught --> PARENT PID = %d , CHILD PID = %d ", parentPID, childPID);
	//kill(childPID, SIGUSR1);
}

void doChildThing(int pid)
{
	printf("CHILD PID: %d, Child process work\n", pid);
	//signal(SIGINT, userInterruptHandler);
	//printf("CHILD PID: %d, SIGINT HANDLER SET\n", pid);
	return;
}

void alarm_handler(int signalBit)
{
	printf("The signal generated from the alarm has been caught");
}

void generateAlarmWithAlarmHandler()
{
	signal(SIGALRM, alarm_handler);
	printf("Setting up Alram\n");
	alarm(5);
}

void createStatusFile()
{
	FILE *fPtr;

	if (access("data/status.txt", F_OK) != -1)
	{
		printf("\nWooo, file already present.\n");
	}
	else
	{
		fPtr = fopen("data/status.txt", "w");
		printf("\nWooo, file created.\n");
		fprintf(fPtr, "*******Log File*******");

		if (fPtr == NULL)
		{
			printf("\nERROR: Unable to create file.\n");
			exit(-1);
		}
		fclose(fPtr);
	}
}

void addToStatusFile(char inputText[1000])
{
	FILE *fPtr;
	time_t clk = time(NULL);

	createStatusFile();
	fPtr = fopen("data/status.txt", "a");
	fprintf(fPtr, "%s: %s", inputText, ctime(&clk));
	fclose(fPtr);
}

void mycustom1_handler(int sig_num)
{
	printf("woo..ctrl-c is pressed..aka TS signal is recieved!\n");
	return;
}
