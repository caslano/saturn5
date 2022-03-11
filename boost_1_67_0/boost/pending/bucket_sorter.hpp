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