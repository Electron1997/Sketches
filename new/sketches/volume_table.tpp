template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void volume_table<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        V[d][j] = V[d][j] + volume;
    }
    l1 = l1 + volume;
}