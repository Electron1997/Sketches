/* // Hyperloglog test
    size_t n, m; std::cin >> n >> m;
    std::set<int> dist;
    for(size_t i = 0; i < m; ++i){
        int k = rng() % n;
        h.insert(k);
        dist.insert(k);
    }
    std::cout << "H " << h.count() << std::endl;
    std::cout << "S " << dist.size() << std::endl;
*/