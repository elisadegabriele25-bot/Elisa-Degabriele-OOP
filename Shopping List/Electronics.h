#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Item.h"
#include <fstream>

class Electronics : public Item {
    public:
    Electronics(const string& n, double p, int elId, string brand);
    ~Electronics() override = default;

    void displayElectronicsInfo() const;
    void persist(ofstream& out) const override;

    private:
    int elecId;
    string elecBrand;
};

#endif //ELECTRONICS_H