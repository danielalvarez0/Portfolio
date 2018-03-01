#include <iostream>
#include "UniqueStrBlob.h"

using namespace std;


// UniqueStrBlob constructors

UniqueStrBlob::UniqueStrBlob(): data(make_unique<vector<string>>()) { }

UniqueStrBlob::UniqueStrBlob(initializer_list<string> il):
    data(make_unique<vector<string>>(il)) { }


// transfer control to a new shared_pointer and set unique pointer to null.
StrBlob UniqueStrBlob::makeSharedBlob() {
	StrBlob tempnewBlob;
	StrBlob newShared;
	int length = data->size();
	// transfers data but reverses order
	for (int x = 0; x < length; ++x) {
		string  tempNewElement = back();
		tempnewBlob.push_back(tempNewElement);
		data->pop_back();
	}
	// repeat transfer to StrBlob that will be returned to fix the order
	for (int y = 0; y < length; ++y) {
		string  newElement = tempnewBlob.back();
		newShared.push_back(newElement);
		tempnewBlob.pop_back();
	}
	data.release();
	return newShared;
};



// UniqueStrBlob element access member functions

void UniqueStrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}
    
string& UniqueStrBlob::front() const
{
    // if the vector is empty, check will throw
    check(0, "front on empty UniqueStrBlob");
    return data->front();
}

string& UniqueStrBlob::back() const
{
    check(0, "back on empty UniqueStrBlob");
    return data->back();
}

void UniqueStrBlob::pop_back()
{
    check(0, "pop_back on empty UniqueStrBlob");
    data->pop_back();
}

UniqueStrBlob operator+(UniqueStrBlob & lhs, const UniqueStrBlob & rhs)
{
	UniqueStrBlob newLHS;
	// append data from lhs and then rhs to newLHS variable
	copy(rhs.data->begin(), rhs.data->end(), back_inserter(newLHS));
	copy(lhs.data->begin(), lhs.data->end(), back_inserter(newLHS));
	// return newLHS variable
	return newLHS;
}

ostream& operator<< (ostream& os, const UniqueStrBlob& s)
{
    vector<string> v = *s.data;

    os << "<";

    for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
	os << " " << *it;

    os << " >";

    return os;
}
