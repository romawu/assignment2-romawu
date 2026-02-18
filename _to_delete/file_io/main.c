#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    // if (argc != 3) {
    //     fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    /* Extracting passed agruments */
    const char *filename = argv[1];
    const char *text = argv[2];

    int fd = open("new_file.txt", O_RDWR | O_CREAT);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    printf("Opened file descriptor: %d\n", fd);
    write(fd, "Hello\n", 6);

    lseek(fd, 0, SEEK_SET);

    char buf[100];
    ssize_t nr = read(fd, buf, sizeof(buf)-1);
    printf("File descriptor %d content: %s\n", fd, buf);


    // /* Processing arguments based on writer.sh logic */
    // fp = fopen(filename, "w");
    // if (fp == NULL) {
    //     syslog(LOG_ERR, "Failed to open file %s: %s", filename, strerror(errno));
    //     closelog();
    //     return EXIT_FAILURE;
    // }

    // if (fprintf(fp, "%s\n", text) < 0) {
    //     syslog(LOG_ERR, "Failed to write to file %s: %s", filename, strerror(errno));
    //     fclose(fp);
    //     closelog();
    //     return EXIT_FAILURE;
    // }

    // fclose(fp);

    // printf("Writing %s to %s\n", text, filename);
}