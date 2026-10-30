#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
    public:
    Item(const string& n, double p);
    virtual ~Item();

    virtual void displayInfo() const;

    protected:
    string name;
    double price;
};

# endif // ITEM_H

