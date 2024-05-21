#ifndef SKETCH_INTERFACE_INCLUDED
#define SKETCH_INTERFACE_INCLUDED

template<typename TKey, typename TVol>
struct sketch{

    virtual ~sketch() {}

    virtual void update(TKey key, TVol vol) = 0;

    virtual TVol query(TKey key) = 0;

};

#endif