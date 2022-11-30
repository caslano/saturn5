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
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
*/