#include "hashing/hash.hpp"
#include "typedefs.hpp"
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
constexpr size_t BUF_SIZE = 1e6;

item buf[BUF_SIZE];

CCA_sketch<TKey, TVol, 30, 30, hash> sk;

void load_trace(std::string path, item* buf = buf, size_t index = 0, size_t n = BUF_SIZE){
	std::fstream file; file.open(path, std::ios::in);
	std::string line, word;
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

int main(){

    load_trace("data/kosarak.csv");

    /*
    for(size_t i = 0; i < 10; ++i){
        std::cout << buf[i].key << " " << buf[i].volume << std::endl;
    }
    */
    size_t n = 10000;
    run(sk, buf, n);
    compute_exact_volumes(buf, n);

    sk.compute_cardinality_table(compute_keyset(buf, n));
    for(size_t i = 0; i < 30; ++i){
        for(size_t j = 0; j < 30; ++j){
            std::cout << sk.C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int k = 0;
    std::cout << std::fixed << std::setprecision(10);
    for(auto p : exact_volumes){
        TVol estimate = sk.query(p.first);
        std::cout << "Item " << p.first << " exact: " << p.second << " estimate: " << estimate << " relative error: " << relative_error(p.second, estimate) * 100 << "%" << std::endl;
        ++k;
        if(k == 100) break;
    }

}