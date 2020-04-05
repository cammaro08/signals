#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fileUtils.h"
#include <sys/types.h>
#include <sys/stat.h>


int out;
int save_out;

void initializeStatusFile() {
    out = open("files/status.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { perror("cant open status file"); exit(255); }
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
    stat("files/status.txt", &attrib);
    printf("\n\n METADATA %ln", &attrib.st_mtime);
}