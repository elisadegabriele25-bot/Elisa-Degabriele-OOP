#ifndef BOOK_H
#define BOOK_H

#include "Item.h"

class Toy : public Item {
    public:
    Toy(const string& n, double p, int tId, string category);
    ~Toy() override = default;

    void displayToyInfo() const;

    private:
    int toyId;
    string toyCategory;
};

#endif //TOY_H