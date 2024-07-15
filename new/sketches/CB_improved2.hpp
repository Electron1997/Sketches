#ifndef CB_IMPROVED2_INCLUDED
#define CB_IMPROVED2_INCLUDED

#include "../prior_estimation/AMS_sketch.hpp"
#include "../prior_estimation/hyperloglog-hip/src/distinct_counter.h"
#include "CB_sketch.hpp"

/**
 * Implementation of the CB Sketch described in https://netsec.ethz.ch/publications/papers/dadalt_bayesiansketching_2022.pdf.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * @tparam D Number of arrays.
 * @tparam W Counters per array.
 * @tparam H Hash function.
 * 
 **/
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
struct CB_improved_ineff : CB_sketch<TKey, TVol, D, W, H>{

    // TVol l1 = 0, V[D][W] = {0}; // Total volume, volume table
    // TVol mu = 0.0, chi = std::numeric_limits<TVol>::infinity(); // Prior

    hyperloglog_hip::distinct_counter<TKey> l0_estimator;
    AMS_sketch<TKey, TVol, D, W, H> l2_estimator;

    void update(TKey key, TVol volume);

    TVol query(TKey key);

};

#include "CB_improved2.tpp"

#endif