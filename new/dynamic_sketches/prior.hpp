#ifndef PRIOR_INCLUDED
#define PRIOR_INCLUDED

#include <cstdint>
#include <limits>

template<typename TVol>
struct prior{

    TVol mu = 0.0, inv_chi = 0.0; // Prior

};

#endif