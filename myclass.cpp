#include <iostream>
#include <string>
using namespace std;

class MyClass {
private:
    string field1;
    int    field2;

public:
    MyClass() : field1("Hello world"), field2(2) {
        cout << "Constructor called" << endl;
    }

    MyClass(const string& str1, int int1) : field1(str1), field2(int1) {
        cout << "Constructor called" << endl;
    }

    ~MyClass() {
        cout << "Destructor called" << endl;
    }

    // Accessors
    void   setField1(const string& s) { field1 = s; }
    string getField1() const          { return field1; }
    int    getField2() const          { return field2; }
};

int main() {
    cout << "Hello, from cdemo!" << endl;

    // Objects on the stack
    MyClass obj1, obj3("Mark", 5);
    obj1.setField1("Mark");
    cout << obj1.getField1() << " " << obj1.getField2() << endl;
    cout << obj3.getField1() << " " << obj3.getField2() << endl;

    // Object on the heap
    MyClass* obj2 = new MyClass("Mark", 5);
    cout << obj2->getField1() << " " << obj2->getField2() << endl;
    delete obj2;
    obj2 = nullptr;

    // Array on the stack (uses default constructor)
    MyClass myclassarray[3];
    for (int i = 0; i < 3; ++i) {
        myclassarray[i].setField1("Elem" + to_string(i));
    }
    for (int i = 0; i < 3; ++i) {
        cout << myclassarray[i].getField1() << " "
             << myclassarray[i].getField2() << endl;
    }

    return 0;
}