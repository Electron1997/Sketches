template<typename T>
inline T absolute_error(const T& true_value, const T& estimate){
    return fabs(true_value - estimate);
}

template<typename T>
inline T relative_error(const T& true_value, const T& estimate){
    return absolute_error<T>(true_value, estimate) / fabs(true_value);
}

template<typename T>
T squared_error(const T& true_value, const T& estimate){
    T ae = absolute_error(true_value, estimate);
    return ae * ae;
}

template<typename T>
T max(const std::vector<T> values){
    T mx = 0;   // TODO: make more general
    for(size_t i = 0; i < values.size(); ++i){
        if(values[i] > mx) mx = values[i];
    }
    return mx;
}

template<typename T>
T min(const std::vector<T> values){
    T mn = 1e100;   // TODO: make more general
    for(size_t i = 0; i < values.size(); ++i){
        if(values[i] < mn) mn = values[i];
    }
    return mn;
}

template<typename T>
T mean(std::vector<T> values){
    std::sort(values.begin(), values.end());
    T m = 0; size_t n = values.size();
    for(size_t i = 0; i < n; ++i){
        m += values[i] / n;
    }
    return m;
}

template<typename T>
T median(std::vector<T> values){
    std::sort(values.begin(), values.end());
    size_t n = values.size(), h = n / 2;
    return 0.5 * values[n - 1 - h] + 0.5 * values[h];
}

template<typename T>
T mode(const std::vector<T> values);

template<typename T, T (*error)(const T&, const T&)>
std::vector<T> componentwise_errors(const std::vector<T>& true_values, const std::vector<T>& estimates){
    assert(true_values.size() == estimates.size());
    size_t n = estimates.size();
    std::vector<T> errors(n);
    for(size_t i = 0; i < n; ++i){
        errors[i] = error(true_values[i], estimates[i]);
    }
    return errors;
}

template<typename T>
T mean_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return mean(componentwise_errors<T, absolute_error>(true_values, estimates));
}

template<typename T>
T mean_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return mean(componentwise_errors<T, relative_error>(true_values, estimates));
}

template<typename T>
T mean_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return mean(componentwise_errors<T, squared_error>(true_values, estimates));
}

template<typename T>
T median_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return median(componentwise_errors<T, absolute_error>(true_values, estimates));
}

template<typename T>
T median_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return median(componentwise_errors<T, relative_error>(true_values, estimates));
}

template<typename T>
T median_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return median(componentwise_errors<T, squared_error>(true_values, estimates));
}

template<typename T>
T max_absolute_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return max(componentwise_errors<T, absolute_error>(true_values, estimates));
}

template<typename T>
T max_relative_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return max(componentwise_errors<T, relative_error>(true_values, estimates));
}

template<typename T>
T max_squared_error(const std::vector<T>& true_values, const std::vector<T>& estimates){
    return max(componentwise_errors<T, squared_error>(true_values, estimates));
}