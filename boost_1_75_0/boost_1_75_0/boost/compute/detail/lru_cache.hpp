//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_LRU_CACHE_HPP
#define BOOST_COMPUTE_DETAIL_LRU_CACHE_HPP

#include <map>
#include <list>
#include <utility>

#include <boost/optional.hpp>

namespace boost {
namespace compute {
namespace detail {

// a cache which evicts the least recently used item when it is full
template<class Key, class Value>
class lru_cache
{
public:
    typedef Key key_type;
    typedef Value value_type;
    typedef std::list<key_type> list_type;
    typedef std::map<
                key_type,
                std::pair<value_type, typename list_type::iterator>
            > map_type;

    lru_cache(size_t capacity)
        : m_capacity(capacity)
    {
    }

    ~lru_cache()
    {
    }

    size_t size() const
    {
        return m_map.size();
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_map.empty();
    }

    bool contains(const key_type &key)
    {
        return m_map.find(key) != m_map.end();
    }

    void insert(const key_type &key, const value_type &value)
    {
        typename map_type::iterator i = m_map.find(key);
        if(i == m_map.end()){
            // insert item into the cache, but first check if it is full
            if(size() >= m_capacity){
                // cache is full, evict the least recently used item
                evict();
            }

            // insert the new item
            m_list.push_front(key);
            m_map[key] = std::make_pair(value, m_list.begin());
        }
    }

    boost::optional<value_type> get(const key_type &key)
    {
        // lookup value in the cache
        typename map_type::iterator i = m_map.find(key);
        if(i == m_map.end()){
            // value not in cache
            return boost::none;
        }

        // return the value, but first update its place in the most
        // recently used list
        typename list_type::iterator j = i->second.second;
        if(j != m_list.begin()){
            // move item to the front of the most recently used list
            m_list.erase(j);
            m_list.push_front(key);

            // update iterator in map
            j = m_list.begin();
            const value_type &value = i->second.first;
            m_map[key] = std::make_pair(value, j);

            // return the value
            return value;
        }
        else {
            // the item is already at the front of the most recently
            // used list so just return it
            return i->second.first;
        }
    }

    void clear()
    {
        m_map.clear();
        m_list.clear();
    }

private:
    void evict()
    {
        // evict item from the end of most recently used list
        typename list_type::iterator i = --m_list.end();
        m_map.erase(*i);
        m_list.erase(i);
    }

private:
    map_type m_map;
    list_type m_list;
    size_t m_capacity;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_LRU_CACHE_HPP

/* lru_cache.hpp
qleqRsR3/VXqFdlgD6NTCdnkx8V+OGVw02KRy0zh7EeIA2aKZ79+J5TPDWpsnBspZ5kfbcTk7NNWtsIsNn0vZX8WDZNHFVNNZc9VarWVlyJ1g25KZdTfb87pp5Qx30qOP6lyd7RXXiw/esi6PaSNAi1wU2sbe9JMpRYQBRzw86sPhw51y7qpqMJdeRVSHecmm4KfiQVJJjPzwBfSySnh0Svp8uve+qV0/XKhYZLGvEiWRqP4lXSSKw94IbUmSwJkZebQJ2luXPh6gGx5T6R5SRr3xzJ+9INlg0A3WME+RbpzV2OfMrSvSpmTWXx6q5dS08Gr1csP5e+r7h7zVp8qzl605HDVJS+saske6m4nO6pdslkVS77QW+WwIhNtV6oM5lz4pxYKhpiLevqvvDrS3bKzABLCu6NJ0e69cmcByPiL0a+QPv+qvVTO1Z2pSX40ztGsKESaSXaztDZujpaVCDegTgvZUzS7xq+lLf11z2upU/271PIPDQIPtay9yaYqhUx2Ro+3l0sfDX+7vfxDIdO9caHqbi3rpYZbRfZw0pH+EALd4CYfVXSqykOtPWCY8noF81uynmzuyguQPbmQUIGTDZfE74X0cWZuN9kTsodfyjxn6ZRO0kcHyFzHeXtkneiR9lI6X+lTzxyti9LJwq6t91K0mHPn2Nh21izqshvOruiv6TNbbiYo/uHZKylDFXtl7rizzV5+8DxH
*/