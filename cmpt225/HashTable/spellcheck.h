#pragma once 
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<iterator>
#include<stdexcept>
#include"HashTable.h"
using namespace std;

// Opens a file and reads the contents into a vector
// PARAM: infile = name of the file to be opened
// PRE: the file contains words separated by white space 
// POST: returns a vector containing the contents of infile vector<string> readFile(string infile)
vector<string> readFile(string infile){
    ifstream ist(infile.c_str()); 
    if (ist.fail())
        throw runtime_error(infile + " not found"); 
    istream_iterator<string> start(ist), end; 
    vector<string> result(start, end);
    ist.close(); 
    return result;
}
char getAlpha (int i){
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                        'n','o','p','q','r','s','t','u','v','w','x','y','z'};
    return (alphabet[i]);
}
// Extra Letter
// PARAM: ht contains the dictionary and word is a string composed solely of lower-case letters.
// PRE: 
// POST: return a empty vector of string if word is not in ht 
//      returns all strings in ht that can be made  by deleting a single letter from word
vector<string>  extraLetter(const HashTable & ht, string word){
    vector<string> v;
    if(ht.find(word)){
        v.push_back(word);
        return v;
    }
    for(int i = 0; i < word.length() ; i++){
        string temp = word;
        temp.replace(i, 1, "");
        if(ht.find(temp)){
            v.push_back(temp);
        }
    }
    return v;
}
// transposition 
// PARAM: ht contains the dictionary and word is a string composed solely of lower-case letters.
// PRE: 
// POST: if word is not in ht,
//       returns all strings in ht that can be made swapping any two neighbouring letters in word

vector<string>  transposition(const HashTable & ht, string word){
    vector<string> v;
    if(ht.find(word)){
        v.push_back(word);
        return v;
    }
    for(int i = 0; i < word.length()-1 ; i++){
        string temp = word;
        swap(temp[i], temp[i+1]);
        if(ht.find(temp))
            v.push_back(temp);
    }
    return v;
}
//  missingSpace 
// PARAM: ht contains the dictionary and word is a string composed solely of lower-case letters.
// PRE: 
// POST:if word is not in ht,
//      returns all pairs of strings in ht that can be made by inserting a single space in word;
//       each string in the result should consist of the two words from ht separated by a space

vector<string> missingSpace(const HashTable & ht, string word){
    vector<string> v;
    if(ht.find(word)){
        v.push_back(word);
        return v;
    }
    for(int i = 1; i < word.length()-1 ; i++){
        string temp = word;
        int length = word.length();
        string delimiter = " ";

        temp.insert(i, delimiter);
        if(ht.find(temp.substr(0, i)) && ht.find(temp.substr(i+1, length)))
            v.push_back(temp);
    }
    return v;
}
// missingLetter 
// PARAM: ht contains the dictionary and word is a string composed solely of lower-case letters.
// PRE: 
// POST:if word is not in ht 
//      returns all strings in ht that can be made 
//      by inserting any single letter of the alphabet at any position in word

vector<string> missingLetter(const HashTable & ht, string word){
    vector<string> v;
    if(ht.find(word)){
        v.push_back(word);
        return v;
    }
    for(int i = 0; i <= word.length(); i++){
        for(int j = 0 ; j < 26; j++){
            string temp = word;
            temp.insert(i, 1, getAlpha(j));
            if(ht.find(temp))
                v.push_back(temp);
        }
    }
    return v;
}
// incorrectLetter 
// PARAM: ht contains the dictionary and word is a string composed solely of lower-case letters.
// PRE: 
// POST: if word is not in ht 
//       returns all strings in ht that can be made 
//       by changing any single letter of word to a different letter in the alphabet
vector<string> incorrectLetter(const HashTable & ht, string word){
    vector<string> v;
    if(ht.find(word)){
        v.push_back(word);
        return v;
    }
    for(int i = 0; i < word.length(); i++){
        for(int j = 0 ; j < 26; j++){ 
            string temp = word;
            temp[i] = getAlpha(j);
            if(ht.find(temp))
                v.push_back(temp);
        }
    }
    return v;
}
