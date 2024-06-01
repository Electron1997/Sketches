#ifndef VOLUME_TABLE_INCLUDED
#define VOLUME_TABLE_INCLUDED

#include <cstdint>

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct volume_table{

    TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table

    void update(TKey key, TVol volume);

    void combine(const volume_table<TKey, TVol, D, W, H>& other);

};

#include "volume_table.tpp"

#endif