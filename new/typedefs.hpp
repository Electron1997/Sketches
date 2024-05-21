#ifndef TYPEDEFS_INCLUDED
#define TYPEDEFS_INCLUDED

#include <cstdint>
#include <string>

typedef uint32_t TKey;
typedef double TVol;

typedef struct{
    TKey key;
    TVol volume;
} item;

inline TKey to_TKey(const std::string& s){
    return std::stoi(s);
}

inline TVol to_TVol(const std::string& s){
    return std::stod(s);
}

inline uint32_t TKey_hash(TKey key){
    return key;
}

#endif