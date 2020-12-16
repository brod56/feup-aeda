#include "packagingMachine.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    unsigned loaded = 0;
    std::vector<Object> notLoaded;
	for (const auto& o : objs){
	    if (o.getWeight() > boxCapacity) {
	        notLoaded.push_back(o);
	        continue;
	    }
	    objects.push(o);
	    loaded++;
	}
	objs = notLoaded;
	return loaded;
}

Box PackagingMachine::searchBox(Object& obj) {
    HeapBox nHeap;
    Box res;
    for (bool remove = true; !boxes.empty(); ){
        Box box = boxes.top();
        std::cout << box.printContent() << "\n";
        boxes.pop();
        if (remove && box.getFree() >= obj.getWeight()){
            res = box;
            remove = false;
        }
        else nHeap.push(box);
    }

    boxes = nHeap;
    return res;
}

unsigned PackagingMachine::packObjects() {

	unsigned used = 0;
    HeapObj hObj = objects;
    std::vector<Box> vecBoxes;

    while (!hObj.empty()){
        Object o = hObj.top();
        hObj.pop();

        bool used_existing = false;
        for (auto& b: vecBoxes){
            if (b.getFree() >= o.getWeight()){
                used_existing = true;
                b.addObject(o);
                break;
            }
        }
        if (!used_existing){
            used++;
            vecBoxes.emplace_back(boxCapacity);
            vecBoxes.back().addObject(o);
        }
    }

    HeapBox boxQueue;
    for (const auto& b: vecBoxes){
        boxQueue.push(b);
    }

    boxes = boxQueue;
    objects = HeapObj();
    return used;
}

string PackagingMachine::printObjectsNotPacked() const {
	if (objects.empty()) return "No objects!\n";
	HeapObj hObj = objects;

	std::stringstream ss;
	while (!hObj.empty()){
	    Object o = hObj.top();
	    ss << std::right << std::setw(2) << std::setfill('O') << o.getID() << ":" << o.getWeight() << '\n';
	    hObj.pop();
	}
	return ss.str();
}

Box PackagingMachine::boxWithMoreObjects() const {
    if (boxes.empty()) throw MachineWithoutBoxes();
    HeapBox hBox = boxes;

    unsigned max = 0;
    Box maxBox;
    while (!hBox.empty()){
        if (hBox.top().getSize() > max) maxBox = hBox.top();
        hBox.pop();
    }
    return maxBox;
}