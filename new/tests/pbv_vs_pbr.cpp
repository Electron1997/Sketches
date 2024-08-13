#include <chrono>
#include <random>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

inline uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

inline uint32_t hash32_pbv(const uint32_t k, const size_t i){
    return splitmix64((i << 32) | k);
}

uint32_t hash32_pbr(const uint32_t& k, const size_t& i){
    return splitmix64((i << 32) | k);
}

uint32_t test_pbv(size_t n){
    uint32_t s = 0;
    for(size_t i = 0; i < n; ++i){
        uint32_t k = rng();
        size_t j = rng();
        s += hash32_pbv(k, j);
    }
    return s;
}

uint32_t test_pbr(size_t n){
    uint32_t s = 0;
    for(size_t i = 0; i < n; ++i){
        uint32_t k = rng();
        size_t j = rng();
        s += hash32_pbr(k, j);
    }
    return s;
}

int main(int argc, char *argv[]){
    size_t n = std::stoi(argv[1]);
    test_pbv(n);
}