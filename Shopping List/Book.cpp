#include "Book.h"
#include <iostream>

using namespace std;

Book::Book(const string& n, double p, int bId, string genre)
    : Item(n, p), bookId(bId), bookGenre(genre) {}

void Book::displayBookInfo() const {
    cout <<"Book Info: ";
    displayInfo();
    cout << "Book ID: " << bookId << ", Genre: "
    << bookGenre << endl;
}