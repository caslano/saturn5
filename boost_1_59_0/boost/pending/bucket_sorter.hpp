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
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
*/