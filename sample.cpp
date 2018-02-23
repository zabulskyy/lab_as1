#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#if 0
void worker(const int& x, std::mutex& m){
    for(int i = 0; i<100; ++i) {
        std::this_thread::sleep_for(std :: chrono::milliseconds(1));
        m.lock();
        std::cout << "Hello from thread: " << x << std::endl;
        m.unlock();
    }
}

class A
{
    std::mutex &m;
public:
    explicit A(std::mutex &m_): m(m_)
    {}

    A& operator()(int a){
        for(int i = 0; i<100; ++i) {
            std::this_thread::sleep_for(std :: chrono::milliseconds(1));
            m.lock();
            std::cout << "Hello from thread: " << a << std::endl;
            m.unlock();
        }
    }
};
int main(){
    std::mutex mux;
    std :: thread thread1(A(mux), 1);
    std :: thread thread2(worker, 2, std::ref(mux));
    std :: thread thread3([&mux](int x){
        for(int i = 0; i<100; ++i) {
            std::this_thread::sleep_for(std :: chrono::milliseconds(1));
            mux.lock();
            std::cout << "THread: " << x << std::endl;
            mux.unlock();
        }
                          },
                                    3);
    std :: cout << "Hello from main" << std::endl;
    thread1. join ();
    thread2. join ();
    thread3. join ();
}

# endif










#if 1
#include <iostream>
#include <limits>

using namespace std;

template <typename  T, size_t N = 10>
T digits_sum(T n)
{
    T res = 0;
    while(n!=0)
    {
        res += n % N;
        n /= N;
    }
    return res;
}

int main()
{
#if 1
    volatile unsigned long long log_r = 0;
    //for(unsigned long long i = 0; i<std::numeric_limits<decltype(i)>::max(); ++i)
    for(unsigned long long i = 0; i<100000; ++i) {
        auto r1 = digits_sum(i);;
        if (i % 10000 == 0)
            cout << ".";
        for (unsigned long long j = 0; j < 100000; ++j) {
            auto r2 = digits_sum(j);
            if (r1 == r2)
                ++log_r;
        }
    }
    cout << log_r << endl;

    return 0;
#endif
}

#if 0
#include <iostream>

int main() {

    asm(
            "nop\n"
            "nop\n"
            "nop\n"
        "nop\n");
    for(int i = 0; i<10; ++i)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
#endif

#endif