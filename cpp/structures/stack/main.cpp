//#include <iostream>
#include "SStack.h"

using namespace std;

int main()
{
    SStack b(10);
    for(int i = 0; i < 15; i++) {
        bool z = b.push(50*i);
        cout << z << endl;
    }
    cout << "-----------------" << endl;

    b.get_stack();

    cout << "-----------------" << endl;

    int g = b.pop();
    cout << g << endl;

    g = b.pop();
    cout << g << endl;

    g = b.pop();
    cout << g << endl;

    cout << "-----------------" << endl;

    b.get_stack();


    return 0;
}