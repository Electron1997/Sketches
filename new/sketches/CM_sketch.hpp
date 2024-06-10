#ifndef CM_SKETCH_INCLUDED
#define CM_SKETCH_INCLUDED

#include "sketch_interface.hpp"
#include "volume_table.hpp"

#include <limits>

/**
 * Implementation of the Count-Min Sketch as described in https://web.archive.org/web/20230525144650/http://dimacs.rutgers.edu/~graham/pubs/papers/cm-full.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @tparam D Number of arrays.
 * @tparam W Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct CM_sketch : public sketch<TKey, TVol>, public volume_table<TKey, TVol, D, W, H>{

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "CM_sketch.tpp"

#endif