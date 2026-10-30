#include "Electronics.h"
#include <iostream>

using namespace std;

Electronics::Electronics(const string& n, double p, int elId, string brand) 
: Item(n, p), elecId(elId), elecBrand(brand) {}

void Electronics::displayElectronicsInfo() const {
    cout <<"Electronics Info: ";
    displayInfo();
    cout << "Electronics ID: " << elecId << ", Brand: "
    << elecBrand << endl;
}

