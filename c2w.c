#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <strings.h>
#include "fileUtils.h"
#include "pyinterop.h"

void alarm_handler(int);
void generateAlarmWithAlarmHandler();
void createStatusFile();
void addToStatusFile(char[]);
void userInterruptHandler(int);
void mycustom1_handler(int);
void childTerminateHandler(int);

int childPID;
int parentPID;
time_t clk;

int main()
{

	int process;
	clk = time(NULL);

	
	printf("Main Parent Process Starting\n");
	

	parentPID = getpid();

	/** CHILD PROCESS **/
	if ((process = fork()) == 0)
	{
		childPID = getpid();

		initializeStatusFile();
    	redirectStdout();

		printf("CHILD PID: %d Child process started %s", childPID,ctime(&clk));
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

		printf("-----------------------------\n");
		printf("Main Parent Process Starting %s",ctime(&clk));

		printf("PARENT PID: %d Parent process started %s",parentPID,ctime(&clk));
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
	printf("CHILD PID: %d Terminating CHILD %s", childPID, ctime(&clk));
	kill(childPID, SIGKILL);
	sleep(1);
}

void userInterruptHandler(int signo)
{
	printf("CHILD PID: %d Interrupt signal has been caught, Sending signal SIGUSR1 %s",childPID, ctime(&clk));
	kill(childPID, SIGUSR1);
	sleep(1);
}

void alarm_handler(int signalBit)
{
	printf("PARENT PID: %d The signal generated from the alarm has been caught. Killing PARENT %s", parentPID, ctime(&clk));
	
	flushOutputAndCloseFile();
	
	kill(childPID, SIGKILL);
	kill(parentPID, SIGKILL);
	sleep(1);
}

void generateAlarmWithAlarmHandler()
{
	signal(SIGALRM, alarm_handler);
	printf("PARENT PID: %d Setting up alarm %s",parentPID, ctime(&clk));
	alarm(5);
}

void mycustom1_handler(int sig_num)
{
	printf("CHILD PID: %d SIGUSR1 signal received %s",childPID, ctime(&clk));
	int r = rand() % 10;
	char strNum[3];
	printf("CHILD PID: %d Random number generated: %d %s", childPID, r, ctime(&clk));
	printf("CHILD PID: %d Adding number to database: %d %s", childPID, r, ctime(&clk)); 
	initPython("db", "putValueInDatabase");
    sprintf(strNum, "%d", r);
	callFunc(strNum);
	printf("CHILD PID: %d Random number added to database: %d %s", childPID, r, ctime(&clk)); 

	
}
