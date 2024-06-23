// Synthetic trace generation
#include "../typedefs.hpp"

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

inline TKey uniform_key(TKey l, TKey r){
    std::uniform_int_distribution<TKey> key(l, r);
    return key(gen);
}

inline TVol normal_volume(TVol mu, TVol sigma){
    std::normal_distribution<TVol> volume(mu, sigma);
    return volume(gen);
}

inline item uniform_normal_item(TKey l, TKey r, TVol mu, TVol sigma){
    return {uniform_key(l, r), normal_volume(mu, sigma)};
}

void load_synthetic_trace(item (*synthetic_item)(), item* buf, size_t index, size_t n){
    for(size_t i = index; i < index + n; ++i){
        buf[i] = synthetic_item();
    }
}