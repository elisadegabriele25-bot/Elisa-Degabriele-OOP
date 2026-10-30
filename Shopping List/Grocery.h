#ifndef GROCERY_H
#define GROCERY_H

#include "Item.h"
#include <fstream>

class Grocery : public Item {
    public:
    Grocery(const string& n, double p, int id, double weight);
    ~Grocery() override = default;

    void displayGroceryInfo() const;
    void persist(ofstream& out) const override;

    private:
    int groceryId;
    double groceryWeight;
};

#endif //GROCERY_H