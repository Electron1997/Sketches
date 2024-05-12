#ifndef SKETCH_INTERFACE_INCLUDED
#define SKETCH_INTERFACE_INCLUDED

template<typename TKey, typename TVol>
struct sketch{

    void update(TKey key, TVol vol);

    TVol query(TKey key);

};

#endif