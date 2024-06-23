#include <chrono>
#include <random>

// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0,  RAND_MAX]
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// Error statistics test
void test(size_t n = 10, unsigned m = 10){
    std::vector<float> u(n), v(n);
    for(size_t i = 0; i < n; ++i){
        u[i] = rng() % m;
        v[i] = rng() % m;
    }
    std::cout << "u ";
    for(size_t i = 0; i < n; ++i){
        std::cout << " " << u[i];
    }
    std::cout << std::endl;
    std::cout << "v ";
    for(size_t i = 0; i < n; ++i){
        std::cout << " " << v[i];
    }
    std::cout << std::endl;

    std::cout << "min u " << min<float>(u) << std::endl;
    std::cout << "max u " << max<float>(u) << std::endl;
    std::cout << "mean u " << mean<float>(u) << std::endl;
    std::cout << "median u " << median<float>(u) << std::endl;
    std::cout << "mean abs " << mean_absolute_error<float>(u, v) << std::endl;
    std::cout << "mean rel " << mean_relative_error<float>(u, v) << std::endl;
    std::cout << "mean sq " << mean_squared_error<float>(u, v) << std::endl;
    std::cout << "median abs " << median_absolute_error<float>(u, v) << std::endl;
    std::cout << "median rel " << median_relative_error<float>(u, v) << std::endl;
    std::cout << "median sq " << median_squared_error<float>(u, v) << std::endl;
    std::cout << "max abs " << max_absolute_error<float>(u, v) << std::endl;
    std::cout << "max rel " << max_relative_error<float>(u, v) << std::endl;
    std::cout << "max sq " << max_squared_error<float>(u, v) << std::endl;
}

    /* // Error statistics test
    size_t x; unsigned m; std::cin >> x >> m;
    test(x, m);
    std::cout << "-------------------------------------" << std::endl;
    */