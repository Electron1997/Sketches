template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void AMS_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    for(size_t d = 0; d < D; ++d){
        size_t h = H(key, d);
        int s = (h >> 31) ? -1 : 1;
        size_t w = h % W;
        V[d][w] = V[d][w] + s * volume;
    }
}

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol AMS_sketch<TKey, TVol, D, W, H>::l2_estimate(){
    for(size_t d = 0; d < D; ++d){
        aux[d] = 0;
        for(size_t w = 0; w < W; ++w){
            aux[d] = aux[d] + V[d][w] * V[d][w];
        }
    }
    std::sort(aux, aux + D);
    size_t h = D / 2;
    return 0.5 * aux[h] + 0.5 * aux[D - 1 - h];
}