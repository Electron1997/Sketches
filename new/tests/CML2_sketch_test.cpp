#include "../prior_estimation/CML2_sketch.hpp"
#include "../hashing/hash.hpp"

#include <iostream>

typedef uint32_t TKey;
typedef float TVol;

typedef struct{
    TKey key;
    TVol volume;
} item;

item buf[100] = {{0, 10}, {1, 10}, {0, 1}, {2, 3}};

CML2_sketch<TKey, TVol, 10, 10, hash32> cml2;


TVol test_CML2_sketch(size_t n){
    for(size_t i = 0; i < n; ++i){
        cml2.update(buf[i].key, buf[i].volume);
    }
    return cml2.l2_estimate();
}


int main(){
    std::cout << test_CML2_sketch(4) << std::endl;
}