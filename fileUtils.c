#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fileUtils.h"
#include <sys/types.h>
#include <sys/stat.h>


int out;
int save_out;

// int main(int argc, const char *argv[])
// {
 
//     initializeStatusFile();
//     redirectStdout();
//     //printf("HOWDY!");
//     writeFileMetaData();
//     flushOutputAndCloseFile();

//     return 0;
// }

void initializeStatusFile() {
    out = open("data/cout.log", O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { perror("opening cout.log"); exit(255); }
}

void redirectStdout() {
   save_out = dup(fileno(stdout));

    if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); exit(255); }
 
}

void flushOutputAndCloseFile() {
    fflush(stdout); close(out);
    dup2(save_out, fileno(stdout));
    close(save_out);

}

void writeFileMetaData() {
    struct stat attrib;
    stat("data/cout.log", &attrib);
    printf("\n\n METADATA %ln", &attrib.st_mtime);
}