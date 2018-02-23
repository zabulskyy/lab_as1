#include <iostream>
#include <chrono>
#include <atomic>

using namespace std;

int is_prime(int n);

void count_single();

void count_single(int N);

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced();

int main(int argc, char **argv) {
    count_single(100);
    return 0;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int is_prime(int n) {
    for (int i = 2; i < n; ++i) {
        if (!(n % i)) {
            return 0;
        }
    }
    return 1;
}

void count_single() {
    auto start_time = get_current_time_fenced();
    int N = 100000000;
    for (int i = 3; i < N; i += 2) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    cout << "Total time: " << to_us(total_time) << endl;
}


void count_single(int N) {
    auto start_time = get_current_time_fenced();
    for (int i = 3; i < N; i += 2) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    cout << "Total time: " << to_us(total_time) << endl;
}

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

