#include "Clothing.h"
#include <iostream>
#include <fstream>

using namespace std;

Clothing::Clothing(const string& n, double p, int cId, string size)
    : Item(n, p), clothingId(cId), clothingSize(size) {}

void Clothing::displayClothingInfo() const {
    cout <<"Clothing Info: ";
    displayInfo();
    cout << "Clothing ID: " << clothingId << ", Size: "
    << clothingSize << endl;
}

void Clothing::persist(ofstream& out) const {
    out << "Clothing" << "|"
        << name << "|"
        << price << "|"
        << clothingId << "|"
        << clothingSize << endl;
}