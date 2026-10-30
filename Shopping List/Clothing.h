#ifndef CLOTHING_H
#define CLOTHING_H

#include "Item.h"
#include <fstream>

class Clothing : public Item {
    public:
    Clothing(const string& n, double p, int cId, string size);
    ~Clothing() override = default;

    void displayClothingInfo() const;
    void persist(ofstream& out) const override;

    private:
    int clothingId;
    string clothingSize;
};

#endif //CLOTHING_H