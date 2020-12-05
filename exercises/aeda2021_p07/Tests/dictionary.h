#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
    string word;
    string meaning;
public:
    WordMeaning(string w, string m): word(w), meaning(m) {}
    string getWord() const { return word; }
    string getMeaning() const { return meaning; }
    void setWord(string w) {word=w; }
    void setMeaning(string m) { meaning=m; }
    bool operator < (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(const string& word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


class WordInexistent
{
public:
    WordInexistent(WordMeaning  before, WordMeaning  after)
    : _before(std::move(before)), _after(std::move(after)) {};

    string getWordBefore() const { return _before.getWord();}
    string getMeaningBefore() const { return _before.getMeaning(); }
    string getWordAfter() const { return _after.getWord(); }
    string getMeaningAfter() const { return _after.getMeaning(); }
private:
    WordMeaning _before;
    WordMeaning _after;
};

#endif