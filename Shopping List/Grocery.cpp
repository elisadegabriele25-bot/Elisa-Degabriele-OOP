#include "Grocery.h"
#include <iostream>
#include <fstream>

using namespace std;

Grocery::Grocery(const string& n, double p, int id, double weight)
    : Item(n, p), groceryId(id), groceryWeight(weight) {}

void Grocery::displayGroceryInfo() const {
    cout <<"Grocery Info: ";
    displayInfo();
    cout << "Grocery ID: " << groceryId << ", Weight: "
    << groceryWeight << endl;
}

void Grocery::persist(ofstream& out) const {
    out << "Grocery" << "|"
        << name << "|"
        << price << "|"
        << groceryId << "|"
        << groceryWeight << endl;
}