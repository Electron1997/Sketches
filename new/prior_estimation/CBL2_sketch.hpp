#ifndef CML2_SKETCH_INCLUDED
#define CML2_SKETCH_INCLUDED

#include <algorithm>
#include <stdint.h>
#include <limits>

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
struct CBL2_sketch{

    TVol V[D][W] = {0};

    void update(TKey key, TVol volume);

    TVol l2_estimate();

};

#include "CBL2_sketch.tpp"

#endif