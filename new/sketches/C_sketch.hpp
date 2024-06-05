#ifndef C_SKETCH_INCLUDED
#define C_SKETCH_INCLUDED

#include "sketch_interface.hpp"

#include <algorithm>

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct C_sketch : public sketch<TKey, TVol>{

    TVol V[D][W] = {0}, aux[D];

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "C_sketch.tpp"

#endif