#ifndef GROCERY_H
#define GROCERY_H

#include "Item.h"

class Grocery : public Item {
    public:
    Grocery(const string& n, double p, int id, double weight);
    ~Grocery() override = default;

    void displayGroceryInfo() const;

    private:
    int groceryId;
    double groceryWeight;
};

#endif //GROCERY_H