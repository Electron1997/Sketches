#ifndef PRIOR_INCLUDED
#define PRIOR_INCLUDED

#include <cstdint>
#include <limits>

template<typename TVol>
struct prior{

    TVol mu = 0.0, chi = std::numeric_limits<TVol>::infinity(); // Prior

};

#endif