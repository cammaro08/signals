#include <stdlib.h>
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
void childTerminateHandler(int);
void doChildThing(int);
void parentHandler(int);

int childPID;
int parentPID;

int main()
{

	int process;

	fprintf(stderr, "Main Parent Process Starting\n");

	parentPID = getpid();

	/** CHILD PROCESS **/
	if ((process = fork()) == 0)
	{
		childPID = getpid();

		printf("CHILD PID: %d CHILD PROCESS CONTINUES\n", childPID);
		signal(SIGINT, &userInterruptHandler);
		signal(SIGUSR1, &mycustom1_handler);
		signal(SIGSTOP, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else
	{
	/** PARENT PROCESS **/
		childPID = process;
		printf("PARENT PID: %d PARENT PROCESS CONTINUES CHILD PID: %d\n", parentPID, childPID);
		signal(SIGINT, &parentHandler);
		signal(SIGTSTP, &childTerminateHandler);
		signal(SIGSTOP, &childTerminateHandler);
		generateAlarmWithAlarmHandler();
	}

	//addToStatusFile("Parent Process Created");
	for (;;);
	return 0;
}

void childTerminateHandler(int signo)
{
	printf("\n CHILD PID: %d exiting", childPID);
	sleep(1);
	kill(childPID, SIGKILL);
}

void parentHandler(int signo)
{
	fprintf(stdout, "PARENT HANDLER INVOKED");
}

void userInterruptHandler(int signo)
{
	printf("\n Interrupt signal has been caught --> PARENT PID = %d , CHILD PID = %d ", parentPID, childPID);
	sleep(1);
	kill(childPID, SIGUSR1);
}

void doChildThing(int pid)
{
	printf("CHILD PID: %d, Child process work\n", pid);
}

void alarm_handler(int signalBit)
{
	fprintf(stderr, "\n The signal generated from the alarm has been caught. Killing PARENT PID %d", parentPID);
	kill(childPID, SIGKILL);
	kill(parentPID, SIGKILL);
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
	printf("\n SIGUSR1 SIGNAL RECEIVED: woo..ctrl-c is pressed..aka TS signal is recieved!\n");
	return;
}
