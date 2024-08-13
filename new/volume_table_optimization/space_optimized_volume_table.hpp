#ifndef OPTIMIZED_VOLUME_TABLE_INCLUDED
#define OPTIMIZED_VOLUME_TABLE_INCLUDED

#include <cstdint>

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct optimized_volume_table{

    TVol l1 = 0, V[D][W - 1] = {0}; // Total volume, volume table

    void update(TKey key, TVol volume);

};

#include "optimized_volume_table.tpp"

#endif