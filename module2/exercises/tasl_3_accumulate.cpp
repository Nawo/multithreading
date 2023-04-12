#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>

template <class InputIt, class T>
constexpr void thread_count(T& var, std::mutex& mutex, InputIt first, InputIt last) {
    T result = std::accumulate(first, last, 0);
    std::lock_guard<std::mutex> lock(mutex);
    var = std::move(result);
}

template <class InputIt, class T>
constexpr T accumulate_imp(InputIt first, InputIt last, T init) {
    size_t distance = std::distance(first, last);

    std::mutex m;

    size_t number_of_thread = std::thread::hardware_concurrency();

    size_t counts_per_thread = floor(distance / number_of_thread);

    std::vector<std::thread> threads;

    std::vector<T> vector_counts;
    vector_counts.resize(number_of_thread);

    for (int i = 0; i < number_of_thread - 1; i++) {
        threads.emplace_back(thread_count<InputIt, T>,
                             std::ref(vector_counts[i]),
                             std::ref(m),
                             first,
                             first + counts_per_thread);
        std::advance(first, counts_per_thread);
    }

    vector_counts[number_of_thread - 1] = std::accumulate(first, last, 0);

    for (auto& a : threads) {
        a.join();
    }

    for (const auto& a : vector_counts) {
        init += a;
    }

    return init;
}

int main() {
    std::vector<int> v(98751112);
    std::generate(v.begin(), v.end(), []() { return 1; });

    auto start_1 = std::chrono::high_resolution_clock::now();
    auto result_1 = accumulate_imp(v.begin(), v.end(), 1);
    auto end_1 = std::chrono::high_resolution_clock::now();
    std::cout << result_1 << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end_1 - start_1).count() << std::endl;

    auto start_2 = std::chrono::high_resolution_clock::now();
    auto result_2 = std::accumulate(v.begin(), v.end(), 1);
    auto end_2 = std::chrono::high_resolution_clock::now();
    std::cout << result_2 << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end_2 - start_2).count() << std::endl;
}