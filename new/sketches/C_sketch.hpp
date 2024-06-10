#ifndef C_SKETCH_INCLUDED
#define C_SKETCH_INCLUDED

#include "sketch_interface.hpp"

#include <algorithm>

/**
 * Implementation of the Count Sketch described in https://www.cs.princeton.edu/courses/archive/spr04/cos598B/bib/CharikarCF.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @tparam D Number of arrays.
 * @tparam W Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct C_sketch : public sketch<TKey, TVol>{

    TVol V[D][W] = {0}, aux[D];

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "C_sketch.tpp"

#endif