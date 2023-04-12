#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

void doWork(int id, std::mutex& mutex) {
    std::this_thread::sleep_for(1s);
    std::lock_guard<std::mutex> lock{mutex};
    std::cout << "[" << id << "]"
              << " thread" << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    std::mutex m;
    for (int i = 0; i < 20; i++) {
        threads.emplace_back(std::thread{doWork, i, std::ref(m)});
    }
    for (auto& a : threads) {
        a.join();
    }
}