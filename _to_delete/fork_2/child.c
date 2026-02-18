#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <child_name> <read_fd> <write_fd>\n", argv[0]);
        return 1;
    }

    char *child_name = argv[1];
    int read_fd = atoi(argv[2]);   // Parent → Child
    int write_fd = atoi(argv[3]);  // Child → Parent

    // Step 1: read message from parent
    char buf[100];
    ssize_t n = read(read_fd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("read failed");
        exit(1);
    }
    buf[n] = '\0';
    printf("%s received: %s\n", child_name, buf);
    fflush(stdout);

    // Step 2: compute a result (example: length of the message)
    int result = (int)strlen(buf);

    // Step 3: send result back to parent
    if (write(write_fd, &result, sizeof(result)) < 0) {
        perror("write failed");
        exit(1);
    }

    close(read_fd);
    close(write_fd);
    return 0;
}
