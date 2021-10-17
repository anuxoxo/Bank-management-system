#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        cout << rand() % 10000 + 1000 << endl;
    }

    return 0;
}