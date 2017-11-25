//#ifndef __SSTACK_H__
//#define __SSTACK_H__

#pragma once
#include <iostream>

using namespace std;

struct SStack {
public:
    SStack();

    SStack(int max_n);

    ~SStack();

    bool push(int x);

    int pop();

    void get_stack();

private:
    int max_n;
    int a[10];
    int n;
};

//#endif

