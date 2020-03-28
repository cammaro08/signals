#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

 void alarm_handler (int);
 void createStatusFile();
 void addToStatusFile();

int main()
{

	pause();
	return 0;
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