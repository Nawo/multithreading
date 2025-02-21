#include <vector>
#include <iostream>
using namespace std;

class X {
    vector<double> values;
     
    void initializeOne()   { values = {1.0}; }
    void initializeTwo()   { values = {1.0, 2.0}; }
    void initializeThree() { values = {1.0, 2.0, 3.0}; }

public:
    explicit X(int i) noexcept {
        switch (i) {
        case 2:  // top priority
            initializeTwo();
            [[fallthrough]];
        case 3:
            initializeThree();
            [[fallthrough]];
        default:  // least priority
            initializeOne();
        // yes, replacing [[fallthrough]] with break is a better solution,
        // but this code is for educational purpose only ;)
        }
    }

    void print() {
        for (const auto & value : values)
            cout << value << " ";
        cout << "\n\n";
    }
};

int main() {
    X x2{2};
    x2.print();
    
    X x3{3};
    x3.print();
    
    X x0{0};
    x0.print();
    
    return 0;
}
