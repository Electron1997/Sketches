#ifndef CARDINALITY_TABLE_INCLUDED
#define CARDINALITY_TABLE_INCLUDED

#include <cstdint>
#include <limits>
#include <set>

template<typename TKey, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct cardinality_table{

    uint32_t l0, C[D][W]; // Cardinality table

    void compute_cardinality_table(const std::set<TKey>* keys);

};

#include "cardinality_table.tpp"

#endif