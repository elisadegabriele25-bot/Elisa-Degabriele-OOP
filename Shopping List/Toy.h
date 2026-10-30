#ifndef BOOK_H
#define BOOK_H

#include "Item.h"
#include <fstream>

class Toy : public Item {
    public:
    Toy(const string& n, double p, int tId, string category);
    ~Toy() override = default;

    void displayToyInfo() const;
    void persist(ofstream& out) const override;

    private:
    int toyId;
    string toyCategory;
};

#endif //TOY_H