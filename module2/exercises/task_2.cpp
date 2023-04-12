#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Zaimplementuj program, w którym 4 wątki będą wyświetlać swój std::this_thread::id()
// określoną liczbę razy

using namespace std::chrono_literals;

void doWork(std::mutex& m, int a, std::chrono::seconds time) {
    {
        std::lock_guard<std::mutex> lock(m);
        for (int i = 0; i < a; i++)
            std::cout << "thread: " << std::this_thread::get_id() << std::endl;
    }
    std::this_thread::sleep_for(time);
}

int main() {
    std::mutex mut;
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(std::thread(doWork, std::ref(mut), 4, 5s));
    }
    for (auto& a : threads) {
        a.join();
    }
}