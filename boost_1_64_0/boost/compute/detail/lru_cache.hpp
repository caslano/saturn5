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
mJL+mn2LKNBhwcrX7RFEhWPifXshcUCLBavf0A4NFqx9055pNJmQ+pa+KdAjNvCYEsckvx0OtqgwYek74WCHChPS3/WYOnPWhvanokPke56/FBkS/77HFBmS/IH9dyhxTOrYnk1UmZL6occcMSTxI7FRZEjqx65zxDHJkcdUmbD0E7FRZkDsp9YbGeqMSf5MmxwxJDH2mAIdFiz/XA6oMGH5F/qhwojkL42LPF2iE48pMiT5K+OkSJfIr8VBlgZTln6jTcoMiU+1QZ4uod+aS3YpMyD6O+1w5o/+RlU2WLD+e/XoE5tZNxToEfuD8VFgQPyPcvSXUHCgbDEj/Sfj9Xv9lrLMMam5MRD9s725OKRD7S/iZ/uv8s6UpYU2mZH6m3oU6RL83RohQ/QLrrHzWXWpNV3/mHF+VJwfljev7ZUPWFcsf1BMFOiwoF4X8/vl8X36rbnOXar64pjUu/zcpMqEpXfrixJdFiy9R37Is/4O6+Bt2nmLOm8Qp/63C9bEy0/ay0/+SL7CHDDl1CvdmxcHI2IvDfvekbE9T//Kw0d4nnGO83uUGLJ92/P4Nw2082LPYfdWmJI8MIfqbSvrhNUNni8fytPKAscsv0DMLD9R/5ToE32SmNijzpjkvhxToEvoycbFHlUmpJ/iHgp0CT9VzBzQZcFaRrzUGJF4mnVEkS6hp+ubLA0WrD5DP9SZsZbVBhXGLD3TderMWXuW64zZfLa26RPNiYcsNSYknqN/DmkTPFd9Dth5vPm8hO9VK6N7zrNNgQ5zznmC9h+nrR3xbpsHed9hS67HRLfUI0OH+IPEej95urf476n9u5vLO5mPa7u2bN1xQJMFp64jXtrMWbqusVFjxur1vC5TY0R8xRyTo8Wc1eu7hzoTkjfwXOeAJlNSN5Qr8jQZc86quKnQJ7iRtcImBzS5y431RYMR8ZtY/+xRokewph5nydNiSuKmYiVDlWOiN3OOA+pMWLm59qgyI3XKY47oE7mFWFm5ltxf3WsNM9avYa4YsbIkj/QIribeq+rnyvqmy+7VT/q9RQzUb+q/QV9OHWIX8veA8oD8zexxpRyzffPzBonLGz/rrzxprwV5PuW68pjNa2ojqf9b2kdPuUmOysP1o7zLjU4Gx8rB9U4GkSvoi00K/kY6VDYYEbuiHKycN1hXrn/xZLCvLHP6+v5dEOWoe9Ken/JLy7lNZe7L3sNSNikn/R6vTKS4wnmDuyhzFBw3lBNyS9pKWLOJk/YBENtlTwaL9ZNB4TYng2WPN9m9lD4vKedkz28dnsvasmf76I/nDfZ+c96gTeNX5w2mJH9+3mCX2s/s7zy2zxI5e2r1Sf34vMEOLaIjx589b1CiT/hzfgdnnxpjUh1jokiX0OfdQ4YWC1a+oB0qHJP4onGSo8mcla7XYI7oEf3SeYNzyNFkxvKXtUOZY5JfOW+wQYEe4Z6+ydBgSvqrfr5RpEf0a+aKLA1mrHzdmKgyIt73dwh5ekS/oQ4ZqtzlXSeC9DfFQpUJyW95f5cKU5YGjpmw9G33UmHM9nfUY0z6u3JLdGi8HDCMh4LQ98wbFTb/EfKZcPd+37xRZ07q3CeCyRt8TvEH4kt4H/v9J4KK4zHLx+6lwZTVH2qPOvW2efqMMTL4sHY/YmzEP2RsH7AmiL5Hbt6p3ar9MQm/Q67Zebu+K/4tgDfJK02mpN7svjfquySXbL5e7Edy8jLjy3t8qK8XiOHyJ4O5cuWF8vL88wanCT1PLKw817p6stzsWUuc9t8BE0/QxrdOBnvK/OPNB5E9dUP+oajH6pc9SixIP876eLhjzjxCDASPNC7KTFnfsR6Ycs6j1GXG6Udbf0xZfYy1R5M=
*/