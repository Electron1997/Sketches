#ifndef CM_SKETCH_INCLUDED
#define CM_SKETCH_INCLUDED

#include "sketch_interface.hpp"
#include "volume_table.hpp"

#include <limits>

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct CM_sketch : public sketch<TKey, TVol>, public volume_table<TKey, TVol, D, W, H>{

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "CM_sketch.tpp"

#endif