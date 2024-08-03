template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CB_bootstrapCM<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    CB_sketch<TKey, TVol, D, W, H>::update(key, volume);
    l0_estimator.insert(key);
    l2_estimator.update(key, volume);
}

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CB_bootstrapCM<TKey, TVol, D, W, H>::query(TKey key){
    // CM query
    TVol CM_estimate = std::numeric_limits<TVol>::max();
    for(size_t d = 0; d < D; ++d){
        size_t w = H(key, d) % W;
        CM_estimate = std::min(CM_estimate, volume_table<TKey, TVol, D, W, H>::V[d][w]);
    }
    TVol l0_estimate = l0_estimator.count(), l2_estimate = l2_estimator.l2_estimate(), var_estimate = l2_estimate / l0_estimate;
    // std::cout << "ATTTTAAA " << l2_estimate << " " << volume_table<TKey, TVol, D, W, H>::l1 * volume_table<TKey, TVol, D, W, H>::l1 / sqrt(l0_estimate) << std::endl;
    TVol inv_chi = l0_estimate - CM_estimate * CM_estimate / var_estimate;
    TVol s = 0.0;
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        s = s + volume_table<TKey, TVol, D, W, H>::V[d][j];
    }
    TVol num = prior<TVol>::mu * inv_chi + W * s - D * volume_table<TKey, TVol, D, W, H>::l1;
    TVol den = inv_chi + D * (W - 1);
    TVol est = num / den;
    if(est > 0) return est;
    return 0;
}