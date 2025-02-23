#include <iostream>
#include <thread>

void do_something(int data) {
    std::cout << "Data: " << data << "\n" << std::flush;
}

struct Foo {
public:
    Foo(int& i): i_(i) {}
    void operator()(){
        for (int k = 0 ; k < 100000 ; ++k) {
            do_something(++i_);
        }
    }

private:
    int& i_;
};

void oops() {
    int some_local_state = 0;
    Foo foo(some_local_state);
    std::thread t(foo);
    std::cout << "Detach thread\n" << std::flush;
    t.detach();
}

int main()
{
    std::thread t(oops);
    t.join();

    return 0;
}