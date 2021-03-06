#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int is_prime(int n);

void count(int &counter, int from, int to);


template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


inline std::chrono::high_resolution_clock::time_point get_current_time_fenced();

int main(int argc, char **argv) {
    int const N = 100000000;
    int counter = 0;
    cout << "launched" << endl;
    auto start_time = get_current_time_fenced();
    count(counter, 1, N);
    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    cout << "Total time: " << to_us(total_time) << endl;
    cout << "value is: " << counter << endl;
    return 0;
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

int is_prime(int n) {
    for (int i = 2; i < n; ++i) {
        if (!(n % i)) {
            return 0;
        }
    }
    return 1;
}


void count(int &counter, int from, int to) {
    for (int i = from; i < to; i += 2) {
        if (is_prime(i)) {
            counter++;
        }
    }
}
