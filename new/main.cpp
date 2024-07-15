#include "data/synthetic_trace.hpp"
#include "hashing/hash.hpp"
#include "prior_estimation/AMS_sketch.hpp"
#include "prior_estimation/CB_prior.hpp"
#include "prior_estimation/CCB_prior.hpp"
#include "typedefs.hpp"
#include "sketches/C_sketch.hpp"
#include "sketches/CM_sketch.hpp"
#include "sketches/CB_improved.hpp"
#include "sketches/CB_sketch.hpp"
#include "sketches/CCA_sketch.hpp"
#include "sketches/CCB_sketch.hpp"
#include "sketches/CCB_improved.hpp"
#include "statistics/error_statistics.hpp"

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
CB_sketch<TKey, TVol, D, W, hash> cb_uninf, cb_with_prior, cb_unbiased_prior;
CB_improved<TKey, TVol, D, W, hash> cb_imp;
CCA_sketch<TKey, TVol, D, W, hash> cca;
CCB_sketch<TKey, TVol, D, W, hash> ccb_uninf, ccb_with_prior;
CCB_improved<TKey, TVol, D, W, hash> ccb_imp;

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

void run(sketch<TKey, TVol>& sk, item *buf, size_t n){
    for(size_t i = 0; i < n; ++i){
        item it = buf[i];
        sk.update(it.key, it.volume);
    }
}

// TODO: find a better solution for this
std::map<TKey, TVol> exact_volumes;

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

// Inefficient
template<TVol (*error_statistic)(const std::vector<TVol>&, const std::vector<TVol>&)>
TVol compute_error_statistic(std::map<TKey, TVol>& exact_volumes, sketch<TKey, TVol>& sketch){
    size_t n = exact_volumes.size();
    std::vector<TVol> values(n), estimates(n);
    size_t i = 0;
    for(std::pair<TKey, TVol> p : exact_volumes){
        values[i] = p.second;
        estimates[i] = sketch.query(p.first);
        ++i;
    }
    return error_statistic(values, estimates);
}

template<TVol (*error_statistic)(const std::vector<TVol>&, const std::vector<TVol>&)>
TVol compare_error_statistic(std::map<TKey, TVol>& exact_volumes, sketch<TKey, TVol>& sketch1, sketch<TKey, TVol>& sketch2){
    return compute_error_statistic<error_statistic>(exact_volumes, sketch1) - compute_error_statistic<error_statistic>(exact_volumes, sketch2);
}

// Inefficient
template<TVol (*error_statistic)(double, const std::vector<TVol>&, const std::vector<TVol>&)>
TVol compute_percentile_error_statistic(double x, std::map<TKey, TVol>& exact_volumes, sketch<TKey, TVol>& sketch){
    size_t n = exact_volumes.size();
    std::vector<TVol> values(n), estimates(n);
    size_t i = 0;
    for(std::pair<TKey, TVol> p : exact_volumes){
        values[i] = p.second;
        estimates[i] = sketch.query(p.first);
        ++i;
    }
    return error_statistic(x, values, estimates);
}

template<TVol (*error_statistic)(double, const std::vector<TVol>&, const std::vector<TVol>&)>
TVol compare_percentile_error_statistic(double x, std::map<TKey, TVol>& exact_volumes, sketch<TKey, TVol>& sketch1, sketch<TKey, TVol>& sketch2){
    return compute_percentile_error_statistic<error_statistic>(x, exact_volumes, sketch1) - compute_percentile_error_statistic<error_statistic>(x, exact_volumes, sketch2);
}

// Inefficient
void print_statistics(sketch<TKey, TVol>& sketch){
    std::cout << "Mean Absolute " << compute_error_statistic<mean_absolute_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Mean Relative " << compute_error_statistic<mean_relative_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Mean Squared " << compute_error_statistic<mean_squared_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Median Absolute " << compute_error_statistic<median_absolute_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Median Relative " << compute_error_statistic<median_relative_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Median Squared " << compute_error_statistic<median_squared_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Max Absolute " << compute_error_statistic<max_absolute_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Max Relative " << compute_error_statistic<max_relative_error<TVol>>(exact_volumes, sketch) << std::endl;
    std::cout << "Max Squared " << compute_error_statistic<max_squared_error<TVol>>(exact_volumes, sketch) << std::endl;
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Absolute " << compute_percentile_error_statistic<percentile_absolute_error<TVol>>(p, exact_volumes, sketch) << std::endl;
    }
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Relative " << compute_percentile_error_statistic<percentile_relative_error<TVol>>(p, exact_volumes, sketch) << std::endl;
    }
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Squared " << compute_percentile_error_statistic<percentile_squared_error<TVol>>(p, exact_volumes, sketch) << std::endl;
    }
    std::cout << "Pearson Correlation " << compute_error_statistic<pearson_correlation<TVol>>(exact_volumes, sketch) << std::endl;
}

