#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;

    /* Open syslog */
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    /* Check the right amount of arguments */
    if (argc != 3) {
        syslog(LOG_ERR, "Invalid arguments. Usage: %s <file> <string>", argv[0]);
        closelog();
        return EXIT_FAILURE;
    }

    /* Extracting passed agruments */
    const char *filename = argv[1];
    const char *text = argv[2];

    /* Processing arguments based on writer.sh logic */
    fp = fopen(filename, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to open file %s: %s", filename, strerror(errno));
        closelog();
        return EXIT_FAILURE;
    }

    if (fprintf(fp, "%s\n", text) < 0) {
        syslog(LOG_ERR, "Failed to write to file %s: %s", filename, strerror(errno));
        fclose(fp);
        closelog();
        return EXIT_FAILURE;
    }

    fclose(fp);

    /* Writing logs */
    syslog(LOG_DEBUG, "Writing %s to %s", text, filename);

    closelog();
    return EXIT_SUCCESS;
}
