#include "parse.h"

using namespace std;

Parse::Parse() {
    str = new char[1];
    str[0] = '\0';
}

Parse::Parse(char* s) {
    strcpy(str, s);
}

Parse::Parse(string s) {
    strcpy(str, s.c_str());
}

Parse::~Parse() {
    if (str) {
        delete[] str;
    }
}

void Parse::parse_input(string s) {
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

bool Parse::exit() {
    char* e = (char*)"exit";
    bool result = false;
    if (strcmp(user_in.front(), e) == 0) {
        result = true;
    }
    return result;
}

char** Parse::get_cmd() {
    int size = user_in.size();
    for (int i = 0; i < size; i++) {
        cmd[i] = user_in[i]; 
    }

    return cmd;
}

int Parse::connectors() {
    int total = 0;
    char* a = (char*)"&&";
    char* o = (char*)"||";
    char* e = (char*)";";

    for (int i = 0, max = user_in.size(); i < max; i++) {
        if (strcmp(a, user_in[i]) == 0 || strcmp(o, user_in[i]) == 0 || 
            strcmp(e, user_in[i]) == 0) {
            total++;
        }
    }
    return total;
}

void Parse::print_vector() {
    //for (int i = 0, max = user_in.size(); i < max; i++) {
    for (vector<char*>::iterator it = user_in.begin(), end = user_in.end();
        it != end; it++) {
        //printf("%s\n", user_in[i]);
        printf("%s\n", *it);
    }
}
