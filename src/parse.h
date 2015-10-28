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
        Parse();
        Parse(char*);
        Parse(string);
        ~Parse();

        void parse_input(string);
        bool exit();
        char** get_cmd();
        int connectors();
        void print_vector();
};

#endif
