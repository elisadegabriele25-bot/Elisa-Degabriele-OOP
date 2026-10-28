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
    private:
    string expiry;
    double weight;

public:
    Grocery(string n, double p, int q, string e, double w, bool o)
        : Item(n, p, q), expiry(e), weight(w), organic(o) {}

    void display() const override;
    void displayGroceryInfo() const;

    string getExpiry() const;
    double getWeight() const;
};
