#include "REAgency.h"
#include <algorithm>

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    std::vector<PropertyTypeItem> pType;

    for (const auto& p : properties){
        PropertyTypeItem item(p->getAddress(),p->getPostalCode(),p->getTypology(),p->getPrice());
        auto it = std::find(pType.begin(),pType.end(),item);
        if (it == pType.end()){
            item.addItems(p);
            pType.emplace_back(item);
        }
        else {
            it->addItems(p);
        }
    }

    for (const auto& pt: pType) catalogItems.insert(pt);
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;

	for (BSTItrIn<PropertyTypeItem> it(catalogItems); !it.isAtEnd(); it.advance()){
	    auto item = it.retrieve();
	    if (item == PropertyTypeItem(property->getAddress(),property->getPostalCode(),property->getTypology(),property->getPrice())){
	        for (const auto& p : item.getItems()){
	            if (p->getReservation() == tuple<Client*,int>()){
	                temp.push_back(p);
	            }
	        }
	        break;
	    }
	}

	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {

    for (BSTItrIn<PropertyTypeItem> it(catalogItems); !it.isAtEnd(); it.advance()){
        auto item = it.retrieve();
        if (item == PropertyTypeItem(property->getAddress(),property->getPostalCode(),property->getTypology(),property->getPrice())){
            for (auto& p : item.getItems()){
                if (p->getReservation() == tuple<Client*,int>()){
                    p->setReservation(make_tuple(client,p->getPrice()*(100-percentage)/100));
                    client->addVisiting(property->getAddress(),property->getPostalCode(),property->getTypology(),std::to_string(property->getPrice()));
                    return true;
                }
            }
        }
    }

	return false;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(ClientRecord(client));
}

void REAgency::deleteClients() {
	for (auto it = listingRecords.begin(); it != listingRecords.end(); ){
	    if (it->getClientPointer()->getVisitedProperties().empty()){
	        it = listingRecords.erase(it);
	    }
	    else it++;
	}
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    for (const auto& c : candidates){
        int visited = c.getVisitedProperties().size();
        int reserved = 0;
        for (const auto& p : properties){
            if (std::get<0>(p->getReservation())->getEMail() == c.getEMail()) reserved++;
        }
        if ((double)reserved/(double)visited > (double)min) clientProfiles.push(c);
    }
}

vector<Property*> REAgency::suggestProperties() {
    std::vector<Property*> res;
	priority_queue<Client> tmpC = clientProfiles;
	for (;!tmpC.empty(); tmpC.pop()){
	    Client c = tmpC.top();

	    // count current visit
	    auto visited = c.getVisitedProperties();
	    if (c.getVisiting() != std::tuple<string,string,string,string>()) visited.push_back(c.getVisiting());

	    if (visited.empty()) continue;

	    int lastPropertyCode = std::stoi(std::get<3>(visited.back()));
	    int mostSimilarCodeDiff = 999999999;
	    Property* suggestion;
	    for (const auto& p : properties){
            if (p->getReservation() != tuple<Client*,int>()) continue; // is reserved
            int diff = abs(std::stoi(p->getPostalCode()) - lastPropertyCode);
            if (diff < mostSimilarCodeDiff){
                mostSimilarCodeDiff = diff;
                suggestion = p;
            }
	    }
	    if (suggestion != nullptr) res.push_back(suggestion);
	}
	return res;
}
