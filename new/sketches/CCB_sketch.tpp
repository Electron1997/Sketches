template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
inline void CCB_sketch<TKey, TVol, D, W, H>::update(TKey key, TVol volume){
    volume_table<TKey, TVol, D, W, H>::update(key, volume);
}

/*
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void CCA_sketch<TKey, TVol, D, W, H>::compute_cardinality_table(const std::set<TKey>* keys){
    cardinality_table<TKey, D, W, H>::compute_cardinality_table(keys);
}
*/

template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
TVol CCB_sketch<TKey, TVol, D, W, H>::query(TKey key){
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