#include "../sketches/CB_sketch.hpp"
#include "hyperloglog-hip/src/distinct_counter.h"
#include "../typedefs.hpp"

// Ignoring alpha
void constant_CB_prior(CB_sketch<TKey, TVol, D, W, hash>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator){
    TVol l0_estimate = l0_estimator.count();
    cb.mu = cb.l1 / l0_estimate;
    cb.inv_chi = l0_estimate;
}

// Using alpha = mu
void unbiased_constant_CB_prior(CB_sketch<TKey, TVol, D, W, hash>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator, AMS_sketch<TKey, TVol, D, W, hash>& l2_estimator){
    TVol l0_estimate = l0_estimator.count();
    TVol l2_estimate = l2_estimator.l2_estimate(), var_estimate = l2_estimate / l0_estimate;    // var: sigma squared
    cb.mu = cb.l1 / l0_estimate;
    TVol bias = cb.mu / var_estimate * cb.mu;
    // std::cout << "BIAS " << bias <<  std::endl;
    cb.inv_chi = l0_estimate - bias;
}

void CB_prior(CB_sketch<TKey, TVol, D, W, hash>& cb);

