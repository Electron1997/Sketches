#ifndef DYNAMIC_CARDINALITY_TABLE_INCLUDED
#define DYNAMIC_CARDINALITY_TABLE_INCLUDED

#include <cstdint>
#include <limits>
#include <set>
#include <vector>

template<typename TKey, uint32_t (*H)(const TKey&, const size_t&)>
struct dynamic_cardinality_table{

    size_t D, W;

    uint32_t l0;

    std::vector<std::vector<TKey>> C;

    dynamic_cardinality_table(size_t d, size_t w);

    void compute_cardinality_table(const std::set<TKey>* keys);

};

#include "dynamic_cardinality_table.tpp"

#endif