template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
dynamic_CCB_sketch<TKey, TVol, H>::dynamic_CCB_sketch(size_t d, size_t w) : dynamic_volume_table<TKey, TVol, H>(d, w), dynamic_cardinality_table<TKey, H>(d, w){}

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
inline void dynamic_CCB_sketch<TKey, TVol, H>::update(TKey key, TVol volume){
    dynamic_volume_table<TKey, TVol, H>::update(key, volume);
}

/*
template<typename TKey, typename TVol, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void CCA_sketch<TKey, TVol, D, W, H>::compute_cardinality_table(const std::set<TKey>* keys){
    cardinality_table<TKey, D, W, H>::compute_cardinality_table(keys);
}
*/

template<typename TKey, typename TVol, uint32_t (*H)(const TKey&, const size_t&)>
TVol dynamic_CCB_sketch<TKey, TVol, H>::query(TKey key){
    TVol s_num = 0.0, s_den = 0.0;
    for(size_t d = 0; d < dynamic_volume_table<TKey, TVol, H>::D; ++d){
        size_t w = H(key, d) % dynamic_volume_table<TKey, TVol, H>::W;
        uint32_t C_entry = dynamic_cardinality_table<TKey, H>::C[d][w];
        if(C_entry == 0){
            return 0.0;
        }else if(C_entry == 1){
            return dynamic_volume_table<TKey, TVol, H>::V[d][w];
        }
        TVol V_entry = dynamic_volume_table<TKey, TVol, H>::V[d][w];
        s_num = s_num + V_entry / (C_entry - 1);
        s_den = s_den + (dynamic_cardinality_table<TKey, H>::l0 - C_entry) / (C_entry - 1);
    }
    TVol num = prior<TVol>::mu * prior<TVol>::inv_chi + (dynamic_cardinality_table<TKey, H>::l0 - 1) * s_num - dynamic_volume_table<TKey, TVol, H>::D * dynamic_volume_table<TKey, TVol, H>::l1;
    TVol den = prior<TVol>::inv_chi + s_den;
    return num / den;
}