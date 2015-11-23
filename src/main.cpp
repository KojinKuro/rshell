#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <string>
#include "parse.h"

#define MAX 80

using namespace std;

// ALL HELPER FUNCTIONS FOR COMMANDHELPER
bool isCustomCommand(char** args) {
    // grabs the first word input
    vector<char*> temp_commands;
    // puts everything into word by word into temp_commands
    for(int i=0; args[i] != NULL; ++i)
        temp_commands.push_back(args[i]);
    
    // checks to see if custom command
    if(!strcmp(temp_commands.front(), "exit") ||
       !strcmp(temp_commands.front(), "test")) {
        return true;
    } return false;
}

// handles test
bool FileExists(char *path) {
    struct stat fileStat;
    // does it exist
    if ( stat(path, &fileStat) )
        return false;
    // is it a folder
    if ( !S_ISREG(fileStat.st_mode) )
        return false;
    return true;
}

bool DirExists(char *path) {
    struct stat fileStat;
    // does it exist
    if ( stat(path, &fileStat) )
        return false;
    // is it a directory
    if ( !S_ISDIR(fileStat.st_mode) )
        return false;
    return true;
}
// END OF ALL HELPER FUNCTIONS


bool commandHandler(char** args) {
    // grabs the first word input
    vector<char*> temp_commands;
    // puts everything into word by word into temp_commands
    for(int i=0; args[i] != NULL; ++i)
        temp_commands.push_back(args[i]);
    
    // handles exit command word
    if(!strcmp(temp_commands.front(),"exit")){
        exit(0);
        return true;
        // handles test command word
    } else if (!strcmp(temp_commands.front(),"test") && (temp_commands.size() == 2 || temp_commands.size() == 3)) {
        if(temp_commands.size() == 2) {
            if(FileExists(temp_commands.at(1)) || DirExists(temp_commands.at(1)))
                return true;
            else
                return false;
        } else if(temp_commands.size() == 3) {
            if(strcmp(temp_commands.at(1),"-e")) {
                if(FileExists(temp_commands.at(1)) || DirExists(temp_commands.at(1)))
                    return true;
                else
                    return false;
            } else if(temp_commands.at(1),"-f") {
                if(FileExists(temp_commands.at(2)))
                    return true;
                else
                    return false;
            } else if(temp_commands.at(1),"-d") {
                if(DirExists(temp_commands.at(2)))
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
    return args;
}

//forks a new procces
bool command (char** args) {
    //std::cout << "in command\n";
    //for(int i = 0; args[i] != NULL; i++){
    // std::cout << args[i];
    //}
    //std::cout << std::endl;
    
    /* handles all custom commands
     * test, [ ], exit
     */
    if(isCustomCommand(args)) {
        return commandHandler(args);
    } else {
        bool data = true;
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
            exit(0);
        }
        else if (c_pid > 0 && (pid = wait(&status)) < 0) {
            perror("wait");
            exit(1);
        }
        return data;
    }
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
        //cout << "beggining\n";
        prompt(); getline(cin, user_in);
        //std::cout << "user input\n";
        in.parse_input(user_in);
        //std::cout << "in.parse_input\n";
        //if (in.exit()) { exit(0); }
        //std::cout << "exit\n";
        
        while(in.cmd_front()) {
            in.set_bool(command(in.get_front_cmd()));
            in.run_logic();
        }
        
        //std::cout << "in.get_cmd\n";
        //printf("\n");
        //cout << in.connectors() << endl;
        //std::cout << "parse_clear\n";
    }
    
    return 0;
}
