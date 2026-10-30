#ifndef BOOK_H
#define BOOK_H

#include "Item.h"
#include <fstream>

class Book : public Item {
    public:
    Book(const string& n, double p, int bId, string genre);
    ~Book() override = default;

    void displayBookInfo() const;
    void persist(ofstream& out) const override;

    private:
    int bookId;
    string bookGenre;
};

#endif //BOOK_H