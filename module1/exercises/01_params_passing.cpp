#include <iostream>
#include <thread>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    std::thread t1{add, 3, 4};
    t1.join();

    return 0;
}
