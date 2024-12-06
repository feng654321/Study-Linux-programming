#include <benchmark/benchmark.h>
#include <atomic>
#include <thread>
#include <cassert>

// Global variables
std::atomic<bool> x = {false};
std::atomic<bool> y = {false};
std::atomic<int> z = {0};
int data = 0;

void write_x() {
	data = 100;
    x.store(true, std::memory_order_relaxed);
}

void write_y() {
    y.store(true, std::memory_order_relaxed);
}

void read_x_then_y() {
    while (!x.load(std::memory_order_relaxed));
	assert(data == 100);
}

void read_y_then_x() {
    while (!y.load(std::memory_order_relaxed));
    if (x.load(std::memory_order_relaxed)) {
        ++z;
    }
}
static void BenchmarkThreads(benchmark::State& state) {
    for (auto _ : state) {

        std::thread a(write_x);
        //std::thread b(write_y);
		std::thread c(read_x_then_y);
        //std::thread d(read_y_then_x);

		a.join(); 
		//b.join(); 
		c.join(); 
		//d.join();
		//assert(z.load() != 0);
    }
}

BENCHMARK(BenchmarkThreads)->DenseRange(1, 100);


BENCHMARK_MAIN();
