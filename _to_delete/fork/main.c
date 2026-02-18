#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{

    int myNumbers[] = {10, 20, 30, 40, 0, 10, 20, 30, 40, 0};

    /* Kreiere pipe */
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    pid_t child1_pid = fork();
    if (child1_pid == 0) {
        printf("This is child 1! \n");

        close(fd1[1]);   // write end schließen
        close(fd2[0]); close(fd2[1]); // unbenutzt

        char buf[100];
        read(fd1[0], buf, sizeof(buf));

        printf("Child 1 received: %s\n", buf);
        close(fd1[0]); 

        exit(0);
    }

    pid_t child2_pid = fork();
    if (child2_pid == 0) {
        printf("This is child 2! \n");

        close(fd2[1]);   // write end schließen
        close(fd1[0]); close(fd1[1]); // unbenutzt

        char buf[100];
        read(fd2[0], buf, sizeof(buf));

        printf("Child 2 received: %s\n", buf);
        close(fd2[0]); 


        exit(0);
    }

    close(fd1[0]);
    close(fd2[0]);

    write(fd1[1], "Hello Child 1", 14);
    write(fd2[1], "Hello Child 2", 14);

    close(fd1[1]);
    close(fd2[1]);
    
}