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
        queue<int> logic;      // Stores the logic for the user_input
                                // 0: ; 1: || 2: &&
        int bool_val;      // Fake "bool" to control logic
        // dumb helper functions to set bool_val
        void set_bool( bool val ) { 
            if ( val ) { bool_val = 1; }
            else { bool_val = 0; }
        }
        void reset_bool() { bool_val = -1; }

        Parse() : bool_val(-1) {
            str = new char[MAX];
            str[0] = '\0';
        }
        Parse(char* s) : bool_val(-1) { strcpy(str, s); }
        Parse(string s) : bool_val(-1) { strcpy(str, s.c_str()); }
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

                cout << semi << " " << orrr << " " << andd << endl;
                int pos = smallest(semi, orrr, andd);
                cout << pos << "\n";

                //break;

                // this is for sitatuions where nothing can be found
                if(pos == -1) {// needs to be fixed for base case
                    strcpy(str,s.c_str());
                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    for(int i = 0; i < MAX; i++){
                        value[1] = new char[MAX]();
                    }
                    logic.push(0);
                    s.erase(0,pos);
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
                    strcpy(str,s.substr(0,pos).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos+1);
                    //str = str.substr(0,str.size()-1);
                    logic.push(0);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    for(int i = 0; i < MAX; i++){
                        value[1] = new char[MAX]();
                    }

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
                    strcpy(str,s.substr(0,pos).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos+1);
                    //str = str.substr(0,str.size()-1);
                    logic.push(1);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    for(int i = 0; i < MAX; i++){
                        value[1] = new char[MAX]();
                    }
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
                    strcpy(str,s.substr(0,pos).c_str());
                    //str = s.substr(0,pos);
                    s.erase(0,pos+1);
                    //str = str.substr(0,str.size()-1);
                    logic.push(2);

                    pch = strtok(str, " ");
                    char** value = new char*[MAX];
                    for(int i = 0; i < MAX; i++){
                        value[1] = new char[MAX]();
                    }
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
        void run_logic() {
            bool end_logic = false;
            while (!end_logic) {
                switch(logic.front())
                {
                    // semi
                    case 0:
                        end_logic = true;
                        reset_bool();
                        break;
                    // orrr
                    case 1:
                        if ( bool_val == 1 ) { cmds.pop(); }
                        else if ( bool_val == 0 ) { end_logic = true; } 
                        break;
                    // andd
                    case 2:
                        if ( bool_val == 1) { end_logic = true; }
                        else if ( bool_val == 0 ) { cmds.pop(); }
                        break;
                    default:
                        break;
                }
                logic.pop();
            }
        }

        // helper math funciton that returns the samllest number of 3 numbers
        int smallest(int x, int y, int z) {
            int small;
            vector<int> result;
            if ( x != -1 ) { result.push_back(x); }
            if ( y != -1 ) { result.push_back(y); }
            if ( z != -1 ) { result.push_back(z); }

            // remove all -1

            if (result.empty()) { return -1; }
            else {
                small = result.front();
                for(int i = 0; i < result.size(); ++i) {
                    if ( small > result.at(i) ) { small = result.at(i); }
                }
            }

            return small;
        }

};

#endif
