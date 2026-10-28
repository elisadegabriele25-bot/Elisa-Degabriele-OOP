#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// ---------- Base class ----------

class Item {
protected:
    string name;
    double price;
    int quantity;

public:
    Item(string n, double p, int q)
        : name(n), price(p), quantity(q) {}

    virtual ~Item() {}
    virtual void display() const;

    string getName() const;
    double getPrice() const;
    int getQuantity() const;

    void setName(const string& n);
    void setPrice(double p) const;
    void setQuantity(int q);

};

// ---------- Grocery ----------

class Grocery : public Item {
    string expiry;
    double weight;
    bool organic;

public:
    Grocery(string n, double p, int q, string e, double w, bool o)
        : Item(n, p, q), expiry(e), weight(w), organic(o) {}

    string type() const override { return "Grocery"; }
    char id() const override { return 'G'; }

    void display() const override {
        Item::display();
        cout << "  Expiry: " << expiry << ", Weight: " << weight
             << " kg, Organic: " << yesNo(organic) << '\n';
    }
};

// ---------- Electronics ----------

class Electronics : public Item {
    string brand;
    int warranty;
    double power;

public:
    Electronics(string n, double p, int q, string b, int w, double pw)
        : Item(n, p, q), brand(b), warranty(w), power(pw) {}

    string type() const override { return "Electronics"; }
    char id() const override { return 'E'; }

    void display() const override {
        Item::display();
        cout << "  Brand: " << brand << ", Warranty: " << warranty
             << " months, Power: " << power << " W\n";
    }

};

// ---------- Clothing ----------

class Clothing : public Item {
    string size, material, color;

public:
    Clothing(string n, double p, int q, string s, string m, string c)
        : Item(n, p, q), size(s), material(m), color(c) {}

    string type() const override { return "Clothing"; }
    char id() const override { return 'C'; }

    void display() const override {
        Item::display();
        cout << "  Size: " << size << ", Material: " << material
             << ", Color: " << color << '\n';
    }
};

// ---------- Book ----------

class Book : public Item {
    string author, isbn;
    int pages;

public:
    Book(string n, double p, int q, string a, string i, int pg)
        : Item(n, p, q), author(a), isbn(i), pages(pg) {}

    string type() const override { return "Book"; }
    char id() const override { return 'B'; }

    void display() const override {
        Item::display();
        cout << "  Author: " << author << ", ISBN: " << isbn
             << ", Pages: " << pages << '\n';
    }

    void save(ofstream& out) const override {
        saveCommon(out);
        out << SEP << author << SEP << isbn << SEP << pages << '\n';
    }

    static Item* create() {
        return new Book(
            readString("Title"), readNumber<double>("Price", 0.0),
            readNumber<int>("Quantity", 1), readString("Author"),
            readString("ISBN"), readNumber<int>("Pages", 1));
    }
};

// ---------- Toy ----------

class Toy : public Item {
    string brand;
    int minAge;
    bool batteries;

public:
    Toy(string n, double p, int q, string b, int a, bool bat)
        : Item(n, p, q), brand(b), minAge(a), batteries(bat) {}

    string type() const override { return "Toy"; }
    char id() const override { return 'T'; }

    void display() const override {
        Item::display();
        cout << "  Brand: " << brand << ", Minimum age: " << minAge
             << ", Needs batteries: " << yesNo(batteries) << '\n';
    }
};

// ---------- Loading saved items ----------

Item* Item::load(vector<string> f) {
    if (f.size() != 7) return nullptr;

    stringstream a(f[2]), b(f[3]);
    double price = 0;
    int quantity = 0;
    a >> price;
    b >> quantity;

    if (f[0] == "G") {
        double weight = 0;
        bool organic = f[6] == "1";
        stringstream(f[5]) >> weight;
        return new Grocery(f[1], price, quantity, f[4], weight, organic);
    }

    if (f[0] == "E") {
        int warranty = 0;
        double power = 0;
        stringstream(f[5]) >> warranty;
        stringstream(f[6]) >> power;
        return new Electronics(f[1], price, quantity, f[4], warranty, power);
    }

    if (f[0] == "C")
        return new Clothing(f[1], price, quantity, f[4], f[5], f[6]);

    if (f[0] == "B") {
        int pages = 0;
        stringstream(f[6]) >> pages;
        return new Book(f[1], price, quantity, f[4], f[5], pages);
    }

    if (f[0] == "T") {
        int age = 0;
        stringstream(f[5]) >> age;
        return new Toy(f[1], price, quantity, f[4], age, f[6] == "1");
    }

    return nullptr;
}

// ---------- Main program ----------

int main() {
}