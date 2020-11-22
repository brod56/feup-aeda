#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return true;
}

//TODO
void Dictionary::readDictionary(ifstream &f)
{
     return;
}

//TODO
string Dictionary::searchFor(string word) const
{
    return "";
}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    return true;
}

//TODO
void Dictionary::print() const
{
    return;
}

