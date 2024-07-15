#ifndef DYNAMIC_CCB_SKETCH_INCLUDED
#define DYNAMIC_CCB_SKETCH_INCLUDED

#include "dynamic_cardinality_table.hpp"
#include "dynamic_volume_table.hpp"
#include "prior.hpp"
#include "sketch_interface.hpp"

/**
 * Implementation of the CCB sketch described in https://netsec.ethz.ch/publications/papers/dadalt_bayesiansketching_2022.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @param d Number of arrays.
 * @param w Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
struct dynamic_CCB_sketch : public sketch<TKey, TVol>, public dynamic_volume_table<TKey, TVol, H>, public dynamic_cardinality_table<TKey, H>, public prior<TVol>{

    // uint32_t l0, C[D][W]; // Cardinality table
    // TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table
    // TVol mu = 0.0, chi = std::numeric_limits<TVol>::infinity(); // Prior

    dynamic_CCB_sketch(size_t d, size_t w);

    void update(TKey key, TVol volume);

    // void compute_cardinality_table(const std::set<TKey>* keys);

    TVol query(TKey key);

};

#include "dynamic_CCB_sketch.tpp"

#endif