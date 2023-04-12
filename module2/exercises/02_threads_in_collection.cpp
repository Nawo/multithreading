#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

using namespace std;

// Secure your code so that each thread can safely enter its full text into the stream.

void do_work(int id, std::mutex& m) {
    this_thread::sleep_for(100ms);
    std::lock_guard<std::mutex> lock(m);
    cout << "Thread [" << id << "]: "
         << "Job done!" << endl;
}

int main() {
    mutex cout_mutex;

    vector<thread> threads;
    for (int i = 0; i < 20; i++) {
        threads.emplace_back(thread(do_work, i, std::ref(cout_mutex)));
    }
    for (auto&& t : threads) {
        t.join();
    }
    return 0;
}
