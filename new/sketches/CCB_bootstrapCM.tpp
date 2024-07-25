template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CCB_bootstrapCM<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    CCB_sketch<TKey, TVol, D, W, H>::update(key, volume);
    l0_estimator.insert(key);
    l2_estimator.update(key, volume);
}

// TODO: optimize

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CCB_bootstrapCM<TKey, TVol, D, W, H>::query(TKey key){
    // CM query
    TVol old_estimate = std::numeric_limits<TVol>::max();
    for(size_t d = 0; d < D; ++d){
        size_t w = H(key, d) % W;
        old_estimate = std::min(old_estimate, volume_table<TKey, TVol, D, W, H>::V[d][w]);
    }
    TVol l0_estimate = l0_estimator.count(), l2_estimate = l2_estimator.l2_estimate(), var_estimate = l2_estimate / l0_estimate;
    TVol inv_chi = l0_estimate - old_estimate * old_estimate / var_estimate;
    TVol s_num = 0.0, s_den = 0.0;
    for(size_t d = 0; d < D; ++d){
        size_t w = H(key, d) % W;
        uint32_t C_entry = cardinality_table<TKey, D, W, H>::C[d][w];
        if(C_entry == 0){
            return 0.0;
        }else if(C_entry == 1){
            return volume_table<TKey, TVol, D, W, H>::V[d][w];
        }
        TVol V_entry = volume_table<TKey, TVol, D, W, H>::V[d][w];
        s_num = s_num + V_entry / (C_entry - 1);
        s_den = s_den + (cardinality_table<TKey, D, W, H>::l0 - C_entry) / (C_entry - 1);
    }
    TVol num = prior<TVol>::mu * prior<TVol>::inv_chi + (cardinality_table<TKey, D, W, H>::l0 - 1) * s_num - D * volume_table<TKey, TVol, D, W, H>::l1;
    TVol den = prior<TVol>::inv_chi + s_den;
    return num / den;
}