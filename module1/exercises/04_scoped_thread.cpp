#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

using namespace std;

class scoped_thread {
public:
    explicit scoped_thread(thread&& t) {
        if (t.joinable())
            t_ = std::move(t);
    }
    template <typename Function, typename... Args>
    scoped_thread(Function&& f, Args&&... args)
        : t_(std::forward<Function>(f),
             std::forward<Args>(args)...) {
    }  // perfekcyjny forwarding

    scoped_thread(scoped_thread&& other)
        : t_(std::move(other.t_)) {
    }  // konstruktor przenoszacy

    scoped_thread& operator=(scoped_thread&& other) {  // operator przenoszenia
        if (&other != this) {
            t_ = std::move(other.t_);  // self assignmed
        }
        return *this;
    }

    scoped_thread(scoped_thread const& other) = delete;             // konstruktor kopiujacy
    scoped_thread& operator=(scoped_thread const& other) = delete;  // operator kopiowania

    ~scoped_thread() {
        if (t_.joinable())
            t_.join();
    }

private:
    thread t_;
};

void do_sth(int) {
    std::cout << "threaaaad" << std::endl;
    this_thread::sleep_for(1s);
}

void do_sth_unsafe_in_current_thread() {
    throw runtime_error("Whoa!");
}

int main() {
    scoped_thread st(thread(do_sth, 42));
    // auto st2 = st;  // copying not allowed
    auto st3 = move(st);
    scoped_thread sr(do_sth, 12);

    try {
        do_sth_unsafe_in_current_thread();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}  // thread is safely destroyed