#include "../prior_estimation/AMS_sketch.hpp"
#include "../typedefs.hpp"

TVol test_AMS_sketch(item *buf, size_t n){
    AMS_sketch<TKey, TVol, D, W, hash> ams;
    for(size_t i = 0; i < n; ++i){
        ams.update(buf[i].key, buf[i].volume);
    }
    return ams.l2_estimate();
}

// Synthetic trace test
// TKey l, r; TVol mu, sigma; std::cin >> l >> r >> mu >> sigma;
load_synthetic_trace([](){
                            return uniform_normal_item(0, 10, 0.0, 5.0);
                        }, buf, 0, 100);
for(size_t i = 0; i < 100; ++i){
    std::cout << buf[i].key << " " << buf[i].volume << std::endl;
}

auto keys = compute_keyset(buf, 100);
compute_exact_volumes(buf, 100);

std::vector<TVol> u(keys->size()), v(keys->size(), 0);
size_t i = 0;
for(std::pair<TKey, TVol> p : exact_volumes){
    u[i] = p.second;
    ++i;
}

std::cout << "Exact " << mean_squared_error(u, v) << std::endl;
std::cout << "AMS " << test_AMS_sketch(buf, 100) / keys->size() << std::endl;