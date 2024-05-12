template<typename TKey, typename TVol, size_t D, size_t W, unsigned (*H)(const TKey&, const size_t&)>
inline void CCA_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    // TODO: factor out basic update
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        V[d][j] = V[d][j] + volume;
    }
}

template<typename TKey, typename TVol, size_t D, size_t W, unsigned (*H)(const TKey&, const size_t&)>
inline TVol CCA_sketch<TKey, TVol, D, W, H>::query(TKey key){
    TVol s = 0.0;
    for(int d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        s = s + V[d][j] / C[d][j];
    }
    TVol num = (l0 + W - 1) * s - D * l1;
    return num / D / (W - 1);
}