void print_statistics_comparison(sketch<TKey, TVol>& sketch1, sketch<TKey, TVol>& sketch2){
    std::cout << "Mean Absolute " << compare_error_statistic<mean_absolute_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Mean Relative " << compare_error_statistic<mean_relative_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Mean Squared " << compare_error_statistic<mean_squared_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Median Absolute " << compare_error_statistic<median_absolute_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Median Relative " << compare_error_statistic<median_relative_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Median Squared " << compare_error_statistic<median_squared_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Max Absolute " << compare_error_statistic<max_absolute_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Max Relative " << compare_error_statistic<max_relative_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    std::cout << "Max Squared " << compare_error_statistic<max_squared_error<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Absolute " << compare_percentile_error_statistic<percentile_absolute_error<TVol>>(p, exact_volumes, sketch1, sketch2) << std::endl;
    }
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Relative " << compare_percentile_error_statistic<percentile_relative_error<TVol>>(p, exact_volumes, sketch1, sketch2) << std::endl;
    }
    for(double p = 0.0; p <= 1.05; p += 0.25){
        std::cout << p * 100 << "th Percentile Squared " << compare_percentile_error_statistic<percentile_squared_error<TVol>>(p, exact_volumes, sketch1, sketch2) << std::endl;
    }
    std::cout << "Pearson Correlation " << compare_error_statistic<pearson_correlation<TVol>>(exact_volumes, sketch1, sketch2) << std::endl;
}

int main(){

    // size_t n = 8019015;
    size_t n = 100000;

    load_trace("data/kosarak.csv");
    /* load_synthetic_trace([](){
                            return uniform_normal_item(0, 10000, 0.0, 1.0);
                        }, buf, 0, n); */

    /* 
    for(size_t i = 0; i < 10; ++i){
        std::cout << buf[i].key << " " << buf[i].volume << std::endl;
    }
    */
    
    run(cb_uninf, buf, n);
    run(cb_with_prior, buf, n);
    run(cb_unbiased_prior, buf, n);
    run(cb_imp, buf, n);
    run(ccb_uninf, buf, n);
    run(ccb_with_prior, buf, n);
    run(ccb_imp, buf, n);
    compute_exact_volumes(buf, n);

    hyperloglog_hip::distinct_counter<TKey> l0_estimator;
    for(size_t i = 0; i < n; ++i){
        l0_estimator.insert(buf[i].key);
    }

    AMS_sketch<TKey, TVol, D, W, hash> l2_estimator;
    for(size_t i = 0; i < n; ++i){
        l2_estimator.update(buf[i].key, buf[i].volume);
    }

    constant_CB_prior(cb_with_prior, l0_estimator);
    unbiased_constant_CB_prior(cb_unbiased_prior, l0_estimator, l2_estimator);
    constant_CCB_prior(ccb_with_prior, l0_estimator, l2_estimator);
    unbiased_constant_CB_prior(cb_imp, l0_estimator, l2_estimator);
    constant_CCB_prior(ccb_imp, l0_estimator, l2_estimator);

    auto keys = compute_keyset(buf, n);
    ccb_uninf.compute_cardinality_table(keys);
    ccb_with_prior.compute_cardinality_table(keys);

    std::cout << "CB uninf " << cb_uninf.mu << " " << cb_uninf.inv_chi << std::endl;
    std::cout << "CB const prior " << cb_with_prior.mu << " " << cb_with_prior.inv_chi << std::endl;
    std::cout << "CB unbiased prior " << cb_unbiased_prior.mu << " " << cb_unbiased_prior.inv_chi << std::endl;

    std::cout << "CCB uninf " << ccb_uninf.mu << " " << ccb_uninf.inv_chi << std::endl;
    std::cout << "CCB const prior " << ccb_with_prior.mu << " " << ccb_with_prior.inv_chi << std::endl;

    /* // Print volume table
    for(size_t i = 0; i < 30; ++i){
        for(size_t j = 0; j < 30; ++j){
            std::cout << cb.V[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */

    int k = 0;

    std::cout << std::fixed << std::setprecision(10);
    /*
    for(auto p : exact_volumes){
        TVol estimate_uninf = ccb_uninf.query(p.first);
        std::cout << "Uninformed Item " << p.first << " exact: " << p.second << " estimate: " << estimate_uninf << " relative error: " << relative_error<TVol>(p.second, estimate_uninf) * 100 << "%" << std::endl;
        TVol estimate_inf = ccb_with_prior.query(p.first);
        std::cout << "Informed Item " << p.first << " exact: " << p.second << " estimate: " << estimate_inf << " relative error: " << relative_error<TVol>(p.second, estimate_inf) * 100 << "%" << std::endl;
        std::cout << std::endl;
        ++k;
        if(k == 100) break;
    }
    */

    std::cout << "CCB Uninformed" << std::endl;
    print_statistics(ccb_uninf);

    std::cout << std::endl << "CCB With prior" << std::endl;
    print_statistics(ccb_with_prior);

    std::cout << "CB Uninformed" << std::endl;
    print_statistics(cb_uninf);

    std::cout << std::endl << "CB With prior" << std::endl;
    print_statistics(cb_with_prior);

    std::cout << std::endl << "CB Unbiased prior" << std::endl;
    print_statistics(cb_unbiased_prior);

    std::cout << std::endl << "CB Improved" << std::endl;
    print_statistics(cb_imp);

    print_statistics_comparison(cb_with_prior, cb_imp);

}