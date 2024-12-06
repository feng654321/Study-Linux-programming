#include <atomic>
#include <thread>
#include <cassert>

int y = 0; 
std::atomic<int> x(0);

void thread1() {
    y = 1;
    x.store(1, std::memory_order_relaxed);  // 使用 seq_cst 内存顺序
}

void thread2() {
    if (x.load(std::memory_order_relaxed) == 1) {
        assert(y == 1); // 使用 seq_cst 内存顺序
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
