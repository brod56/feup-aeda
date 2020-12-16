#include "Gallery.h"
#include <ostream>
#include <algorithm>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

vector<Paint*> Gallery::getPaintsBy(string a) const {
    std::vector<Paint*> res;
    for (BSTItrIn<PaintCatalogItem> it(catalog); !it.isAtEnd(); it.advance()){
        if (it.retrieve().getAuthor() == a) res.push_back(it.retrieve().getPaint());
    }
    return res;
}

vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    for (BSTItrIn<PaintCatalogItem> it(catalog); !it.isAtEnd(); it.advance()){
        if (it.retrieve().getYear() >= y1 && it.retrieve().getYear() <= y2) tmp.push_back(it.retrieve().getPaint());
    }
    return tmp;
}

bool Gallery::updateTitle(Paint* p, string tnew) {
    if (!catalog.remove(PaintCatalogItem(p))) return false;
    catalog.insert(PaintCatalogItem(p->getAuthor(),tnew,p->getYear(),p->getPrice()));
    return true;
}

int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    int counter = 0;
    for (const auto& p: collection){
        if (authorRecords.insert(AuthorRecord(p->getAuthor(),std::count_if(collection.begin(),collection.end(),[p](const Paint* p1){
            return p1->getAuthor() == p->getAuthor();
        }),0)).second) counter++;
    }
    return counter;
}

double Gallery::totalSells() const {
    return 0.0;
}

double Gallery::sellPaint(string a, string t) {
    auto p = std::find_if(collection.begin(),collection.end(),[a,t](Paint* p){
        return p->getAuthor() == a && p->getTitle() == t;
    });
    if (p == collection.end()) return 0.0;
    collection.erase(p);
    auto record = *authorRecords.find(AuthorRecord(a,0,0));
    authorRecords.erase(record);
    authorRecords.insert(AuthorRecord(a,record.getAvailablePaints()-1,record.getTotalSells()+(*p)->getPrice()));
    return (*p)->getPrice();
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    return 0;
}

