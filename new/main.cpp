#include "accuracy_tests/error_statistics.hpp"
#include "hashing/hash.hpp"
#include "typedefs.hpp"
#include "sketches/C_sketch.hpp"
#include "sketches/CM_sketch.hpp"
#include "sketches/CB_sketch.hpp"
#include "sketches/CCA_sketch.hpp"
#include "sketches/CCB_sketch.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <set>
#include <sstream>

// STREAM PROCESSING
constexpr size_t BUF_SIZE = 1e7;

item buf[BUF_SIZE];

// Instantiate sketches
constexpr size_t D = 30, W = 30; // Put this into typedefs/config file

CB_sketch<TKey, TVol, D, W, hash> cb_uninf, cb_with_prior;
CCA_sketch<TKey, TVol, D, W, hash> cca;
CCB_sketch<TKey, TVol, D, W, hash> ccb;

void load_trace(std::string path, item* buf = buf, size_t index = 0, size_t n = BUF_SIZE){
	std::fstream file; file.open(path, std::ios::in);
	std::string line, word;
    // TODO: Fix n
	while(index < n && getline(file, line)){
		std::stringstream s(line);
		getline(s, word, ',');  // Skip time
		getline(s, word, ',');
		buf[index].key = to_TKey(word);
		getline(s, word, ',');
		buf[index].volume = to_TVol(word);
        ++index;
	}
	file.close();
}

// Synthetic trace generation
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

inline item generate_item(){
    std::uniform_int_distribution<TKey> key(1, 5);
    std::normal_distribution<TVol> volume(0.0, 3.3);
    return {key(gen), volume(gen)};
}

void synthetic_trace(item (*synthetic_item)(), item* buf = buf, size_t index = 0, size_t n = BUF_SIZE){
    for(size_t i = index; i < index + n; ++i){
        buf[i] = synthetic_item();
    }
}

void run(sketch<TKey, TVol>& sk, item *buf, size_t n){
    for(size_t i = 0; i < n; ++i){
        item it = buf[i];
        sk.update(it.key, it.volume);
    }
}

std::map<TKey, unsigned> exact_volumes;

void compute_exact_volumes(item *buf, size_t n){
    exact_volumes.clear();
    for(size_t i = 0; i < n; ++i){
        exact_volumes[buf[i].key] += buf[i].volume;
    }
}

std::set<TKey>* compute_keyset(item *buf, size_t n){
    std::set<TKey>* keyset = new std::set<TKey>();
    for(size_t i = 0; i < n; ++i){
        keyset->emplace(buf[i].key);
    }
    return keyset;
}

TVol absolute_error(const TVol& ground_truth, const TVol& estimate){
    return fabs(ground_truth - estimate);
}

TVol relative_error(const TVol& ground_truth, const TVol& estimate){
    return absolute_error(ground_truth, estimate) / fabs(ground_truth);
}

/*
    Hyperloglog test
*/
#include "hyperloglog-hip/src/distinct_counter.h"

#include <chrono>
#include <random>

hyperloglog_hip::distinct_counter<int> h;

// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0,  RAND_MAX]
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void compute_prior(CB_sketch<TKey, TVol, D, W, hash>& cb, size_t n){
    hyperloglog_hip::distinct_counter<TKey> l0_estimator;
    for(size_t i = 0; i < n; ++i){
        l0_estimator.insert(buf[i].key);
    }
    cb.mu = cb.l1 / l0_estimator.count();
    cb.inv_chi = l0_estimator.count();
}

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

int main(){

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

    // Error statistics test
    size_t x; unsigned m; std::cin >> x >> m;
    test(x, m);
    std::cout << "-------------------------------------" << std::endl;

    // Synthetic trace test
    synthetic_trace(generate_item, buf, 0, 100);
    for(size_t i = 0; i < 100; ++i){
        std::cout << buf[i].key << " " << buf[i].volume << std::endl;
    }

    load_trace("data/kosarak.csv");

    /* 
    for(size_t i = 0; i < 10; ++i){
        std::cout << buf[i].key << " " << buf[i].volume << std::endl;
    }
    */
    size_t n = 8019015;
    run(cb_uninf, buf, n);
    run(cb_with_prior, buf, n);
    compute_exact_volumes(buf, n);
    compute_prior(cb_with_prior, n);

    std::cout << cb_uninf.mu << " " << cb_uninf.inv_chi << std::endl;
    std::cout << cb_with_prior.mu << " " << cb_with_prior.inv_chi << std::endl;

    /* // Print volume table
    for(size_t i = 0; i < 30; ++i){
        for(size_t j = 0; j < 30; ++j){
            std::cout << cb.V[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */

    int k = 0;
    double avg_rel_err_inf = 0.0, avg_rel_err_uninf = 0.0;
    TVol avg_abs_err_inf = 0.0, avg_abs_err_uninf = 0.0;

    std::cout << std::fixed << std::setprecision(10);
    for(auto p : exact_volumes){
        TVol estimate_uninf = cb_uninf.query(p.first);
        std::cout << "Uninformed Item " << p.first << " exact: " << p.second << " estimate: " << estimate_uninf << " relative error: " << relative_error(p.second, estimate_uninf) * 100 << "%" << std::endl;
        TVol estimate_inf = cb_with_prior.query(p.first);
        std::cout << "Informed Item " << p.first << " exact: " << p.second << " estimate: " << estimate_inf << " relative error: " << relative_error(p.second, estimate_inf) * 100 << "%" << std::endl;
        std::cout << std::endl;
        ++k;
        if(k == 100) break;
    }

}