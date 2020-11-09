#include"HashTable.h"
#include<math.h>
#include<iostream>
// Check prime number 
// PARAM: n is the number need to be checked for prime
// PRE:
// POST: true for prime number, else for false
bool HashTable::checkPrime(int n){
    bool isPrime = true;
    for(int i=2; i<=n/2 ;i++){
        if(n % i == 0){
            isPrime = false;
            break;
        }
    }
    return isPrime;
}
// Get prime number 
// PARAM: an integer n 
// PRE:
// POST: return an integer which is the smallest prime number equal to or greater than n
int HashTable::getPrime(int n){
    bool found =  false;
    while(!found){
        if(checkPrime(n) == true)
            return n;
        n++;
    }
    return n;
}
// Hash function
// PARAM: a key value (string) to be calcuated as index in hash table
// PRE:
// POST: the index for hash table 
int HashTable::firstHash(string s) const{
    int value = 0;
    for(int i = 0; i<s.length();i++){
        value+= (s[i]-96)*pow(32.0, 1.0*(s.length()-1-i));
        value = value %tableSize;
    }
    return value;
}

// Default constructor
// PARAM:
// PRE:
// POST: initialize all the attribute in class as default value
HashTable::HashTable(){
    curSize = 0;
    tableSize = 101;
    hashTable = new string[tableSize];
    for(int i = 0; i<tableSize ;i++){
        hashTable[i] = "";
    }
    secondHashValue = getPrime(tableSize/2);
}
// Constructor
// PARAM: n is the the size of the underlying array 
//        should be the smallest prime number equal to or greater than 2n
// PRE:
// POST: initialize all the attribute in class as n
HashTable::HashTable(int n){
    tableSize = getPrime(2*n);
    hashTable = new string[tableSize];
    secondHashValue = getPrime(tableSize/2);
    curSize = 0;
    for(int i = 0; i<tableSize ;i++)
        hashTable[i] = "";
}
// Copy constructor
// PARAM: a hash table object which is deeply copied
// PRE:
// POST: 
HashTable::HashTable(const HashTable& hash){
    copyHash(hash);
}
// Destructor
// PARAM:
// PRE:
// POST: 
HashTable::~HashTable(){
    curSize = 0;
    tableSize = 0;
    secondHashValue = 0;
    delete []hashTable;
}
        
// Overloads operator =
// PARAM: a hash table  object which is assigened to calling object
// PRE:
// POST: returns a reference hash table to the calling object
HashTable& HashTable::operator=(const HashTable& hash){
    if(this !=  &hash){
        delete []hashTable;
        copyHash(hash);
    }
    return *this;
}
// Insert the string in hashtable
// PARAM: a string will be inserted in the hashtable
// PRE:
// POST: 
void HashTable::insert(string s){
    int indexFirst = firstHash(s);
    int indexSecond = secondHash(s);

    if(!find(s)){
        while(hashTable[indexFirst] != "")
            indexFirst = (indexFirst + indexSecond) % tableSize;
        hashTable[indexFirst]=s;
        curSize++;
    }    

    if(loadFactor() > 0.67){
        HashTable h = HashTable(tableSize);
        for(int i = 0; i < tableSize ;i++)
            if(hashTable[i] != "")
                h.insert(hashTable[i]);
        *this = h;
    }
}
// Find if its string in the hash table
// PARAM: a string s need to be checked 
// PRE:
// POST: return true if s is found in table, else return false
bool HashTable::find(string s) const{
    int indexFirst = firstHash(s);
    int indexSecond = secondHash(s);
    while(hashTable[indexFirst] != "" && hashTable[indexFirst] != s)
        indexFirst = (indexFirst + indexSecond) % tableSize;
    return (hashTable[indexFirst] == s);
}
// the amount of element in hash table
// PARAM:
// PRE:
// POST: return how many element inserted in the hash table
int HashTable::size() const{
    return curSize;
}
// Max Size of hash table
// PARAM:
// PRE:
// POST: Returns the size of the hash table’s underlying array
int HashTable::maxSize() const{
    return tableSize;
}
// Calculate load factor of the hash table
// PARAM:
// PRE:
// POST: Returns the load factor of the hash table
double HashTable::loadFactor() const{
    return (1.0*curSize)/tableSize;
}
// Helper function for constructor deep copy
// PARAM: a hash table object 
// PRE:
// POST:
void HashTable::copyHash( const HashTable& table){
    curSize = table.curSize;
    tableSize =  table.tableSize;
    secondHashValue = table.secondHashValue;
    hashTable =  new string[tableSize];
    for(int i = 0; i<tableSize; i++)
        hashTable[i] = table.hashTable[i];
}
// Helper function for getting double hash prime 
// PARAM: 
// PRE:
// POST: return the number that set for double hash value
int HashTable::getSecondHashPrime(){
    return secondHashValue;
}
// Helper function for double hash
// PARAM: a string to be caclucate double hashing index
// PRE:
// POST: return the index for double hashing
int HashTable::secondHash(string s) const {
    return (secondHashValue - (firstHash(s)%secondHashValue));
}