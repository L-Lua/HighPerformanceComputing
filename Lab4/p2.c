#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "common.h"
int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        struct timeval stime,etime;
        gettimeofday(&stime, NULL);
        Spin(1);
        gettimeofday(&etime, NULL); 
        printf("Sleep 1 -- Child :  %ld.%ld  ,  %ld.%ld\n",stime.tv_sec,stime.tv_usec,etime.tv_sec,etime.tv_usec);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        struct timeval stime,etime;
        gettimeofday(&stime, NULL);
        Spin(1);
        gettimeofday(&etime, NULL); 
        printf("Sleep 1 -- Parent:  %ld.%ld  ,  %ld.%ld\n",stime.tv_sec,stime.tv_usec,etime.tv_sec,etime.tv_usec);
    }
    return 0;
}
