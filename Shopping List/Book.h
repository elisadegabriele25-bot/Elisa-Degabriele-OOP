#ifndef BOOK_H
#define BOOK_H

#include "Item.h"

class Book : public Item {
    public:
    Book(const string& n, double p, int bId, string genre);
    ~Book() override = default;

    void displayBookInfo() const;

    private:
    int bookId;
    string bookGenre;
};

#endif //BOOK_H