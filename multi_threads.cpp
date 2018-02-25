#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int is_prime(int n);

void count(int &counter, int from, int to, mutex &m);

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced();

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

int main(int argc, char *argv[]) {
    int n = 1;

    if (argc > 4) {
        n = atoi(argv[argc - 1]);
    }
    mutex mux;


    int const N = 100000;
    /******************/
    thread threads[n];
    int x = 0;

    auto start_time = get_current_time_fenced();

    for (int i = 0; i < n; ++i) {
        cout << "thread " << i + 1 << " started" << endl;
        threads[i] = thread(count, std::ref(x), N / n * (i) + 1, N / n * (i + 1) + 1, std::ref(mux));
    }

    for (int i = 0; i < n; ++i) {
        threads[i].join();
    }


    /******************/

    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    cout << "Total time: " << to_us(total_time) << endl;
    cout << "value is: " << x << endl;

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

void count(int &counter, int from, int to, mutex &m) {
    for (int i = from; i < to; i += 1) {
        if (is_prime(i)) {
            m.lock();
            counter++;
            m.unlock();

        }
    }
}

