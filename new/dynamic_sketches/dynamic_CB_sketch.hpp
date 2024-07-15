#ifndef DYNAMIC_CB_SKETCH_INCLUDED
#define DYNAMIC_CB_SKETCH_INCLUDED

#include "prior.hpp"
#include "sketch_interface.hpp"
#include "dynamic_volume_table.hpp"

/**
 * Implementation of the CB Sketch described in https://netsec.ethz.ch/publications/papers/dadalt_bayesiansketching_2022.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @param d Number of arrays.
 * @param w Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
struct dynamic_CB_sketch : public sketch<TKey, TVol>, public dynamic_volume_table<TKey, TVol, H>, public prior<TVol>{

    // TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table
    // TVol mu = 0.0, chi = std::numeric_limits<TVol>::infinity(); // Prior

    dynamic_CB_sketch(size_t d, size_t w);

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "dynamic_CB_sketch.tpp"

#endif