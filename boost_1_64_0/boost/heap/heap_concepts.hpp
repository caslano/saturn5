// boost heap: concepts
//
// Copyright (C) 2010 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_CONCEPTS_HPP
#define BOOST_HEAP_CONCEPTS_HPP

#include <boost/concept_check.hpp>

namespace boost {
namespace heap  {


template <class C>
struct PriorityQueue:
    boost::ForwardContainer<C>
{
    typedef typename C::iterator iterator;
    typedef typename C::const_iterator const_iterator;
    typedef typename C::allocator_type allocator_type;
    typedef typename C::value_compare value_compare;
    typedef typename C::value_type value_type;
    typedef typename C::const_reference const_reference;


    BOOST_CONCEPT_USAGE(PriorityQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::Assignable<value_type>));
        BOOST_CONCEPT_ASSERT((boost::Container<C>));
        BOOST_CONCEPT_ASSERT((boost::EqualityComparable<C>));
        BOOST_CONCEPT_ASSERT((boost::Comparable<C>));

        BOOST_CONCEPT_ASSERT((boost::Const_BinaryPredicate<value_compare, value_type, value_type>));

        c.swap(c2);
        c.clear();
        a = c.get_allocator();

        typename PriorityQueue::value_type v;
        c.push(v);

        v = c.top();
        c.pop();

        cmp = c.value_comp();

        // verify tags
        has_ordered_iterators = C::has_ordered_iterators;
        is_mergable = C::is_mergable;
        is_stable   = C::is_stable;
    }

private:
    C c, c2;
    allocator_type a;
    typename C::value_type v;
    value_compare cmp;
    bool has_ordered_iterators, is_mergable, is_stable;
};

template <class C>
struct MergablePriorityQueue:
    PriorityQueue<C>
{
    BOOST_CONCEPT_USAGE(MergablePriorityQueue)
    {
        C c, c2;
        c.merge(c2);
    }
};


template <class C>
struct MutablePriorityQueue:
    PriorityQueue<C>
{
    typedef typename C::handle_type handle_type;

    BOOST_CONCEPT_USAGE(MutablePriorityQueue)
    {
        BOOST_CONCEPT_ASSERT((boost::Assignable<typename MutablePriorityQueue::handle_type>));

        typename MutablePriorityQueue::value_type v;
        typename MutablePriorityQueue::handle_type h  = c.push(v);
        typename MutablePriorityQueue::handle_type h2 = c.push(v);
        c.update(h, v);
        c.increase(h, v);
        c.decrease(h, v);

        c.update(h);
        c.increase(h);
        c.decrease(h);

        equal = (h == h2);
        not_equal = (h != h2);

        h2 = h;
    }

    C c;
    bool equal, not_equal;
};

}}

#endif /* BOOST_HEAP_CONCEPTS_HPP */

/* heap_concepts.hpp
ka84J1ZQK8DkBy8908D3c/KdiJg7X812EQvCcOoZD0EtNUfcbtLw/M270+YC53nutE25bHln0fZdb1fCqCPUdGhTXSyAZO04O3J+Mif0mfML2/wQrHeMocG7KgHZFhh+s6hr1Y6+w/+h5anpCF28zSDJ5N8c+hInpj1TqTeP7KGBN6p6OpkgFUxaBaAcFQP5sirgKG6IW048StOrsVUgqnGZzf3BrPNEpV1MHw2EVvUf6dg9semNxWoPmvQyRO5t9oKqJ3WV/dd1qoLj91Lnnhsq9N+WaY//UGDI8joA60Km+xA73Tc6hck4p6TvWXDuUeUN37O0yyqQVlYJy4Wp6ePIYpqyx9x5zVdEtIjdi6qDtStCh0wT5cGVvkeRbz0x3YruwMkdamr7u3PF2yMLkv4PyoSdeXPrSXGOUTvkLtGaWcDAwUKYZCv2jdK+U1ECcy5tXhFuOPS2wSjCDojVg4VOrG5oft11Fo53FyF9Q1bnBme5SiRr8O5AVkyrEzl50faIhyrCLD+MYtuBLj4YvBBh8DGR6AilEFyzCECcboOfbNIN83r4G5HrsA==
*/