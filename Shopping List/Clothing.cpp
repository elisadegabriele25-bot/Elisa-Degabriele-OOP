#include "Clothing.h"
#include <iostream>

using namespace std;

Clothing::Clothing(const string& n, double p, int cId, string size)
    : Item(n, p), clothingId(cId), clothingSize(size) {}

void Clothing::displayClothingInfo() const {
    cout <<"Clothing Info: ";
    displayInfo();
    cout << "Clothing ID: " << clothingId << ", Size: "
    << clothingSize << endl;
}