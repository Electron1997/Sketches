template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CM_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    volume_table<TKey, TVol, D, W, H>::update(key, volume);
}

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CM_sketch<TKey, TVol, D, W, H>::query(TKey key){
    TVol s = std::numeric_limits<TVol>::max();
    for(size_t d = 0; d < D; ++d){
        size_t w = H(key, d) % W;
        s = std::min(s, volume_table<TKey, TVol, D, W, H>::V[d][w]);
    }
    return s;
}