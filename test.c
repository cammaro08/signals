#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
void forkexample() 
{ 
	// child process because return value zero 
	if (fork() == 0){

		int childPID = getpid();
		printf("Hello from Child! CHILD PID: %d\n",childPID); 
		while(1){

		}
	} 
		

	// parent process because return value non-zero. 
	else{

		int parentPID = getpid();
		printf("Hello from Parent! PARENT PID: %d\n",parentPID); 
		while(1){

		}
	}
		
} 
int main() 
{ 
	forkexample(); 
	return 0; 
}