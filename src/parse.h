#ifndef _PARSE_H
#define _PARSE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <list>
#include <queue>

#define MAX 80

using namespace std;


class Parse {
    protected:
        char* str; 		//The string entered by the user
        queue<char**> cmds; // The final commands that are going to used
    public:
        vector<char*> user_in;  // Stores the seperate words entered by the user
        vector<int> logic;      // Stores the logic for the user_input
                                // 0: ; 1: || 2: &&
        bool global_bool_val;


        Parse() {
            str = new char[MAX];
            str[0] = '\0';
        }
        Parse(char* s) { strcpy(str, s); }
        Parse(string s) { strcpy(str, s.c_str()); }
        ~Parse() { if (str) { delete[] str; } }

        void parse_input(string s) {
            strcpy(str, s.c_str());
            char* pch;
              /*cout << "PARSE_INPUT\n";
            pch = strtok(str, " ");
              //cout << "strok(str, " ")\n";
            while (pch != NULL) {
                //printf("%s\n", pch);
                if(pch[0] == '#'){
                    break;
                }
                user_in.push_back(pch);
                pch = strtok(NULL, " ");
            }
              cout << "END WHILE\n";
            user_in.push_back(NULL);
              cout << "DONE PARSE_INPUT\n";*/

            // puts the words from user_input back together
            /*s = (string)user_in.front() + " ";
            user_in.pop_front();
            while (!user_in.empty()) {
                s += (string)user_in.front() + " ";
                user_in.pop_front();
            }*/
 
            int comment = s.find_first_of("#", 0);
            if(comment != -1){
                s = s.substr(0,comment-1);
            }
            while (s.size()) {
                //cout << "PROBABLY STUCK HERE\n";
                // set up the variables
                int semi = s.find_first_of(";", 0);
                int orrr = s.find_first_of("||", 0);
                int andd = s.find_first_of("&&", 0);

                int pos = smallest(semi, orrr, andd);
                cout << pos << "\n";
                // this is for sitatuions where nothing can be found
                if(pos == -1) {// needs to be fixed for base case
                    strcpy(str,s.c_str());
                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    logic.push_back(0);
                    //cout << "strok(str, " ")\n";
                    
                    int i; // decalred otuside for loop
                    for (i = 0; pch != NULL; ++i) {
                        //printf("%s\n", pch);
                        value[i] = pch;
                        pch = strtok(NULL, " ");
                    }
                    value[++i] = NULL;
                    cmds.push(value);
                    //for(int i = 0; value[i] != NULL; i++){
                      //  cout << value[i];
                    //}
                    //cout << "\n";
                    break;
                }
                else if (pos == semi) {
                    strcpy(str,s.substr(0,pos-1).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos);
                    //str = str.substr(0,str.size()-1);
                    logic.push_back(0);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    //cout << "strok(str, " ")\n";
                    
                    int i; // decalred otuside for loop
                    for (i = 0; pch != NULL; ++i) {
                        //printf("%s\n", pch);
                        value[i] = pch;
                        pch = strtok(NULL, " ");
                    }
                    value[++i] = NULL;
                    cmds.push(value);
                      //cout << "END WHILE\n";
                }
                else if (pos == orrr) {
                    strcpy(str,s.substr(0,pos-1).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos);
                    //str = str.substr(0,str.size()-1);
                    logic.push_back(1);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    //cout << "strok(str, " ")\n";
                    
                    int i; // decalred otuside for loop
                    for (i = 0; pch != NULL; ++i) {
                        //printf("%s\n", pch);
                        value[i] = pch;
                        pch = strtok(NULL, " ");
                    }
                    value[++i] = NULL;
                    cmds.push(value);
                      //cout << "END WHILE\n";
                }
                else if (pos == andd) {
                    strcpy(str,s.substr(0,pos-1).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos);
                    //str = str.substr(0,str.size()-1);
                    logic.push_back(2);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    //cout << "strok(str, " ")\n";
                    
                    int i; // decalred otuside for loop
                    for (i = 0; pch != NULL; ++i) {
                        //printf("%s\n", pch);
                        value[i] = pch;
                        pch = strtok(NULL, " ");
                    }
                    value[++i] = NULL;
                    cmds.push(value);
                      //cout << "END WHILE\n";
                }
            }
            //cout << "NOPE TO BAD\n";
        }
        void parse_clear() { user_in.clear(); }
        /*bool exit() {
            char* e = (char*)"exit";
              cout << "exit_\n";
            //return (strcmp("here", e) == 0);
              cout << user_in.size() << endl;
            if (user_in.size() == 1){
                return false;
            }
            return (strcmp(user_in.front(), e) == 0);
        }*/
        char** get_front_cmd() {
            char** temp = cmds.front();
            cmds.pop();
            return temp;
        }
        bool cmd_front(){
            return !cmds.empty();
        }
        /*void print_vector() {
            // for (int i = 0, max = user_in.size(); i < max; i++) {
            for (vector<char*>::iterator it = user_in.begin(), end = user_in.end(); it != end; it++) {
                // printf("%s\n", user_in[i]);
                printf("%s\n", *it);
            }
        }*/

        // helper math funciton that returns the samllest number of 3 numbers
        int smallest(int x, int y, int z) {
            int result;
            if(x == y && y == z && z == -1){
                return -1;
            }
            if(x != -1){
                result = x;
            }
            else if(y != -1){
                result = y;
            }
            else{
                return z;
            }
            if (y < result && y != 0) { result = y; }
            if (z < result && z != 0) { result = z; }
            return result;
        }

};

#endif
