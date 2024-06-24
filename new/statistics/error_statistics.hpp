/**
 * @file error_statistics.hpp
 * @brief Error statistics.
 */

#ifndef ERROR_STATISTICS_INCLUDED
#define ERROR_STATISTICS_INCLUDED

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

// TODO: add Pearson correlation and maybe some other metrics

// TODO: add variance and standard deviation estimates

template<typename T>
T absolute_error(const T& true_value, const T& estimate);

template<typename T>
T relative_error(const T& true_value, const T& estimate);

template<typename T>
T sum(const std::vector<T> values);

template<typename T>
T sum_of_squares(const std::vector<T> values);

// TODO: avoid copying vector
template<typename T>
T max(const std::vector<T> values);

template<typename T>
T min(const std::vector<T> values);

template<typename T>
T mean(std::vector<T> values);

template<typename T>
T median(std::vector<T> values);

template<typename T>
T mode(const std::vector<T> values);

template<typename T>
T percentile(std::vector<T> values);

template<typename T, T (*error)(const T&, const T&)>
std::vector<T> componentwise_errors(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the mean componentwise absolute difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex. TODO: add constraint on arguments.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Mean componentwise absolute error.
 * 
 **/
template<typename T>
T mean_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the mean componentwise relative error between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Mean componentwise relative error.
 * 
 **/
template<typename T>
T mean_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the mean componentwise squared difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Mean componentwise squared error.
 * 
 **/
template<typename T>
T mean_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the median componentwise absolute difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex. TODO: add constraint on arguments.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Median componentwise absolute error.
 * 
 **/
template<typename T>
T median_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the median componentwise relative error between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Median componentwise relative error.
 * 
 **/
template<typename T>
T median_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the median componentwise squared difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Median componentwise squared error.
 * 
 **/
template<typename T>
T median_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the mean componentwise absolute difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex. TODO: add constraint on arguments.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Mean componentwise absolute error.
 * 
 **/
template<typename T>
T max_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the maximum componentwise relative error between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Maximum componentwise relative error.
 * 
 **/
template<typename T>
T max_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the maximum componentwise squared difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return Maximum componentwise squared error.
 * 
 **/
template<typename T>
T max_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the 100p-th percentile componentwise absolute difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param p Percentile.
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return 100p-th percentile componentwise absolute error.
 * 
 **/
template<typename T>
T percentile_absolute_error(double p, const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the 100p-th percentile componentwise relative difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param p Percentile.
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return 100p-th percentile componentwise relative error.
 * 
 **/
template<typename T>
T percentile_relative_error(double p, const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the 100p-th percentile componentwise squared difference between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param p Percentile.
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return 100p-th percentile componentwise squared error.
 * 
 **/
template<typename T>
T percentile_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates);

/**
 * Returns the Pearson correlation coefficient between the values in \p true_values and the values in \p estimates .
 * Formally, this function computes \f$\frac{\sum_{i = 1}^n | u_i - v_i |}{n}\f$. TODO: fix latex.
 *
 * @tparam T Type.
 * 
 * @param true_values Vector of reference values.
 * @param estimates Vector of values to compare to reference values.
 * 
 * @return 100p-th percentile componentwise squared error.
 * 
 **/
template<typename T>
T pearson_correlation(const std::vector<T>& true_values, const std::vector<T>& estimates);

#include "error_statistics.tpp"

#endif