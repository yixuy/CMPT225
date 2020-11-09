#include"StringSet.h"
#include<iostream>

using namespace std;
// Default constructor
// POST: Creates an String Set object with an array of size 2, current size is 0
StringSet::StringSet(){
    arrSize = 2;
    arr = new string [arrSize];
    curSize = 0;
}
// Destructor
// POST: De-allocates dynamic memory
StringSet::~StringSet(){
    delete []arr;
    arrSize = 2;
    curSize = 0;
}
//copy constructor
//PARAM: set = string set to be copied
StringSet::StringSet(const StringSet & set){
    copyStringSet(set);
}
//Helper method for copy constructor and overload operator
//PRE: 
//POST: copies string set to the calling object
//PARAM: set = string set to be copied
void StringSet::copyStringSet(const StringSet & set){
    arrSize = set.arrSize;
    curSize = set.curSize;
    arr = new string[arrSize];
    for(int i = 0;i < curSize;i++)
        arr[i] = set.arr[i];

}

// Sets the value of the next free element
// PRE:
// POST:  doubles size of arr if arr is full, sets index n to string, increments current size and returns true  
//         else return false  
// PARAM:  a string to be inserted in set    
bool StringSet::insert(string str){
    for(int i=0; i<curSize ;i++)
        if(str.compare(arr[i]) == 0)
            return false;
    if(curSize == arrSize){  
        arrSize = arrSize*2;  
        string* tempArr = new string [arrSize];
        for(int i = 0; i< curSize; i++)
            tempArr[i] = arr[i];
        delete[] arr;
        arr = tempArr;
    }
    // Insert new string at index n and increment n
    arr[curSize++] = str;
    return true;
}

// remove the matched string in the array 
// PRE:
// POST: replaces matching string with the last string in the array, decrements n,return true
//       no matrching return false
// PARAM: matched string to be removed
//    
bool StringSet::remove(string str){
    for(int i=0; i<curSize ;i++)
        if(str.compare(arr[i]) == 0){
            arr[i]=arr[--curSize];
            return true;
        }
    return false;

}
// find the matched string in the array and return the index 
// PRE:
// POST: return the index of matching string in set, no matching return -1
// PARAM: matched string to be found
int StringSet::find(string str) const{
    for(int i=0; i<curSize ;i++)
        if(str.compare(arr[i]) == 0)
            return i;
    return -1;
}
// getter for size of the set 
// POST: return the index of matching string in array, no matching return -1
// PARAM:  
int StringSet::size() const{
    return curSize;
}
// union two sets 
// PRE:
// POST: return a set contains the all the string but not duplicate in both sets
// PARAM: a string set to be unioned
StringSet StringSet::unions(const StringSet & set) const{
    StringSet diffSet=this->difference(set);
    for(int i = 0; i< set.size();i++)
        diffSet.insert(set.arr[i]);
    return diffSet;
}
// intersection two sets
// PRE:
// POST: return a set containing the common element in both sets
// PARAM: a string set to be intersected
StringSet StringSet::intersection(const StringSet & set) const{  
    StringSet tempSet;
    for(int i= 0;i<curSize;i++)
        for (int j = 0; j<set.size() ;j++)
            if(arr[i].compare(set.arr[j]) == 0)
                tempSet.insert(arr[i]);
    return tempSet;
}
// set1(calling object) get difference from set2(parameter)
// PRE:
// POST: return the string set that contains the string in set1 but not s2
// PARAM: string set to be differenced   
StringSet StringSet::difference(const StringSet & set) const{
    StringSet interSet = this->intersection(set);

    StringSet tempSet;
    for(int i=0; i< curSize; i++)
        if(interSet.find(arr[i]) == -1)
            tempSet.insert(arr[i]);
    return tempSet;
}
// overload the equal operator for set
// PRE:
// POST: copies string set to the calling object
// PARAM: set = string set to be copied
StringSet & StringSet::operator= (const StringSet &set){
    if(this != &set){
        delete []arr;
        copyStringSet(set);
    }
    return *this;
}


//printer
// void StringSet::print() const{
//     if(curSize==0){
//         cout<<"Empty set"<<endl;
//         return;
//     }
//     cout<<"The string is {";
//     for (int i=0 ; i<curSize ; i++){
//         cout<<arr[i];
//         if(i != curSize-1)
//             cout<<",";
//     }
//     cout<<"}"<<endl;
//     cout<<"The string size is "<<this->size()<<endl;

//     cout<<"Done"<<endl;
// }