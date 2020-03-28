#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "fileUtils.h"

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


	printf("Main Parent Process Starting\n");

	

	parentPID = getpid();

	/** CHILD PROCESS **/
	if ((process = fork()) == 0)
	{
		childPID = getpid();

		initializeStatusFile();
    	redirectStdout();

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

		initializeStatusFile();
    	redirectStdout();
		printf("PARENT PID: %d PARENT PROCESS CONTINUES CHILD PID: %d\n", parentPID, childPID);
		signal(SIGINT, SIG_IGN);
		signal(SIGTSTP, &childTerminateHandler);
		signal(SIGSTOP, &childTerminateHandler);
		srand(time(NULL));   // Initialization, should only be called once.
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
	printf("PARENT HANDLER INVOKED");
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
	printf("\n The signal generated from the alarm has been caught. Killing PARENT PID %d", parentPID);
	
	flushOutputAndCloseFile();
	
	kill(childPID, SIGKILL);
	kill(parentPID, SIGKILL);
}

void generateAlarmWithAlarmHandler()
{
	signal(SIGALRM, alarm_handler);
	printf("Setting up Alram\n");
	alarm(5);
}

void mycustom1_handler(int sig_num)
{
	printf("\n SIGUSR1 SIGNAL RECEIVED: woo..ctrl-c is pressed..aka TS signal is recieved!\n");
	int r = rand() % 10;
	printf("CHILD PID: %d RANDOM NUMBER GENERATED: %d", childPID, r); 
	
}
