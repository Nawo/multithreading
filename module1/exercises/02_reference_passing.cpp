#include <iostream>
#include <thread>

using namespace std;

void add10(int& a) {
    a += 10;
}

int main() {
    int a = 0;

    std::cout << "a: " << a << std::endl;

    std::thread t1{[&]() { add10(a); }};
    // std::thread t2{add10, std::ref(a)}; std::ref() to wrapper do przekazywania referencji

    std::cout << "a: " << a << std::endl;

    return 0;
}
