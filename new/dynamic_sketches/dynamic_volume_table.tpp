template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
dynamic_volume_table<TKey, TVol, H>::dynamic_volume_table(size_t d, size_t w) : D(d), W(w){
    V = std::vector(d, std::vector<TVol>(w, 0));
}

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
inline void dynamic_volume_table<TKey, TVol, H>::update(TKey key, TVol volume){
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        V[d][j] = V[d][j] + volume;
    }
    l1 = l1 + volume;
}