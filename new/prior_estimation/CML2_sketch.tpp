template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CML2_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    for(size_t d = 0; d < D; ++d){
        size_t j = H(key, d) % W;
        V[d][j] = V[d][j] + volume;
    }
}

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CML2_sketch<TKey, TVol, D, W, H>::l2_estimate(){
    TVol l2_est = std::numeric_limits<TVol>::max();
    for(size_t d = 0; d < D; ++d){
        TVol cand_l2 = 0.0;
        for(size_t w = 0; w < W; ++w){
            cand_l2 = cand_l2 + V[d][w] * V[d][w];
        }
        l2_est = std::min(l2_est, cand_l2);
    }

    return l2_est;
}