#include <unistd.h>

int main (int argc, char** argv) {
    pid_t pid = fork();

    if (pid == 0) {
        execv("sequential_min_max", argv);
    }

    return 0;
}
