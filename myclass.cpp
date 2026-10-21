#include <iostream>

using namespace std;

class MyClass{

    private:
        string field1;
        int field2;

    public:

        //Default Constructor
        MyClass() : field1("Hello world"), field2(2) {
            cout << "Constructor called " << endl;
        }

        //Parenthesized Constructor
        MyClass(const string& str1, int int1) : field1(str1), field2(int1) {
            cout << "Constructor called" << endl;
        }

        //Destructor
        ~MyClass() {
            cout << "Destructor called" << endl;
        }
};