template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CBL2_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        V[d][j] = V[d][j] + volume;
    }
}

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CBL2_sketch<TKey, TVol, D, W, H>::l2_estimate(){
    TVol s = 0.0;
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        s = s + volume_table<TKey, TVol, D, W, H>::V[d][j];
    }
    TVol num = prior<TVol>::mu * prior<TVol>::inv_chi + W * s - D * volume_table<TKey, TVol, D, W, H>::l1;
    TVol den = prior<TVol>::inv_chi + D * (W - 1);
    return num / den;

    return l2_est;
}