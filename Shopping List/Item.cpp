#include "Item.h"
#include <iostream>
#include <fstream>

using namespace std;

Item::Item(const string& n, double p) : name(n), price(p) {}

Item::~Item() {}

void Item::displayInfo() const {
    cout << "Name: " << name << ", Price: " << price;
}
