#include "Toy.h"
#include <iostream>

using namespace std;

Toy::Toy(const string& n, double p, int tId, string category)
    : Item(n, p), toyId(tId), toyCategory(category) {}

void Toy::displayToyInfo() const {
    cout <<"Toy Info: ";
    displayInfo();
    cout << "Toy ID: " << toyId << ", Category: "
    << toyCategory << endl;
}