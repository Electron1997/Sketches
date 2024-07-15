#ifndef DYNAMIC_VOLUME_TABLE_INCLUDED
#define DYNAMIC_VOLUME_TABLE_INCLUDED

#include <vector>

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
struct dynamic_volume_table{

    size_t D, W;

    TVol l1; // Total volume

    std::vector<std::vector<TVol>> V;

    dynamic_volume_table(size_t d, size_t w);

    void update(TKey key, TVol volume);

};

#include "dynamic_volume_table.tpp"

#endif