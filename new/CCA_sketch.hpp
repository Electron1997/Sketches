#ifndef CCA_SKETCH_INCLUDED
#define CCA_SKETCH_INCLUDED

#include "sketch_interface.hpp"
#include <stddef.h>

template<typename TKey, typename TVol, size_t D, size_t W, unsigned (*H)(const TKey&, const size_t&)>
struct CCA_sketch : public sketch<TKey, TVol>{

    unsigned l0, l1, C[D][W]; // Cardinality table
    TVol V[D][W] = {0}; // Volume table

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "CCA_sketch.tpp"

#endif