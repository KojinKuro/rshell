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
        vector<char*> user_in;  // Stores the seperate words entered by the user
        vector<int> logic;      // Stores the logic for the user_input
                                // 0: ; 1: || 2: &&


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
              cout << "PARSE_INPUT\n";
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
              cout << "DONE PARSE_INPUT\n";
 
            //GETS STUCK IN THIS LOOP
     /*       while (s.length() > 0) {
                // set up the variables
                int semi = s.find_first_of(";", 0);
                int orrr = s.find_first_of("||", 0);
                int andd = s.find_first_of("&&", 0);

                int pos = smallest(semi, orrr, andd);

                // this is for sitatuions where nothing can be found
                if(pos == -1) {//probably not working
                    if(s.find_first_not_of(" ") == string::npos) { break; }
                }
                else if (pos == semi) {
                    logic.push_back(0);
                }
                else if (pos == orrr) {
                    logic.push_back(1);
                }
                else if (pos == andd) {
                    logic.push_back(2);
                }
break;*/
                /*  CODE TO USE
                    if(pos == -1)
                    {
                        if(line.find_first_not_of(" ") == string::npos)
                            return q;
                        q.push(line);
                        line = "";
                    }
                    else if(pos == semi)
                    {
                        string linecpy(line);
                        if(!strtok((char*)linecpy.c_str(), ";"))
                        {
                            cout << "Error. not enough arguments." << endl;
                            return q;
                        }
                        s = strtok((char*)line.c_str(), ";");
                        q.push(s);
                        q.push(";");
                        line.erase(0, pos+1);
                    }
                    else if(pos == orr)
                    {
                        string linecpy(line);
                        if(!strtok((char*)linecpy.c_str(), "|"))
                        {
                            cout << "Error. not enough arguments." << endl;
                            return q;
                        }
                        s = strtok((char*)line.c_str(), "|");
                        q.push(s);
                        q.push("||");
                        line.erase(0, pos+2);
                    }
                    else    
                    {
                        string linecpy(line);
                        if(!strtok((char*)linecpy.c_str(), "&"))
                        {
                            cout << "Error. not enough arguments." << endl;
                            return q;
                        }
                        s = strtok((char*)line.c_str(), "&");
                        q.push(s);
                        q.push("&&");
                        line.erase(0, pos+2);
                    } */
        /*    }
              cout << "END WHILE2\n"; */
        }
        void parse_clear() { user_in.clear(); }
        bool exit() {
            char* e = (char*)"exit";
              cout << "exit_\n";
            //return (strcmp("here", e) == 0);
              cout << user_in.size() << endl;
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
        void connectors() {
        // int connectors() {
            int total = 0;
            char* a = (char*)"&&";
            char* o = (char*)"||";
            char* e = (char*)";";
            
            for (int x = 0, max = user_in.size(); x < max; x++) {
                if (strcmp(a, user_in[x]) == 0 || 
                    strcmp(o, user_in[x]) == 0 || 
                    strcmp(e, user_in[x]) == 0) {
                    total++;
                }
            }

            cout << total << endl;
            // return total;
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

        }

        // helper math funciton that returns the samllest number of 3 numbers
        int smallest(int x, int y, int z) {
            int result = x;
            if (y < result) { result = y; }
            if (z < result) { result = z; }
            return result;
        }

};

#endif
