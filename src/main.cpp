#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include "parse.h"

using namespace std;

void command(char** args) {
    pid_t c_pid, pid;
    int status;
    c_pid = fork();

    if (c_pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (c_pid == 0) {
        execvp(*args, args);
        perror("execvp failed");
    }
    else if (c_pid > 0) {
        if ((pid = wait(&status)) < 0) {
            perror("wait");
            exit(1);
        }
    }
}

int main(void) {
    string user_in;
    Parse in;

    while (1) {
        printf("$ ");
        getline(cin, user_in);
        in.parse_input(user_in);
        if (in.exit()) {
            exit(0);
        }
        command(in.get_cmd());
        printf("\n");
    }

    return 0;
}
