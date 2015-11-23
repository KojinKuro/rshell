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
    char* str;      //The string entered by the user
    queue<bool> is_in_parr;      // If we are in parentheses or not
    queue<int> num_commands;     // Number of commands in each grouping, either in parentheses or out
    queue<vector<char*> > cmds; // The final commands that are going to used
    char* command[MAX]; // WHAT IS BEING SENT
    vector<int> quoteHolder; // HANDLES QUOTATIONS
public:
    queue<int> logic;   // Stores the logic for the user_input
                        // 0: ; 1: || 2: &&
    int bool_val; // Fake "bool" to control logic
    

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
    
    void parse_input(string s, bool is_parr) {
        is_in_parr.push(is_parr);
        int number_commands = 0;
        // inputs all the quotes into hanlder and gets ready
        int tempNumber = -1; quoteHolder.clear();
        do {
            tempNumber = s.find_first_of("\"", tempNumber+1);
            if(tempNumber != -1)
                quoteHolder.push_back(tempNumber);
        } while(tempNumber != -1);
        // cleans up if excess qutoes ex: 3 instead of 2
        if(quoteHolder.size() % 2 != 0) {
            s.erase(quoteHolder.back(),1);
            quoteHolder.pop_back(); } 

        // removes comments out of the code
        int comm = s.find_first_of("#", 0);
        for(unsigned i=0; i < quoteHolder.size()/2; ++i) {
            if(quoteHolder.at(i*2) < comm && comm < quoteHolder.at(i*2+1)) {
                comm = s.find_first_of("#", quoteHolder.at(i*2+1)+1);
            }
        } if(comm != -1){ s.erase(comm, s.size()-1); }

        while (s.size()) {
            vector<char*> user_in;
            char* str_cpy = new char[MAX];
            strcpy(str_cpy, s.c_str());

            // set up the variables
            //cout << s << endl;
            int semi = s.find_first_of(";", 0);
            int orrr = s.find_first_of("||", 0);
            int andd = s.find_first_of("&&", 0);
            int parr = s.find_first_of("(", 0);

            // makes sure the position isn't in quotations
            for(unsigned i=0; i < quoteHolder.size()/2; ++i) {
                if(quoteHolder.at(i*2) < semi && semi < quoteHolder.at(i*2+1)) {
                    semi = s.find_first_of(";", quoteHolder.at(i*2+1)+1);
                }
            }
            for(unsigned i=0; i < quoteHolder.size()/2; ++i) {
                if(quoteHolder.at(i*2) < orrr && orrr < quoteHolder.at(i*2+1)) {
                    orrr = s.find_first_of("||", quoteHolder.at(i*2+1)+1);
                }
            }
            for(unsigned i=0; i < quoteHolder.size()/2; ++i) {
                if(quoteHolder.at(i*2) < andd && andd < quoteHolder.at(i*2+1)) {
                    andd = s.find_first_of("&&", quoteHolder.at(i*2+1)+1);
                }
            }
             for(unsigned i=0; i < quoteHolder.size()/2; ++i) {
                if(quoteHolder.at(i*2) < andd && andd < quoteHolder.at(i*2+1)) {
                    parr = s.find_first_of("(", quoteHolder.at(i*2+1)+1);
                }
            }
            // high unefficent optimize later;
            
            //cout << semi << " " << orrr << " " << andd << " " << parr << endl;
            int pos = smallest(semi, orrr, andd);
            if(parr < pos && parr != -1){
                pos = parr;
            }
            //cout << pos << "\n";
            
            //break;
            
            // this is for sitatuions where nothing can be found
            if(pos == -1) {// needs to be fixed for base case
                strcpy(str_cpy, s.c_str());
                s.erase(0,s.size());
                
                // gets rid of quotes from final code
                for(int i=0; i < MAX; ++i)
                {
                    if(str_cpy[i] =='\"') {
                        int j = i;
                        for(; j < MAX-1; ++j) {
                            str_cpy[j] = str_cpy[j+1];
                        } str_cpy[j] = '\0';
                    }
                }
                
                char* pch;
                pch = strtok(str_cpy, " ");
                if ( !is_parr ) {
                    logic.push(0); // controls logic
                }
                //number_commands ++;
                while (pch != NULL) {
                    user_in.push_back(pch);
                    pch = strtok(NULL, " ");
                }
                user_in.push_back(NULL);
                cmds.push(user_in);
                break;
            }
            else if (pos == parr) {
               num_commands.push(number_commands);
               //cout << "GOT INTO ELSE IF" << endl;
               int closingParr = s.find_first_of(")", 0);  //needs a for loop for nested parithesies
               //cout << "closing parr found " << closingParr << endl;
               string subs = s.substr(pos + 1, closingParr - pos - 1);
               //cout << "created string subs " << subs << endl;
               s.erase(pos, closingParr + 1);
               //cout << " erased: " << s << endl;
               parse_input(subs, true);
               //cout << "parsed input" << endl;
            }
            else if (pos == semi) {
                strcpy(str_cpy,s.substr(0,pos).c_str());
                s.erase(0,pos+1);
                
                // gets rid of quotes from final code
                for(int i=0; i < MAX; ++i)
                {
                    if(str_cpy[i] == '\"') {
                        int j = i;
                        for(; j < MAX-1; ++j) {
                            str_cpy[j] = str_cpy[j+1];
                        } str_cpy[j] = '\0';
                    }
                }
                
                char* pch;
                pch = strtok(str_cpy, " ");
                logic.push(0); // controls logic
                number_commands ++;
                while (pch != NULL) {
                    user_in.push_back(pch);
                    pch = strtok(NULL, " ");
                }
                user_in.push_back(NULL);
                cmds.push(user_in);
            }
            else if (pos == orrr) {
                strcpy(str_cpy,s.substr(0,pos).c_str());
                s.erase(0,pos+2);
                
                // gets rid of quotes from final code
                for(int i=0; i < MAX; ++i)
                {
                    if(str_cpy[i] == '\"') {
                        int j = i;
                        for(; j < MAX-1; ++j) {
                            str_cpy[j] = str_cpy[j+1];
                        } str_cpy[j] = '\0';
                    }
                }
                
                char* pch;
                pch = strtok(str_cpy, " ");
                //cout << "PCH " << pch << endl;
                logic.push(1); // controls logic
                number_commands ++;
                while (pch != NULL) {
                    user_in.push_back(pch);
                    pch = strtok(NULL, " ");
                }
                user_in.push_back(NULL);
                cmds.push(user_in);
            }
            else if (pos == andd) {
                strcpy(str_cpy,s.substr(0,pos).c_str());
                s.erase(0,pos+2);
                
                // gets rid of quotes from final code
                for(int i=0; i < MAX; ++i)
                {
                    if(str_cpy[i] == '\"') {
                        int j = i;
                        for(; j < MAX-1; ++j) {
                            str_cpy[j] = str_cpy[j+1];
                        } str_cpy[j] = '\0';
                    }
                }
                
                char* pch;
                pch = strtok(str_cpy, " ");
                logic.push(2); // controls logic
                number_commands ++;
                while (pch != NULL) {
                    user_in.push_back(pch);
                    pch = strtok(NULL, " ");
                }
                user_in.push_back(NULL);
                cmds.push(user_in);
            }
        }
        //cout << "NOPE TO BAD\n";
        num_commands.push(number_commands);
    }
    // void parse_clear() { user_in.clear(); }
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
        // sanitizes everything for use
        for(int i=0; i < MAX; ++i) { command[i] = NULL; }
        reset_bool();

        for (unsigned i = 0; i < cmds.front().size() - 1; ++i) {
            command[i] = cmds.front().at(i);
        }
        return command;
    }
    bool cmd_front(){
        return !cmds.empty();
    }
    void run_logic() {
        //cout << cmds.size() << endl;
        cmds.pop();

        bool end_logic = false;
        while (!end_logic) {
            //cout << "beggining of while" << endl;
            //setup for parr
            //cout << num_commands.front() << endl;
            //cout << is_in_parr.front() << endl;

            num_commands.front() -= 1;
            if ( num_commands.front() <= 0) {
                num_commands.pop();
                is_in_parr.pop();
            }
            //cout << num_commands.front() << endl;
            //cout << is_in_parr.front() << endl;
            switch(logic.front()) {
                    // semi
                case 0:
                    //cout << "CASE 0" << endl;
                    end_logic = true; reset_bool();
                    break;
                    // orrr
                case 1:
                    //cout << "CASE 1" << endl;
                    if ( bool_val == 1 ) {
                        if ( is_in_parr.empty() || !is_in_parr.front() ) {
                            cmds.pop();
                        }
                        else if ( !is_in_parr.empty() && is_in_parr.front() ) {
                            for ( int i = 0; i <= num_commands.front(); ++i ) { //if you make sure that cmds has the right size this works, if not it's an error
                                cmds.pop();
                                logic.pop(); //this line may need to be double checked
                            }
                            is_in_parr.pop();
                            num_commands.pop();
                        }
                    }
                    else if ( bool_val == 0 ) { end_logic = true; }
                    else { end_logic = true; reset_bool(); }
                    break;
                    // andd
                case 2:
                    //cout << "CASE 2" << endl;
                    if ( bool_val == 1) {  end_logic = true; reset_bool(); }
                    else if ( bool_val == 0 ) {
                        if ( is_in_parr.empty() || !is_in_parr.front() ) {
                            cmds.pop();
                        }
                        else if ( !is_in_parr.empty() &&  is_in_parr.front() ) {
                            for ( int i = 0; i <= num_commands.front(); i++ ) {
                                cmds.pop();
                                logic.pop(); //only like 90% about this line
                            }
                            is_in_parr.pop();
                            num_commands.pop();
                        }
                    }
                    else { end_logic = true; reset_bool(); }
                    break;
                default:
                    break;
            }
            //cout << "before logic" << endl;
            logic.pop();
            //num_commands.front() -= 1;
            //if ( num_commands.front() <= 0) {
                //num_commands.pop();
                //is_in_parr.pop();
            //}
            //cout << "after logic" << endl;

        }
       //cout << "after loop" << endl;
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
            for(unsigned i = 0; i < result.size(); ++i) {
                if ( small > result.at(i) ) { small = result.at(i); }
            }
        }
        
        return small;
    }
    
};

#endif
