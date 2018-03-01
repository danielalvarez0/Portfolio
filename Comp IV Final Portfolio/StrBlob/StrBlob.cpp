#include <iostream>
#include "StrBlob.h"

using namespace std;


// StrBlob constructors

StrBlob::StrBlob(): data(make_shared<vector<string>>()) { }

StrBlob::StrBlob(initializer_list<string> il):
    data(make_shared<vector<string>>(il)) { }


// StrBlob element access member functions

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
    
string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

ostream& operator<< (ostream& os, const StrBlob& s)
{
    vector<string> v = *s.data;

    os << "<";

    for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
	os << " " << *it;

    os << " >";

    return os;
}
