#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
 
static const char SEP = '|';
static const char* DATA_FILE = "shopping_items.txt";
 
static std::vector<std::string> split(const std::string& line, char sep) {
    std::vector<std::string> fields;
    std::string current;
    for (std::size_t i = 0; i < line.size(); ++i) {
        if (line[i] == sep) {
            fields.push_back(current);
            current.clear();
        } else {
            current += line[i];
        }
    }
    fields.push_back(current);
    return fields;
}
static std::string sanitize(std::string s) {
    for (std::size_t i = 0; i < s.size(); ++i)
        if (s[i] == SEP) s[i] = '/';
    return s;
}
 
static std::string readString(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt << ": ";
        if (!std::getline(std::cin, s)) throw std::runtime_error("input closed");
        s = sanitize(s);
        if (!s.empty()) return s;
        std::cout << "  Value cannot be empty.\n";
    }
}
 
static double readDouble(const std::string& prompt, double minValue) {
    while (true) {
        std::string s = readString(prompt);
        try {
            std::size_t pos = 0;
            double v = std::stod(s, &pos);
            if (pos == s.size() && v >= minValue) return v;
        } catch (const std::exception&) {}
        std::cout << "  Enter a number >= " << minValue << ".\n";
    }
}
 
static int readInt(const std::string& prompt, int minValue) {
    while (true) {
        std::string s = readString(prompt);
        try {
            std::size_t pos = 0;
            int v = std::stoi(s, &pos);
            if (pos == s.size() && v >= minValue) return v;
        } catch (const std::exception&) {}
        std::cout << "  Enter a whole number >= " << minValue << ".\n";
    }
}
 
static bool readBool(const std::string& prompt) {
    while (true) {
        std::string s = readString(prompt + " (y/n)");
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "  Please answer y or n.\n";
    }
}
 
static std::string yesNo(bool b) { return b ? "yes" : "no"; }
 
static void requireFields(const std::vector<std::string>& f, std::size_t n) {
    if (f.size() != n) throw std::runtime_error("wrong number of fields");
}
 
class Item {
public:
    Item(const std::string& name, double price, int quantity)
        : name_(name), price_(price), quantity_(quantity) {}
    virtual ~Item() {}

    virtual void display() const {
        std::cout << "[" << typeName() << "] " << name_
                  << " | price: " << std::fixed << std::setprecision(2) << price_
                  << " | qty: " << quantity_ << '\n';
    }
 
    // Writes one complete line (ends with std::endl).
    virtual void persist(std::ofstream& out) const = 0;
 
protected:
    virtual const char* typeName() const = 0;
    virtual char typeId() const = 0;
 
    void persistCommon(std::ofstream& out) const {
        out << typeId() << SEP << name_ << SEP << std::to_string(price_)
            << SEP << quantity_;
    }
 
    static void parseCommon(const std::vector<std::string>& f,
                            std::string& name, double& price, int& qty) {
        name = f[1];
        price = std::stod(f[2]);
        qty = std::stoi(f[3]);
    }
 
    std::string name_;
    double price_;
    int quantity_;
};
 
class Grocery : public Item {
public:
    Grocery(const std::string& name, double price, int qty,
            const std::string& expiry, double weightKg, bool organic)
        : Item(name, price, qty), expiry_(expiry), weightKg_(weightKg), organic_(organic) {}
 
    void display() const override {
        Item::display();
        std::cout << "    expires: " << expiry_ << ", weight: " << weightKg_
                  << " kg, organic: " << yesNo(organic_) << '\n';
    }
 
    void persist(std::ofstream& out) const override {
        persistCommon(out);
        out << SEP << expiry_ << SEP << std::to_string(weightKg_) << SEP << organic_
            << std::endl;
    }
 
    static Item* fromFields(const std::vector<std::string>& f) {
        requireFields(f, 7);
        std::string name; double price; int qty;
        parseCommon(f, name, price, qty);
        return new Grocery(name, price, qty, f[4], std::stod(f[5]), f[6] == "1");
    }
 
    static Item* fromConsole() {
        std::string name = readString("Name");
        double price = readDouble("Price", 0);
        int qty = readInt("Quantity", 1);
        std::string expiry = readString("Expiry date (YYYY-MM-DD)");
        double weight = readDouble("Weight (kg)", 0);
        bool organic = readBool("Organic");
        return new Grocery(name, price, qty, expiry, weight, organic);
    }
 
protected:
    const char* typeName() const override { return "Grocery"; }
    char typeId() const override { return 'G'; }
 
private:
    std::string expiry_;
    double weightKg_;
    bool organic_;
};
 
