#include <MemoryManage/MemoryManage.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define error(message) fprintf(stderr, "%s-%d%s\n", __FILE__, __LINE__, message);

int main(const int argc, char **argv) {
    if (argc != 2) {
        error("This was a CMake failure and not a program failure.\n");
        return 1;
    }
    printf("Opening %s\n", argv[1]);
    fflush(stdout);

    FILE* target = popen(argv[1], "r");
    printf("Processing %s\n", argv[1]);
    fflush(stdout);
    if (!target) {
        error("This was an OS failure and not a program failure.\n");
        return 1;
    }
    int pid;
    long long int memory;
    char buffer[1024];
    if (fgets(buffer, sizeof buffer, target) == NULL) {
        error("Failed to read from command output.\n");
        return 1;
    }

    sscanf(buffer, "%d %lld\n", &pid, &memory); // NOLINT(*-err34-c)
    printf("PID: %d\nAddress: %lld\n", pid, memory);
    fflush(stdout);

    const process_t process = openProcess(pid);
    if (!process) {
        error("Could not find process.\n");
    }
    printf("Attempting to write memory at address: %lld\n", memory);
    fflush(stdout);

    if (fillMemoryWithByteByLength(process, memory, 13, 'A')==-1) {
        perror(NULL);
        kill(process, SIGKILL);
        return 1;
    }
    printf("Memory written. Waiting for OK from child.\n");
    fflush(stdout);
    char result[3]; // 1,\n,\0
    if (fgets(buffer, sizeof buffer, target) == NULL) {
        error("Failed to read from command output.\n");
        return 1;
    }
    kill(process, SIGKILL);
    if (buffer[0] != '1') {
        fprintf(stderr, "Did not get OK from child process.\n");
        return 1;
    }
    printf("OK Received from child.\n");
    return 0;
}
