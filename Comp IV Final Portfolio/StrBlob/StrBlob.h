#ifndef STRBLOB_H
#define STRBLOB_H

#include <memory>
#include <string>
#include <initializer_list>
#include <vector>

class StrBlob
{
    public:
        typedef std::vector<std::string>::size_type size_type;

	    StrBlob();
	    StrBlob(std::initializer_list<std::string> il);

        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        // add and remove elements    
        void push_back(const std::string &t) {data->push_back(t);}
        void pop_back();

        // element access
        std::string& front();
        std::string& back();

	    friend std::ostream& operator<< (std::ostream& os, const StrBlob& s);

    private:
        std::shared_ptr<std::vector<std::string>> data;

        // throws msg if data[i] isn't valid
        void check(size_type i, const std::string &msg) const;
};

#endif
