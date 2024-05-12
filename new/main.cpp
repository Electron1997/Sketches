#include "CCA_sketch.hpp"
#include <functional>
#include <istream>
#include <stddef.h>
#include <streambuf>


typedef unsigned TKey;
typedef double TVol;

typedef struct{
    TKey key;
    TVol volume;
} item;

std::hash<int> h;

unsigned key_hash(const TKey& k){
    return h(k);
}

unsigned ind_hash(const TKey& k){
    return h(k);
}

unsigned hash(const TKey& k, const size_t& i){
    return key_hash(k) ^ ind_hash(i);
};

CCA_sketch<TKey, TVol, 30, 30, hash> sk;

/*
inline void run(sketch<TKey, TVol> sk, std::basic_istream<item> st, unsigned n){
    for(int t = 0; t < n; ++t){
        item i; st.get(i);
        sk.update(i.key, i.volume);
    }
}
*/

int main(){

    std::basic_istream<item> st(NULL);

    // run(sk, st, 10000);

}