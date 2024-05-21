#ifndef CB_SKETCH_INCLUDED
#define CB_SKETCH_INCLUDED

#include "prior.hpp"
#include "sketch_interface.hpp"
#include "volume_table.hpp"

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct CB_sketch : public sketch<TKey, TVol>, public volume_table<TKey, TVol, D, W, H>, public prior<TVol>{

    // TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table
    // TVol mu = 0.0, chi = std::numeric_limits<TVol>::infinity(); // Prior

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "CB_sketch.tpp"

#endif