template<typename TKey, uint32_t (*H)(const TKey&, const size_t&)>
dynamic_cardinality_table<TKey, H>::dynamic_cardinality_table(size_t d, size_t w) : D(d), W(w){
    C = std::vector(d, std::vector<TKey>(w));
}

template<typename TKey, uint32_t (*H)(const TKey&, const size_t&)>
void dynamic_cardinality_table<TKey, H>::compute_cardinality_table(const std::set<TKey>* keys){
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