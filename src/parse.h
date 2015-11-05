#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>

#define MAX 80

using namespace std;

class Parse {
    protected:
        char* str; 		//The string entered by the user
        char* cmd[MAX];
    public:
        vector<char*> user_in;  //Stores the seperate words entered by the user
        Parse() {
            str = new char[1];
            str[0] = '\0';
        }
        Parse(char* s) { strcpy(str, s); }
        Parse(string s) { strcpy(str, s.c_str()); }
        ~Parse() { if (str) { delete[] str; } }

        void parse_input(string s) {
            strcpy(str, s.c_str());
            char* pch;
            //cout << "PARSE_INPUT\n";
            pch = strtok(str, " ");
            //cout << "strok(str, " ")\n";
            while (pch != NULL) {
                //printf("%s\n", pch);
                user_in.push_back(pch);
                pch = strtok(NULL, " ");
            }
            //cout << "END WHILE\n";
            user_in.push_back(NULL);
            //cout << "DONE PARSE_INPUT\n";  
        }
        void parse_clear() { user_in.clear(); }
        bool exit() {
            char* e = (char*)"exit";
            //cout << "exit_\n";
            //return (strcmp("here", e) == 0);
            //cout << user_in.size() << endl;
            if (user_in.size() == 1){
                return false;
            }
            return (strcmp(user_in.front(), e) == 0);
        }
        char** get_front_cmd() {
            int size = user_in.size();
            for (int i = 0; i < size; i++) {
                cmd[i] = user_in[i];
            }

            return cmd;
        }
        // has seg fault
        int connectors() {
            int total = 0;
            char* a = (char*)"&&";
            char* o = (char*)"||";
            char* e = (char*)";";

            cout << "black" << endl;

            for (int x = 0, max = user_in.size(); x < max; x++) {
                if (strcmp(a, user_in[x]) == 0 || 
                    strcmp(o, user_in[x]) == 0 || 
                    strcmp(e, user_in[x]) == 0) {
                    total++;
                }
            }
            return total;
        }
        void print_vector() {
            // for (int i = 0, max = user_in.size(); i < max; i++) {
            for (vector<char*>::iterator it = user_in.begin(), end = user_in.end(); it != end; it++) {
                // printf("%s\n", user_in[i]);
                printf("%s\n", *it);
            }
        }
        bool can_move_on() {
            return false;
        }
        void move_on() {
            return 0;
        }

};

#endif
