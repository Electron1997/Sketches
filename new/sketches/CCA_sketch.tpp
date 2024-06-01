template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CCA_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    volume_table<TKey, TVol, D, W, H>::update(key, volume);
}

/*
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void CCA_sketch<TKey, TVol, D, W, H>::compute_cardinality_table(const std::set<TKey>* keys){
    cardinality_table<TKey, D, W, H>::compute_cardinality_table(keys);
}
*/

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CCA_sketch<TKey, TVol, D, W, H>::query(TKey key){
    TVol s = 0.0;
    for(size_t d = 0; d < D; ++d){
        size_t w = H(key, d) % W;
        if(cardinality_table<TKey, D, W, H>::C[d][w] == 0){
            return 0.0;
        }
        s = s + volume_table<TKey, TVol, D, W, H>::V[d][w] / cardinality_table<TKey, D, W, H>::C[d][w];
    }
    TVol num = (cardinality_table<TKey, D, W, H>::l0 + W - 1) * s - D * volume_table<TKey, TVol, D, W, H>::l1;
    TVol den = D * (W - 1);
    return num / den;
}