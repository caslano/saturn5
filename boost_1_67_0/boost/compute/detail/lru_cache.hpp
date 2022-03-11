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