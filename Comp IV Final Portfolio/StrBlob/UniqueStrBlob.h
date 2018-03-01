#ifndef UNIQUEStrBlob_H
#define UNIQUEStrBlob_H

#include <memory>
#include <string>
#include <initializer_list>
#include <vector>
#include "StrBlob.h"

class UniqueStrBlob
{
    public:
        typedef std::vector<std::string>::size_type size_type;

	    UniqueStrBlob();
	    UniqueStrBlob(std::initializer_list<std::string> il);

        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }

		StrBlob makeSharedBlob();

        // add and remove elements    
        void push_back(const std::string &t) {data->push_back(t);}
        void pop_back();

        // element access
        std::string& front() const;
        std::string& back() const;
		friend UniqueStrBlob operator+ (UniqueStrBlob& lhs, const UniqueStrBlob& rhs);
	    friend std::ostream& operator<< (std::ostream& os, const UniqueStrBlob& s);

    private:
        std::unique_ptr<std::vector<std::string>> data;

        // throws msg if data[i] isn't valid
        void check(size_type i, const std::string &msg) const;
};

#endif
