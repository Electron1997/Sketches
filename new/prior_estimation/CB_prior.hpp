#include "../sketches/CB_sketch.hpp"
#include "hyperloglog-hip/src/distinct_counter.h"

// Ignoring alpha
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void constant_CB_prior(CB_sketch<TKey, TVol, D, W, H>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator){
    TVol l0_estimate = l0_estimator.count();
    cb.mu = cb.l1 / l0_estimate;
    cb.inv_chi = l0_estimate;
}

// Using alpha = mu
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void unbiased_constant_CB_prior(CB_sketch<TKey, TVol, D, W, H>& cb, hyperloglog_hip::distinct_counter<TKey>& l0_estimator, AMS_sketch<TKey, TVol, D, W, H>& l2_estimator){
    TVol l0_estimate = l0_estimator.count();
    TVol l2_estimate = l2_estimator.l2_estimate(), var_estimate = l2_estimate / l0_estimate;    // var: sigma squared
    cb.mu = cb.l1 / l0_estimate;
    TVol bias = cb.mu / var_estimate * cb.mu;
    // std::cout << "BIAS " << bias <<  std::endl;
    cb.inv_chi = l0_estimate - bias;
}

