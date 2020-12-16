//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//
//
// Revision History:
//   13 June 2001: Changed some names for clarity. (Jeremy Siek)
//   01 April 2001: Modified to use new <boost/limits.hpp> header. (JMaddock)
//
#ifndef BOOST_GRAPH_DETAIL_BUCKET_SORTER_HPP
#define BOOST_GRAPH_DETAIL_BUCKET_SORTER_HPP

#include <vector>
#include <cassert>
#include <boost/limits.hpp>
#include <boost/concept/assert.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost
{

template < class BucketType, class ValueType, class Bucket,
    class ValueIndexMap >
class bucket_sorter
{
    BOOST_CONCEPT_ASSERT(
        (ReadablePropertyMapConcept< ValueIndexMap, ValueType >));

public:
    typedef BucketType bucket_type;
    typedef ValueType value_type;
    typedef typename std::vector< value_type >::size_type size_type;

    bucket_sorter(size_type _length, bucket_type _max_bucket,
        const Bucket& _bucket = Bucket(),
        const ValueIndexMap& _id = ValueIndexMap())
    : head(_max_bucket, invalid_value())
    , next(_length, invalid_value())
    , prev(_length, invalid_value())
    , id_to_value(_length)
    , bucket(_bucket)
    , id(_id)
    {
    }

    void remove(const value_type& x)
    {
        const size_type i = get(id, x);
        const size_type& next_node = next[i];
        const size_type& prev_node = prev[i];

        // check if i is the end of the bucket list
        if (next_node != invalid_value())
            prev[next_node] = prev_node;
        // check if i is the begin of the bucket list
        if (prev_node != invalid_value())
            next[prev_node] = next_node;
        else // need update head of current bucket list
            head[bucket[x]] = next_node;
    }

    void push(const value_type& x)
    {
        id_to_value[get(id, x)] = x;
        (*this)[bucket[x]].push(x);
    }

    void update(const value_type& x)
    {
        remove(x);
        (*this)[bucket[x]].push(x);
    }
    //  private:
    //    with KCC, the nested stack class is having access problems
    //    despite the friend decl.
    static size_type invalid_value()
    {
        return (std::numeric_limits< size_type >::max)();
    }

    typedef typename std::vector< size_type >::iterator Iter;
    typedef typename std::vector< value_type >::iterator IndexValueMap;

public:
    friend class stack;

    class stack
    {
    public:
        stack(bucket_type _bucket_id, Iter h, Iter n, Iter p, IndexValueMap v,
            const ValueIndexMap& _id)
        : bucket_id(_bucket_id), head(h), next(n), prev(p), value(v), id(_id)
        {
        }

        // Avoid using default arg for ValueIndexMap so that the default
        // constructor of the ValueIndexMap is not required if not used.
        stack(bucket_type _bucket_id, Iter h, Iter n, Iter p, IndexValueMap v)
        : bucket_id(_bucket_id), head(h), next(n), prev(p), value(v)
        {
        }

        void push(const value_type& x)
        {
            const size_type new_head = get(id, x);
            const size_type current = head[bucket_id];
            if (current != invalid_value())
                prev[current] = new_head;
            prev[new_head] = invalid_value();
            next[new_head] = current;
            head[bucket_id] = new_head;
        }
        void pop()
        {
            size_type current = head[bucket_id];
            size_type next_node = next[current];
            head[bucket_id] = next_node;
            if (next_node != invalid_value())
                prev[next_node] = invalid_value();
        }
        value_type& top() { return value[head[bucket_id]]; }
        const value_type& top() const { return value[head[bucket_id]]; }
        bool empty() const { return head[bucket_id] == invalid_value(); }

    private:
        bucket_type bucket_id;
        Iter head;
        Iter next;
        Iter prev;
        IndexValueMap value;
        ValueIndexMap id;
    };

    stack operator[](const bucket_type& i)
    {
        assert(i < head.size());
        return stack(i, head.begin(), next.begin(), prev.begin(),
            id_to_value.begin(), id);
    }

protected:
    std::vector< size_type > head;
    std::vector< size_type > next;
    std::vector< size_type > prev;
    std::vector< value_type > id_to_value;
    Bucket bucket;
    ValueIndexMap id;
};

}

#endif

