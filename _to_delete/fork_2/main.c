#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Pipes for Child 1
    int fd1_parent_to_child[2];
    int fd1_child_to_parent[2];
    pipe(fd1_parent_to_child);
    pipe(fd1_child_to_parent);

    // Pipes for Child 2
    int fd2_parent_to_child[2];
    int fd2_child_to_parent[2];
    pipe(fd2_parent_to_child);
    pipe(fd2_child_to_parent);

    pid_t pid;

    // -------------------- Child 1 --------------------
    pid = fork();
    if (pid == 0) {
        // Child closes unused ends
        close(fd1_parent_to_child[1]);
        close(fd1_child_to_parent[0]);

        // Close all unused pipes
        close(fd2_parent_to_child[0]); close(fd2_parent_to_child[1]);
        close(fd2_child_to_parent[0]); close(fd2_child_to_parent[1]);

        char read_fd_str[10], write_fd_str[10];
        sprintf(read_fd_str, "%d", fd1_parent_to_child[0]);
        sprintf(write_fd_str, "%d", fd1_child_to_parent[1]);

        execl("./child", "child", "Child 1", read_fd_str, write_fd_str, NULL);
        perror("execl failed");
        exit(1);
    }

    // -------------------- Child 2 --------------------
    pid = fork();
    if (pid == 0) {
        close(fd2_parent_to_child[1]);
        close(fd2_child_to_parent[0]);

        close(fd1_parent_to_child[0]); close(fd1_parent_to_child[1]);
        close(fd1_child_to_parent[0]); close(fd1_child_to_parent[1]);

        char read_fd_str[10], write_fd_str[10];
        sprintf(read_fd_str, "%d", fd2_parent_to_child[0]);
        sprintf(write_fd_str, "%d", fd2_child_to_parent[1]);

        execl("./child", "child", "Child 2", read_fd_str, write_fd_str, NULL);
        perror("execl failed");
        exit(1);
    }

    // -------------------- Parent --------------------
    // Close child read/write ends
    close(fd1_parent_to_child[0]); // parent does not read here
    close(fd1_child_to_parent[1]); // child writes to parent here
    close(fd2_parent_to_child[0]);
    close(fd2_child_to_parent[1]);

    // Send messages to children
    write(fd1_parent_to_child[1], "Hello Child 1", 14);
    write(fd2_parent_to_child[1], "Hello Child 23", 15);

    // Close write ends after sending
    close(fd1_parent_to_child[1]);
    close(fd2_parent_to_child[1]);

    // Read results from children
    int result1, result2;
    read(fd1_child_to_parent[0], &result1, sizeof(result1));
    read(fd2_child_to_parent[0], &result2, sizeof(result2));

    printf("Child 1 returned: %d\n", result1);
    printf("Child 2 returned: %d\n", result2);

    // Close read ends
    close(fd1_child_to_parent[0]);
    close(fd2_child_to_parent[0]);

    // Wait for children to exit
    wait(NULL);
    wait(NULL);

    return 0;
}
