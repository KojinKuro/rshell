#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    bool boop = true;
    string value;
    while (boop)
    {
        cout << "$ ";
        cin >> value;
        if (value == "quit")
            boop = false;
    }
    return 0;
}