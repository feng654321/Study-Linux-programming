//include header files
#include <benchmark/benchmark.h>    //benchmark library
#include <vector>                   //vector library
#include <algorithm>                //algorithm library
#include <cstdlib>                  //cstdlib library
#include <cstdint>                  //cstdint library


constexpr uint8_t range=100;
constexpr size_t elementsInRandomSet=10000;

//Auxiliary functions and constantsAuxiliary functions and constants
auto generateRandomData(uint8_t max, size_t n)
{
    std::vector<uint8_t> result(n);
 
    std::generate(begin(result), end(result), [&]{
        return std::rand()%max;
    });
 
    return result;
}


//test_no_data_dependency
void BM_no_data_dependency(benchmark::State& state){
    const auto probability = state.range(0);
    
    const auto data = generateRandomData(range, elementsInRandomSet);
    uint8_t sum=0;
    
    for (auto _ : state)
    {
        for (auto element : data)
        {
            if(__builtin_expect(!!(element < probability), 1))
            {
                sum += element;
            }
            sum+=element%7;
        }
    }
}

//test data dependecny 
void BM_data_dependency(benchmark::State& state){
    const auto probability = state.range(0);
    
    const auto data = generateRandomData(range, elementsInRandomSet);
    uint8_t sum=0;
    
    for (auto _ : state)
    {
        for (auto element : data)
        {
            if(__builtin_expect(!!(sum < probability), 1))
            {
				element+=sum%13;
			}
			sum+=element%7;
			sum += sum %17;
        }
		benchmark::DoNotOptimize(sum);
    }
}

//main function to run the benchmark
BENCHMARK(BM_no_data_dependency)->DenseRange(1, 100);
BENCHMARK(BM_data_dependency)->DenseRange(1, 100);

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}