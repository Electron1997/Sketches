template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
dynamic_CB_sketch<TKey, TVol, H>::dynamic_CB_sketch(size_t d, size_t w) : dynamic_volume_table<TKey, TVol, H>(d, w){}

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
inline void dynamic_CB_sketch<TKey, TVol, H>::update(TKey key, TVol volume){
    dynamic_volume_table<TKey, TVol, H>::update(key, volume);
}

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
TVol dynamic_CB_sketch<TKey, TVol, H>::query(TKey key){
    TVol s = 0.0;
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        s = s + dynamic_volume_table<TKey, TVol, H>::V[d][j];
    }
    TVol num = prior<TVol>::mu * prior<TVol>::inv_chi + W * s - D * dynamic_volume_table<TKey, TVol, H>::l1;
    TVol den = prior<TVol>::inv_chi + D * (W - 1);
    return num / den;
}