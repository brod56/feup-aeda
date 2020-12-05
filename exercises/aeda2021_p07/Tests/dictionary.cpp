#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return getWord() < wm1.getWord();
}

void Dictionary::readDictionary(ifstream &f)
{
    bool readWord = true;
    std::string word;
    for (std::string line; std::getline(f,line);){
        if (readWord){
            word = line;
            readWord = false;
        }
        else {
            words.insert(WordMeaning(word,line));
            readWord = true;
        }
    }
}

string Dictionary::searchFor(const string& word) const
{
    for (auto it = BSTItrIn<WordMeaning>(words); !it.isAtEnd(); it.advance()){
        if (it.retrieve().getWord() == word) return it.retrieve().getMeaning();

        auto afterIt = it;
        afterIt.advance();

        if (afterIt.isAtEnd()) throw WordInexistent(it.retrieve(),it.retrieve());
        if (afterIt.retrieve().getWord() > word) throw WordInexistent(it.retrieve(),afterIt.retrieve());
        else if (afterIt.retrieve().getWord() < word){
            auto afterAfterIt = afterIt;
            afterAfterIt.advance();
            if (afterAfterIt.isAtEnd()) throw WordInexistent(afterIt.retrieve(),afterIt.retrieve());
        }
    }
    return "Tree malfunction"; // should not reach this
}


bool Dictionary::correct(string word, string newMeaning)
{
    for (auto it = BSTItrIn<WordMeaning>(words); !it.isAtEnd(); it.advance()){
        if (it.retrieve().getWord() == word){
            WordMeaning wm = it.retrieve();
            words.remove(wm);
            wm.setMeaning(newMeaning);
            words.insert(wm);
            return true;
        }
    }
    words.insert(WordMeaning(word,newMeaning));
    return false;
}

void Dictionary::print() const
{
    for (auto it = BSTItrIn<WordMeaning>(words); !it.isAtEnd(); it.advance()){
        WordMeaning wm = it.retrieve();
        std::cout << wm.getWord() << "\n" << wm.getMeaning() << "\n";
    }
}

