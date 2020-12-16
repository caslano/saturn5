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
80UuOyvCSl5zrj20NAQtn+4Tq/50dgw2jv1ihYC88gShBrPOQKfwZXbne7aaLkCM9dyDT9UdS99u4DThJYSsbVRLGXU07rnnEYyzhYFpZKbobA50IgeFj05joSycMyD8BGUAz/kUwrTfvqiJWoOrqhxy736wTHUAAqJfRjQhTStsF3WzD6pflr8Ltj4hDBNIBaYe3M39tvXXMd9U8Y2qcH1Z+F4qEDsNr+1kBUSBG9dxc9kIDBbluwQCB3Y/6Fb/IJIVI1mxTDaeRvQo0ytYnfOB3YF0647uPysXs1c6f3c0uqlB2Ghsyk5uCWiBqU1po1lzNys7Xkx7b3XhjB3u4ZP7qxvP8o8tll7Goa4uYoTTmVxmCFcld/dmK+AZfGo2hFEX3NrNVt2VlIVbca2LDS/+Ys1Xxpop3NswrK/MW9REpO9Rr9u8J+KFL6fRO7h5HR7cT4i5jbZuMPPAfRcJEmXwviXy2vIyNmCoFdXb7KPMWTNtOxpsmXihkEOG4LchF3LYnA9kGWkow18slCzqB9gRAJSdgAJaACDaD+oINDKMAVkwxNUfxkBctl2g7i/GNeEYyVFjmKlomXHoTDOLfOMbg5GMwCns8UnGfGUXMbZVo61wQjm1E5Fqw6eWTpvUT0+RvqP6Q2C7sdvkuIxPahnhfVtprJ1KHiVrR3cSVBa6l2jJn6G0ogXkMCrb/aBL/QhCnugt4ZObHCwB2AwB7N9EbG3R39DTjrRfOwcCi4u5c4+0k3N+rSpLikDfqFIEWpsTrwx4bvOeDug7LtAhPaxDqsyJ6jsCm/d8F0mqY+v7pZ9K+emhrnHyU5Yq5aevesat72/fINf3KW//K9f3uv2fqcP2f130/a2eCfZ/m00ny/4vveP6o3zoPxLs/7Bk1+z/esSTzK/76vZ/b3VEf7T+40TYV+uwh/SI6o9G6HAnvXWyVs6yPU5NOF+bEL4/ITwrPuzR1kIKBAEaa3RMHotnj/pT+jDR4gnVkninTLSGaqvxov6Qv9shLoZqazkmqzxUu7yjZ82Osj94bcz+4P12uVv3TTa/JVNZCH6aHbNbt/cz2divZyf4hslo//ghxv696L7RHvVCvZTl8aXcHFvK7XopM7OjXbrPyiWcKF+Ing/ukeBfjff/IZArpBgQIyw3BCdPM3m+W2apXje/m23VumWhWuSs2r+FfIRWmosntHwWPGyqdCwbXxipXrcguWpdpCUtmm5d16r9uytSJiDNLR8oby76GAv/qgXJFwfXHSwJpNH8xMfaUJC1zAuno7duAB7UOSjwCGiwQ4dd+XvLxhk57lUt7mcUZ1tF1w5mLxuXdEQ+xG1dNs6E76lNGC2RloxYiLBmB1gstmyrNnZ6q3rj/Mm2VXACrbza6Q1UeULDpymdYB9Cjw/pn78rODuovBZcY27Yaq+1Ka81bLXUTjTWlicFm01EZMFGUwhJQnh1vmtbPpA2vadOUxq5nnhDlf+lJ/lixxeNrOZUA358AW1f3vhjq5ObLNL3inYBQHMKJQuldpBh03qvWZwMKTaLxyTxmGJoU19q4f0vM9OX1e0per9or2KHjysisRA+1Wys7Fm10B4ZVpEVvhFHICszEDo87Nkk5IM+jDQ8uDslW1hCUOVC5+I9a9rkUCaZEvCk5i0iL5C3Pk/1HUWkkl0cwrP6/QVma6TFojQuqxLksHbR/gg7Vt9Mi48DwypMY1qyQM52pSG4tuuw3RRXs4biDifZbnsWL4v2f8MZfk0f13VdtJ/SBLrilKktfLcoL6s2xz6ixUxv+FzR73JMRVmp3Mx0znN+hXPnLTcQheQ3mTaZVCIQpMa/Y53QutmW05U7lLkogrbos3eNqWI=
*/