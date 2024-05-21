template<typename TKey, size_t D, size_t W, uint32_t (*H)(const TKey&, const size_t&)>
void cardinality_table<TKey, D, W, H>::compute_cardinality_table(const std::set<TKey>* keys){
    for(size_t d = 0; d < D; ++d){
        for(size_t w = 0; w < W; ++w){
            C[d][w] = 0;
        }
    }
    l0 = keys->size();
    for(TKey key : *keys){
        for(size_t d = 0; d < D; ++d){
            size_t w = H(key, d) % W;
            ++C[d][w];
        }
    }
}