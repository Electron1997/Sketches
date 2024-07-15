#ifndef SKETCH_INTERFACE_INCLUDED
#define SKETCH_INTERFACE_INCLUDED

/**
 * Abstract sketch interface. A sketch data structure must implement a per-item update operation and a query operation.
 *
 * @tparam TKey Key type.
 * @tparam TVol Volume type.
 * 
 **/
template<typename TKey, typename TVol>
struct sketch{

    virtual ~sketch() {}

    /**
     * Updates the sketch data structure for item (key, value) appearing in the stream.
     *
     * @param key Item key.
     * @param vol Item volume.
     * 
     **/
    virtual void update(TKey key, TVol vol) = 0;

    /**
     * Returns total volume estimate for key \p key in processed stream.
     *
     * @param key Key.
     * @return Volume estimate for \p key.
     * 
     **/
    virtual TVol query(TKey key) = 0;

};

#endif