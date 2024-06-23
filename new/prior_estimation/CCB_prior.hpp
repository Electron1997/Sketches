#include "AMS_sketch.hpp"
#include "../sketches/CCB_sketch.hpp"
#include "hyperloglog-hip/src/distinct_counter.h"
#include "../typedefs.hpp"

// Ignoring alpha
void constant_CB_prior(CCB_sketch<TKey, TVol, D, W, hash>& ccb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator, AMS_sketch<TKey, TVol, D, W, hash>& l2_estimator){
    
    TVol l0_estimate = l0_estimator.count();
    TVol l2_estimate = l2_estimator.l2_estimate(), var_estimate = l2_estimate / l0_estimate;    // var: sigma squared
    ccb.mu = cb.l1 / l0_estimate;
    ccb.inv_chi = ((l0_estimate - 1) / (l0_estimate - 2) * l0_estimate - cb.l1 * cb.l1 / (l0_estimate - 2) / var;
}