class Electronics : public Item {
public:
    Electronics(const std::string& name, double price, int qty,
                const std::string& brand, int warrantyMonths, double powerWatts)
        : Item(name, price, qty), brand_(brand),
          warrantyMonths_(warrantyMonths), powerWatts_(powerWatts) {}
 
    void display() const override {
        Item::display();
        std::cout << "    brand: " << brand_ << ", warranty: " << warrantyMonths_
                  << " months, power: " << powerWatts_ << " W\n";
    }
 
    void persist(std::ofstream& out) const override {
        persistCommon(out);
        out << SEP << brand_ << SEP << warrantyMonths_ << SEP
            << std::to_string(powerWatts_) << std::endl;
    }
 
    static Item* fromFields(const std::vector<std::string>& f) {
        requireFields(f, 7);
        std::string name; double price; int qty;
        parseCommon(f, name, price, qty);
        return new Electronics(name, price, qty, f[4], std::stoi(f[5]), std::stod(f[6]));
    }
 
    static Item* fromConsole() {
        std::string name = readString("Name");
        double price = readDouble("Price", 0);
        int qty = readInt("Quantity", 1);
        std::string brand = readString("Brand");
        int warranty = readInt("Warranty (months)", 0);
        double power = readDouble("Power (W)", 0);
        return new Electronics(name, price, qty, brand, warranty, power);
    }
 
protected:
    const char* typeName() const override { return "Electronics"; }
    char typeId() const override { return 'E'; }
 
private:
    std::string brand_;
    int warrantyMonths_;
    double powerWatts_;
};
 
class Clothing : public Item {
public:
    Clothing(const std::string& name, double price, int qty,
             const std::string& size, const std::string& material, const std::string& color)
        : Item(name, price, qty), size_(size), material_(material), color_(color) {}
 
    void display() const override {
        Item::display();
        std::cout << "    size: " << size_ << ", material: " << material_
                  << ", color: " << color_ << '\n';
    }
 
    void persist(std::ofstream& out) const override {
        persistCommon(out);
        out << SEP << size_ << SEP << material_ << SEP << color_ << std::endl;
    }
 
    static Item* fromFields(const std::vector<std::string>& f) {
        requireFields(f, 7);
        std::string name; double price; int qty;
        parseCommon(f, name, price, qty);
        return new Clothing(name, price, qty, f[4], f[5], f[6]);
    }
 
    static Item* fromConsole() {
        std::string name = readString("Name");
        double price = readDouble("Price", 0);
        int qty = readInt("Quantity", 1);
        std::string size = readString("Size");
        std::string material = readString("Material");
        std::string color = readString("Color");
        return new Clothing(name, price, qty, size, material, color);
    }
 
protected:
    const char* typeName() const override { return "Clothing"; }
    char typeId() const override { return 'C'; }
 
private:
    std::string size_, material_, color_;
};
 
class Book : public Item {
public:
    Book(const std::string& name, double price, int qty,
         const std::string& author, const std::string& isbn, int pages)
        : Item(name, price, qty), author_(author), isbn_(isbn), pages_(pages) {}
 
    void display() const override {
        Item::display();
        std::cout << "    author: " << author_ << ", ISBN: " << isbn_
                  << ", pages: " << pages_ << '\n';
    }
 
    void persist(std::ofstream& out) const override {
        persistCommon(out);
        out << SEP << author_ << SEP << isbn_ << SEP << pages_ << std::endl;
    }
 
    static Item* fromFields(const std::vector<std::string>& f) {
        requireFields(f, 7);
        std::string name; double price; int qty;
        parseCommon(f, name, price, qty);
        return new Book(name, price, qty, f[4], f[5], std::stoi(f[6]));
    }
 
    static Item* fromConsole() {
        std::string title = readString("Title");
        double price = readDouble("Price", 0);
        int qty = readInt("Quantity", 1);
        std::string author = readString("Author");
        std::string isbn = readString("ISBN");
        int pages = readInt("Pages", 1);
        return new Book(title, price, qty, author, isbn, pages);
    }
 
protected:
    const char* typeName() const override { return "Book"; }
    char typeId() const override { return 'B'; }
 
private:
    std::string author_, isbn_;
    int pages_;
};

