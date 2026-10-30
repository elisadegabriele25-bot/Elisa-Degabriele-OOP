#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>

using namespace std;

class Item {
    public:
    Item(const string& n, double p);
    virtual ~Item();

    virtual void displayInfo() const;
    virtual void persist(ofstream& out) const = 0;

    protected:
    string name;
    double price;
};

# endif // ITEM_H

