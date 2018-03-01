#include <iostream>
#include "StrBlob.h"

using namespace std;

int main(void)
{
    StrBlob b1 = {"she", "he", "it"};
    StrBlob b2 = {"a", "an", "the"};

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;

    b1 = b2;
    b2.push_back("about");

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;

    return 0;
}
