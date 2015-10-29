#ifndef _PARSE_H
#define _PARSE_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>

#define MAX 80

using namespace std;

class Parse {
    protected:
        char* str;
        char* cmd[MAX];
    public:
        vector<char*> user_in;
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
            pch = strtok(str, " ");
            while (pch != NULL) {
                //printf("%s\n", pch);
                user_in.push_back(pch);
                pch = strtok(NULL, " ");
            }
            user_in.push_back(NULL);
        }
        void parse_clear() { user_in.clear(); }
        bool exit()
        {
            char* e = (char*)"exit";
            return (strcmp(user_in.front(), e) == 0);
        }
        char** get_cmd()
        {
            int size = user_in.size();
            for (int i = 0; i < size; i++)
                cmd[i] = user_in[i]; 

            return cmd;
        }
        int connectors()
        {
            int total = 0;
            char* a = (char*)"&&";
            char* o = (char*)"||";
            char* e = (char*)";";

            for (int i = 0, max = user_in.size(); i < max; i++) {
                if (strcmp(a, user_in[i]) == 0 || 
                    strcmp(o, user_in[i]) == 0 || 
                    strcmp(e, user_in[i]) == 0) {
                    total++;
                }
            }
            return total;
        }
        void print_vector()
        {
            // for (int i = 0, max = user_in.size(); i < max; i++) {
            for (vector<char*>::iterator it = user_in.begin(), end = user_in.end(); it != end; it++) {
                // printf("%s\n", user_in[i]);
                printf("%s\n", *it);
            }
        }
};

#endif