class Toy : public Item {
public:
    Toy(const std::string& name, double price, int qty,
        const std::string& brand, int minAge, bool needsBatteries)
        : Item(name, price, qty), brand_(brand), minAge_(minAge),
          needsBatteries_(needsBatteries) {}
 
    void display() const override {
        Item::display();
        std::cout << "    brand: " << brand_ << ", min age: " << minAge_
                  << ", needs batteries: " << yesNo(needsBatteries_) << '\n';
    }
 
    void persist(std::ofstream& out) const override {
        persistCommon(out);
        out << SEP << brand_ << SEP << minAge_ << SEP << needsBatteries_ << std::endl;
    }
 
    static Item* fromFields(const std::vector<std::string>& f) {
        requireFields(f, 7);
        std::string name; double price; int qty;
        parseCommon(f, name, price, qty);
        return new Toy(name, price, qty, f[4], std::stoi(f[5]), f[6] == "1");
    }
 
    static Item* fromConsole() {
        std::string name = readString("Name");
        double price = readDouble("Price", 0);
        int qty = readInt("Quantity", 1);
        std::string brand = readString("Brand");
        int minAge = readInt("Minimum age", 0);
        bool batteries = readBool("Needs batteries");
        return new Toy(name, price, qty, brand, minAge, batteries);
    }
 
protected:
    const char* typeName() const override { return "Toy"; }
    char typeId() const override { return 'T'; }
 
private:
    std::string brand_;
    int minAge_;
    bool needsBatteries_;
};
 
std::vector<Item*> restore(std::ifstream& in) {
    std::vector<Item*> items;
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty()) continue;
        std::vector<std::string> f = split(line, SEP);
        try {
            Item* item = nullptr;
            if (f[0] == "G")      item = Grocery::fromFields(f);
            else if (f[0] == "E") item = Electronics::fromFields(f);
            else if (f[0] == "C") item = Clothing::fromFields(f);
            else if (f[0] == "B") item = Book::fromFields(f);
            else if (f[0] == "T") item = Toy::fromFields(f);
            else throw std::runtime_error("unknown type ID '" + f[0] + "'");
            items.push_back(item);
        } catch (const std::exception& e) {
            std::cerr << "Skipping line " << lineNo << ": " << e.what() << '\n';
        }
    }
    return items;
}
 
void persistAll(const std::vector<Item*>& items, std::ofstream& out) {
    for (std::size_t i = 0; i < items.size(); ++i) items[i]->persist(out);
}
 
void displayAll(const std::vector<Item*>& items) {
    if (items.empty()) {
        std::cout << "(no items)\n";
        return;
    }
    for (std::size_t i = 0; i < items.size(); ++i) items[i]->display();
}
 
void clearItems(std::vector<Item*>& items) {
    for (std::size_t i = 0; i < items.size(); ++i) delete items[i];
    items.clear();
}
 
static void printMenu() {
    std::cout << "\n1) Add grocery\n2) Add electronics\n3) Add clothing\n"
                 "4) Add book\n5) Add toy\n6) Show items\n0) Save and exit\n> ";
}
 
int main() {
    std::vector<Item*> items;

    {
        std::ifstream in(DATA_FILE);
        if (in) {
            items = restore(in);
            std::cout << "Loaded " << items.size() << " item(s) from " << DATA_FILE << ".\n";
        }
    }
 
    try {
        while (true) {
            printMenu();
            std::string choice;
            if (!std::getline(std::cin, choice)) break;  
            if (choice == "0") break;
            else if (choice == "1") items.push_back(Grocery::fromConsole());
            else if (choice == "2") items.push_back(Electronics::fromConsole());
            else if (choice == "3") items.push_back(Clothing::fromConsole());
            else if (choice == "4") items.push_back(Book::fromConsole());
            else if (choice == "5") items.push_back(Toy::fromConsole());
            else if (choice == "6") displayAll(items);
            else std::cout << "Unknown option.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "\nInput ended unexpectedly (" << e.what() << ").\n";
    }
 
    std::cout << "\n=== All items ===\n";
    displayAll(items);
 
    std::ofstream out(DATA_FILE);
    if (out) {
        persistAll(items, out);
        std::cout << "\nSaved " << items.size() << " item(s) to " << DATA_FILE << ".\n";
    } else {
        std::cerr << "Could not write " << DATA_FILE << ".\n";
    }
 
    clearItems(items);
    return 0;
}
