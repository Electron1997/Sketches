#include "../sketches/CB_sketch.hpp"
#include "hyperloglog-hip/src/distinct_counter.h"
#include "../typedefs.hpp"

// Ignoring alpha
void constant_CB_prior(CB_sketch<TKey, TVol, D, W, hash>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator){
    TVol l0_estimate = l0_estimator.count();
    cb.mu = cb.l1 / l0_estimate;
    cb.inv_chi = l0_estimate;
}