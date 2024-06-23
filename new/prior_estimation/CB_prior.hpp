#include "../sketches/CB_sketch.hpp"
#include "hyperloglog-hip/src/distinct_counter.h"
#include "../typedefs.hpp"

void constant_CB_prior(CB_sketch<TKey, TVol, D, W, hash>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator){
    cb.mu = cb.l1 / l0_estimator.count();
    cb.inv_chi = l0_estimator.count();
}