/* bucket_sorter.hpp
3dVdPNyfncRJUe8yvn9+54x8Fnb9W81OnuuRx57LFtcp74dWfPUnCXmruL76M+xjlLTrnWbXi7ZB6PwUa5Wy3/lj+XLbd7kbx1thgjMZdgz6VgsWjkj3499ylDMXHev32j9RdEzGfm9a0i4zXLQPNvC0AD4XbUPbe7Wc7w0XOqINmS0Q+6CGinbC36HOOa7n8X61zvHGPG6qTff/X8R2TEQqpN9yKeo436/60LeamKe3Yaf5odjvDcJuD+7p/V2MAe4LEPuyHHs+iLbYdprav7+7yIc6MmpwdL6NOpfXpfv9jw14P1d4VeQ/pvd+IGhtpbJ7hiBlBLj/Xuo/hc+o3kiXkQy1h+PhVjtOR0eH3DtVIcZmcyKZsZekHPyhKB9w9+x8Io5XV/Y1d5gs5o7pn0SetXksy/gGbI9twzdpw1HQSd2XczLbF2SB4dybtkEg7dmMaT9RagvHm2NoYubOy2yey9g6NATcsag+l4OviCGwPZKfXAk9twwoY28A+eXu/kf3WlLvW6yLe7jc4+3E/aC6zvM+49p9ishb5tq9Qxz7XN/wLbLwDbf34xwekPumNs04nuT6jqMNbgsy35O97yrp9xn7sAS6n86+gpV67sBt8LWnXdqrvPeswi4om/XzvpPV5312nZVunf9tH3dLPAd87pJbd7mxbGbR8qe+2/3ARVfM1D7u+fBx5+AR35td4MORvhfrGPztwN8hXfTbDXAN4Gj6MR8HrgQfTz/DU8Fj6O88jscTeDwJfA79us8FTwWfx3cinw+eRf/nvcEXgmfT3znCd/IezHf0HgK+FDyf/tFH0x/6RPAV4JPAV4LP4DuCLwAvBN/AdwPfTL/Vh+iv+hr9Vd+mf+pv4BfAdltfAY8Cv+b6YfI7FjzRww8TthB+q1W0SzX9Y2vAG4HHKM9tX2U9fg//w+353HYKn9tOZTm0md9lOOfht1vHcmvQ/31Nxe+9FLwNuAy8NvtrPeq3PrgevCH9djflu723AE9hOerN7xrI9dB7D8rfk+OjSfE73ZLltvfwO92JfqfTwUXgGfQbbqTf8G7cF7CLosfprK/IQ4951ONw8CrgI8DTC3q/3+eyEX7hm/k42PbPDHQL/0bXT3PxCPAI/wr7ako/zWAp6vgz3U9zEuSofppjkcfLT3Mqznu9H+igbu/3MDeVOn6azeCF+8KnfTDvYUaZ1AHIA74KaRFSN9LIMvhgIsWQLivTawQaKwcBpErO/3eZtkfjtJkTN97QDqwHjDMqy1ZR5hMlSO0HpM/XZ85o3MXIUR0aGhoaGhoaGhoaGhoaGhr5QX/z/w2NrTh3lyjBGs8DYcPwnr9vbPgcv3nm/nGIs8Zs7CWXqqbJNaUd5UIV1klyJn8c5S9j7sJCym+i87Q5y0pEEO04x3I3pNwUn91/JNu95wJEZ2tvirabTQm02LT/y7HszWSbKfs3V7aZ6tPsOdZhHeoQ8xkCrys6zIQXxTQEY891X8ux1k2ZQdnXu3ea1oJZpiUc7xGMdUqiM56HNkv5MRb4WrZ5RpKDLGHtaIZTnRYGnfD9yK18OdaXsMCEQlf+VC555kWuHOsHBRi32pXruhXsOTOaTE3HUn2+bP4BZddK2TuZqZ5LbfukvNRyLV+O8yb6CLwzxEt+bmXKfn6OMjdT2+z4hsyAa8g+uW4r5WINxhDYSpG7q4hpOl3cW/bJsVxp43sp9zPXxvm7l8i2TqA/QbXSVhmSXmyzmtGcU7nyWrqZcst7y+W9ZEbOryXZ5rFFzN6n7NzKldfwQsodK+VOjSbtGLeOoWdG51hha8EUvDSB8jU0NDQ0NDRyhwBSDb/b956yx16NTTN2ndawyYQ+1++F174=
*/