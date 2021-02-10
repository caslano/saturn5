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
s4TVW1ts7+3bE7bN9nf3dxvsnIdSBMxNRDgW8bTB3vv6yT9m/OHBVuK3BhMJ44G9QnA4k4qpaJLc81gw/B1IT4RK+Iwr5gvlxXKMLzJkyUywiQwEa/X6n53uhwa7n0lvltF5jFKmZlEa+GzG7wSLhSfknSGz4HHCogkogL4vVQKaaSKj0AZ7wRIRz1VGhoTggYoYv+My4GOw4wmbJclCvdvZ8dI4gCY7fuSpHS83hT1L5mtafYY0c/7IokXCkoilSjQYrW+weeTLCX3CRHi4SMeBVLPGUiwwDP2dKGZKBEFGDlulUEYFwdzMWg1ayRaQXib0oaJQEbf7WTRfWQizZoQmaRyCHcyCdX4EwzdYGvoi1uu1IXIumZW1yX/gsqXsPotCSMVqTZc5bo2NuZKqwT45w8ve9ZB9ag4Gze7wM+tdsGb3c0bvo9M9R2xIcI2ZeFjEQkGKmMn5IpDCX2H+l2a6ZQ8vGfl0dAfrIR5GMpxE7IDV9lk3ukNc7x3WWC2QY1rEju3DXXu39OCKhykPQMa9ZN3mVdt6SmsbgZjA6IrFabidyLlg+e5sHaN1moT7udvru45r2WfsbzL0gtQX7D2tNYE3+82y1QJvHVZ7wmnk84Sz10+e11nretDJedX4VLDa1ilk5r5met52
*/