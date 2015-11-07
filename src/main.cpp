#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include "parse.h"

//forks a new procces
bool command (char** args) {
    std::cout << "in command\n";
    bool data = 1;
    pid_t c_pid, pid;
    int status;
    c_pid = fork();

    if (c_pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (c_pid == 0) {
        data = execvp(*args, args);
        perror("execvp failed");
    }
    else if (c_pid > 0 && (pid = wait(&status)) < 0) {
        perror("wait");
        exit(1);
    }
    return data;
}

// provides the user@hostname $
void prompt() {
    if ( getlogin() != NULL )            // only runs if there is a login user
        std::cout << getlogin() << "@";
    char hostname[254];                  // can hold a 255 character hostname
    if( gethostname(hostname, 255) )     // only runs if there is a host
        std::cout << hostname << " ";
   std::cout << "$" << " ";
}

int main (void) {
    //std::cout << "main\n";
    string user_in;    // the values of the string go into here
    Parse in;         // object that handles all of the commands

    while (true) {
        cout << "beggining\n";
        prompt(); getline(cin, user_in);
        std::cout << "user input\n";
        in.parse_input(user_in);
        std::cout << "in.parse_input\n";
        //if (in.exit()) { exit(0); }
        //std::cout << "exit\n";
        while(in.cmd_front()) {
            command(in.get_front_cmd());
        }

        std::cout << "in.get_cmd\n";
        printf("\n");
        //cout << in.connectors() << endl;
        in.parse_clear();
        std::cout << "parse_clear\n";
    }

    return 0;
}
