#include <iostream>
#include "StrBlob.h"
#include "UniqueStrBlob.h"
using namespace std;

int main(void)
{
    UniqueStrBlob b1 = {"she", "he", "it"};
    UniqueStrBlob b2 = {"a", "an", "the"};

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;

   // b1 = b2;
    b2.push_back("about");

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;

    return 0;
}
