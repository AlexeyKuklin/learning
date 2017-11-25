#include "SStack.h"

SStack::SStack() {
    n = 0;
    max_n = 10;
    cout << "Constructor11" << endl;
}

SStack::SStack(int max_n) {
    n = 0;
    this->max_n = max_n;
    cout << "Constructor22" << endl;
}

SStack::~SStack() {
    cout << "Destructor" << endl;
}

bool SStack::push(int x)
{
    if(n < max_n) {
        n++;
        a[n-1] = x;
        return true;
    } else {
        return false;
    }
}

int SStack::pop() {
    if(n > 0)
    {
        n--;
        return a[n];
    }
    else {
        return -1;
    }
}

void SStack::get_stack(){
    for(int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
}
