#ifndef CCA_SKETCH_INCLUDED
#define CCA_SKETCH_INCLUDED

#include "cardinality_table.hpp"
#include "sketch_interface.hpp"
#include "volume_table.hpp"

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct CCA_sketch : public sketch<TKey, TVol>, public volume_table<TKey, TVol, D, W, H>, public cardinality_table<TKey, D, W, H>{

    // uint32_t l0, C[D][W]; // Cardinality table
    // TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table

    void update(TKey key, TVol volume);

    // void compute_cardinality_table(const std::set<TKey>* keys);

    TVol query(TKey key);

};

#include "CCA_sketch.tpp"

#endif