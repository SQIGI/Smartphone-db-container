#include "SmartphoneList.h"

void SmartphoneList::addSmartphone(const Smartphone& smartphone) {
    smartphones.push_back(smartphone);
}

bool SmartphoneList::removeSmartphone(int index) {
    if (index >= 0 && index < static_cast<int>(smartphones.size())) {
        smartphones.erase(smartphones.begin() + index);
        return true;
    }
    return false;
}

bool SmartphoneList::editSmartphone(int index, const Smartphone& newSmartphone) {
    if (index >= 0 && index < static_cast<int>(smartphones.size())) {
        smartphones[index] = newSmartphone;
        return true;
    }
    return false;
}

Smartphone* SmartphoneList::getSmartphone(int index) const {
    if (index >= 0 && index < static_cast<int>(smartphones.size())) {
        return const_cast<Smartphone*>(&smartphones[index]);
    }
    return nullptr;
}

int SmartphoneList::size() const {
    return static_cast<int>(smartphones.size());
}

void SmartphoneList::clear() {
    smartphones.clear();
}
