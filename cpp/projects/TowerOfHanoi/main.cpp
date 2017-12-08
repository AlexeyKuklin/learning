#include <iostream>

void move(int n, char a, char b, char c) {
    if (n <= 0) return;
    move(n - 1, a, c, b);
    cout << "disc " << n << " " << a << " -> " << b << endl;
    move(n - 1, c, b, a);
}

int main(int argc, char** argv)
{
    move(4, 'a', 'b', 'c');
    return 0;
}
