#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const char SEP = '|';
const string FILE_NAME = "shopping_items.txt";

// ---------- Input helpers ----------

string readString(string prompt) {
    string s;
    do {
        cout << prompt << ": ";
        getline(cin, s);
    } while (s.empty());

    for (char& c : s)
        if (c == SEP) c = '/';

    return s;
}

template <typename T>
T readNumber(string prompt, T minValue) {
    T value;
    string s;

    while (true) {
        cout << prompt << ": ";
        getline(cin, s);

        stringstream ss(s);
        char extra;

        if (ss >> value && !(ss >> extra) && value >= minValue)
            return value;

        cout << "Invalid number. Try again.\n";
    }
}

bool readBool(string prompt) {
    string s;

    while (true) {
        s = readString(prompt + " (y/n)");

        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;

        cout << "Enter y or n.\n";
    }
}

string yesNo(bool value) {
    return value ? "yes" : "no";
}

vector<string> split(string s) {
    vector<string> fields;
    string field;
    stringstream ss(s);

    while (getline(ss, field, SEP))
        fields.push_back(field);

    return fields;
}

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

    virtual void display() const {
        cout << "[" << type() << "] " << name
             << " | Price: " << fixed << setprecision(2) << price
             << " | Quantity: " << quantity << '\n';
    }

    virtual string type() const = 0;
    virtual char id() const = 0;
    virtual void save(ofstream& out) const = 0;

    void saveCommon(ofstream& out) const {
        out << id() << SEP << name << SEP
            << price << SEP << quantity;
    }

    static Item* load(vector<string> f);
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

    void save(ofstream& out) const override {
        saveCommon(out);
        out << SEP << expiry << SEP << weight << SEP << organic << '\n';
    }

    static Item* create() {
        return new Grocery(
            readString("Name"), readNumber<double>("Price", 0.0),
            readNumber<int>("Quantity", 1),
            readString("Expiry date"), readNumber<double>("Weight (kg)", 0.0),
            readBool("Organic"));
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

    void save(ofstream& out) const override {
        saveCommon(out);
        out << SEP << brand << SEP << warranty << SEP << power << '\n';
    }

    static Item* create() {
        return new Electronics(
            readString("Name"), readNumber<double>("Price", 0.0),
            readNumber<int>("Quantity", 1), readString("Brand"),
            readNumber<int>("Warranty (months)", 0),
            readNumber<double>("Power (W)", 0.0));
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

    void save(ofstream& out) const override {
        saveCommon(out);
        out << SEP << size << SEP << material << SEP << color << '\n';
    }

    static Item* create() {
        return new Clothing(
            readString("Name"), readNumber<double>("Price", 0.0),
            readNumber<int>("Quantity", 1), readString("Size"),
            readString("Material"), readString("Color"));
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

    void save(ofstream& out) const override {
        saveCommon(out);
        out << SEP << brand << SEP << minAge << SEP << batteries << '\n';
    }

    static Item* create() {
        return new Toy(
            readString("Name"), readNumber<double>("Price", 0.0),
            readNumber<int>("Quantity", 1), readString("Brand"),
            readNumber<int>("Minimum age", 0),
            readBool("Needs batteries"));
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
    vector<Item*> items;
    ifstream in(FILE_NAME);
    string line;

    while (getline(in, line)) {
        vector<string> fields = split(line);
        Item* item = Item::load(fields);

        if (item)
            items.push_back(item);
    }
    in.close();

    cout << "Loaded " << items.size() << " item(s).\n";

    while (true) {
        cout << "\n1. Add grocery\n"
             << "2. Add electronics\n"
             << "3. Add clothing\n"
             << "4. Add book\n"
             << "5. Add toy\n"
             << "6. Show items\n"
             << "0. Save and exit\n"
             << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "0") break;
        else if (choice == "1") items.push_back(Grocery::create());
        else if (choice == "2") items.push_back(Electronics::create());
        else if (choice == "3") items.push_back(Clothing::create());
        else if (choice == "4") items.push_back(Book::create());
        else if (choice == "5") items.push_back(Toy::create());
        else if (choice == "6") {
            if (items.empty())
                cout << "No items.\n";

            for (Item* item : items)
                item->display();
        }
        else
            cout << "Invalid choice.\n";
    }

    ofstream out(FILE_NAME);

    for (Item* item : items) {
        item->save(out);
        delete item;
    }

    cout << "Items saved. Goodbye!\n";
    return 0;
}