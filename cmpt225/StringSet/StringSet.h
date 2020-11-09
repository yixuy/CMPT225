#include<string>
#pragma once

using namespace std;

class StringSet{
    private:
        string* arr;
        int arrSize;
        int curSize;

    public:
        //constructor and destructor 
        //default constructor
        StringSet();

        //copy constructor
        StringSet(const StringSet & set);
        //destructor 
        ~StringSet();

        //mutator
        bool insert(string str);
        bool remove(string str);
        StringSet unions(const StringSet & set) const;
        StringSet intersection(const StringSet & set) const;
        StringSet difference(const StringSet & set)const;
        //helper
        void copyStringSet (const StringSet & set);

        //accessor
        int size() const;
        int find(string str) const;

        //overload operator
        StringSet & operator= (const StringSet &set);
        //printer
        // void print() const;

};
