#include "Toy.h"
#include <iostream>
#include <fstream>

using namespace std;

Toy::Toy(const string& n, double p, int tId, string category)
    : Item(n, p), toyId(tId), toyCategory(category) {}

void Toy::displayToyInfo() const {
    cout <<"Toy Info: ";
    displayInfo();
    cout << "Toy ID: " << toyId << ", Category: "
    << toyCategory << endl;
}


void Toy::persist(ofstream& out) const {
    out << "Toy" << "|"
        << name << "|"
        << price << "|"
        << toyId << "|"
        << toyCategory << endl;
}