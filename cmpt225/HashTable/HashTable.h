#pragma once
#include<iostream>
#include<string>
using namespace std;

class HashTable {
    private:
        /* data */
        string* hashTable;
        int tableSize;
        int secondHashValue;
        int curSize;
        // generate a prime number
        bool checkPrime(int n);
        int getPrime(int n);
    public:
        // default constructor
        HashTable();
        // constructor
        HashTable(int tableSize);
        // copy constructor
        HashTable(const HashTable& hash);
        // destructor
         ~HashTable();
        //overloads  the  assignment  operator  for HashTable objects
        HashTable& operator=(const HashTable& hash);
        //searches the hash table for the method's string parameter and insert
        void insert(string s);
        //find if its string parameteris in the hash table
        bool find(string s) const;
        //returns the number of items stored in the hash table
        int size() const;
        //returns the size of the hash table’s underlying array
        int maxSize() const;
        // returns the load factor of the hash table
        double loadFactor() const;
        // helper function
        void copyHash( const HashTable& table);
        int getSecondHashPrime();
        // hash function
        int firstHash(string s) const;
        int secondHash(string s) const ;
};