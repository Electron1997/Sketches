#include <random>

#include "../data/synthetic_trace.hpp"
#include "../hashing/hash.hpp"
#include "optimized_volume_table.hpp"
#include "unoptimized_volume_table.hpp"

constexpr size_t D = 30, W = 30;

unoptimized_volume_table<uint32_t, float, D, W, hash32> unoptimized_table;
unoptimized_volume_table<uint32_t, int, D, W, hash32> optimized_table;

void test_unoptimized_table(int n){
    for(size_t i = 0; i < n; ++i){
        unoptimized_table.update(uniform_key<uint32_t>(0, 10000), normal_volume<float>(0.0, 5.0));
    }
}

void test_optimized_table(int n){
    for(size_t i = 0; i < n; ++i){
        optimized_table.update(uniform_key<uint32_t>(0, 10000), uniform_key<int>(0, 10000));
    }
}

int main(int argc, char *argv[]){
    int n = std::stoi(argv[1]);
    test_unoptimized_table(n);
}