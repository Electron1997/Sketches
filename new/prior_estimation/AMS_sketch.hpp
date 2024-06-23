#ifndef AMS_SKETCH_INCLUDED
#define AMS_SKETCH_INCLUDED

#include <algorithm>

/**
 * Implementation of the AMS Sketch described in https://www.dimacs.rutgers.edu/~graham/pubs/papers/encalgs-ams.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @tparam D Number of arrays.
 * @tparam W Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct AMS_sketch{

    TVol V[D][W] = {0}, aux[D];

    void update(TKey key, TVol volume);

    TVol l2_estimate();

};

#include "AMS_sketch.tpp"

#endif