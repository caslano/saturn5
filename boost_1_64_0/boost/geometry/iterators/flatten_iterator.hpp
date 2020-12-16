// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_FLATTEN_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_FLATTEN_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/core/assert.hpp>

namespace boost { namespace geometry
{



template
<
    typename OuterIterator,
    typename InnerIterator,
    typename Value,
    typename AccessInnerBegin,
    typename AccessInnerEnd,
    typename Reference = Value&
>
class flatten_iterator
    : public boost::iterator_facade
        <
            flatten_iterator
                <
                    OuterIterator,
                    InnerIterator,
                    Value,
                    AccessInnerBegin,
                    AccessInnerEnd,
                    Reference
                >,
            Value,
            boost::bidirectional_traversal_tag,
            Reference
        >
{
private:
    OuterIterator m_outer_it, m_outer_end;
    InnerIterator m_inner_it;

public:
    typedef OuterIterator outer_iterator_type;
    typedef InnerIterator inner_iterator_type;

    // default constructor
    flatten_iterator() {}

    // for begin
    flatten_iterator(OuterIterator outer_it, OuterIterator outer_end)
        : m_outer_it(outer_it), m_outer_end(outer_end)
    {
        advance_through_empty();
    }

    // for end
    flatten_iterator(OuterIterator outer_end)
        : m_outer_it(outer_end), m_outer_end(outer_end)
    {}

    template
    <
        typename OtherOuterIterator, typename OtherInnerIterator,
        typename OtherValue,
        typename OtherAccessInnerBegin, typename OtherAccessInnerEnd,
        typename OtherReference
    >
    flatten_iterator(flatten_iterator
                     <
                         OtherOuterIterator,
                         OtherInnerIterator,
                         OtherValue,
                         OtherAccessInnerBegin,
                         OtherAccessInnerEnd,
                         OtherReference
                     > const& other)
        : m_outer_it(other.m_outer_it),
          m_outer_end(other.m_outer_end),
          m_inner_it(other.m_inner_it)
    {
        static const bool are_conv
            = boost::is_convertible
                <
                    OtherOuterIterator, OuterIterator
                >::value
           && boost::is_convertible
                <
                    OtherInnerIterator, InnerIterator
                >::value;

        BOOST_MPL_ASSERT_MSG((are_conv),
                             NOT_CONVERTIBLE,
                             (types<OtherOuterIterator, OtherInnerIterator>));
    }

    flatten_iterator& operator=(flatten_iterator const& other)
    {
        m_outer_it = other.m_outer_it;
        m_outer_end = other.m_outer_end;
        // avoid assigning an iterator having singular value
        if ( other.m_outer_it != other.m_outer_end )
        {
            m_inner_it = other.m_inner_it;
        }
        return *this;
    }

private:
    friend class boost::iterator_core_access;

    template
    <
        typename Outer,
        typename Inner,
        typename V,
        typename InnerBegin,
        typename InnerEnd,
        typename R
    >
    friend class flatten_iterator;

    static inline bool empty(OuterIterator outer_it)
    {
        return AccessInnerBegin::apply(*outer_it)
            == AccessInnerEnd::apply(*outer_it);
    }

    inline void advance_through_empty()
    {
        while ( m_outer_it != m_outer_end && empty(m_outer_it) )
        {
            ++m_outer_it;
        }

        if ( m_outer_it != m_outer_end )
        {
            m_inner_it = AccessInnerBegin::apply(*m_outer_it);
        }
    }

    inline Reference dereference() const
    {
        BOOST_GEOMETRY_ASSERT( m_outer_it != m_outer_end );
        BOOST_GEOMETRY_ASSERT( m_inner_it != AccessInnerEnd::apply(*m_outer_it) );
        return *m_inner_it;
    }


    template
    <
        typename OtherOuterIterator,
        typename OtherInnerIterator,
        typename OtherValue,
        typename OtherAccessInnerBegin,
        typename OtherAccessInnerEnd,
        typename OtherReference
    >
    inline bool equal(flatten_iterator
                      <
                          OtherOuterIterator,
                          OtherInnerIterator,
                          OtherValue,
                          OtherAccessInnerBegin,
                          OtherAccessInnerEnd,
                          OtherReference
                      > const& other) const
    {
        if ( m_outer_it != other.m_outer_it )
        {
            return false;
        }

        if ( m_outer_it == m_outer_end )
        {
            return true;
        }

        return m_inner_it == other.m_inner_it;
    }

    inline void increment()
    {
        BOOST_GEOMETRY_ASSERT( m_outer_it != m_outer_end );
        BOOST_GEOMETRY_ASSERT( m_inner_it != AccessInnerEnd::apply(*m_outer_it) );

        ++m_inner_it;
        if ( m_inner_it == AccessInnerEnd::apply(*m_outer_it) )
        {
            ++m_outer_it;
            advance_through_empty();
        }
    }

    inline void decrement()
    {
        if ( m_outer_it == m_outer_end
             || m_inner_it == AccessInnerBegin::apply(*m_outer_it) )
        {
            do
            {
                --m_outer_it;
            }
            while ( empty(m_outer_it) );
            m_inner_it = AccessInnerEnd::apply(*m_outer_it);
        }        
        --m_inner_it;
    }
};



}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_FLATTEN_ITERATOR_HPP

/* flatten_iterator.hpp
UHNrPNTlGafm7mtJd1p2ZO5e/ZRj8p4cY+4u9btOxdGNdEw7V1PZL2CW2sd17n6FCpMTXaeUcr0ZTX9DqAsJJ4fM1MNuz3RTVTw9SRu7TnsWq7J5rmnnqzC5yJh2kaG3+GmtaiyTvCSa597VmLhqim1u6gjTgzDJVpgiPReoEyafMAnqeq7qpueIdcJURcOs1GGOedz0p/1ZlcnoXFJRQXj6rH5erd+P0qX/0nfwp+/Is84gKw7jjQzLfvd5zmef8RGdFR3kHk4ms2EH+JY5np6v+3Z5UUVlietdPOb6iMjLt63Oxv6Fsoe953n8MZ+fJmgZ2qL09SB7cYF3sidoG1+L6ObRe+GaC0y3kP62j6FkUry1xnl8PyzfmgvouHMknMeoVeF+yVrEUs4SeaiR0WnlZn3qe7QsA5XMUflphcvtSqaXZxsu0j4d9/o02F2F8elvUJ+s7Bfpb1AfUPntWG8ukMF/P5sp7xOUPZLHgzqP6TrNhfPLCqLP/umwrYp3Dc+H+ZYbtjzlVsmqyZRofpkr8kfPP15UaZxGmth1mp09zY0J6JRvpdLcTQKJ0TVi9d3oaR45T6XCD1JujLuEY76j3M4wslU4FVDH25Gwd1A/+KkxOdHm1wKZHYbXNu+pNBu8vtbvqHCZyGLX1zDDcypu81hxfZF61fM0rt+yiuh4vUCFLfWY87Q3jBT1/iWV+9qN7a1nZ18B72V8SeFQihHr+V2VbbiKYwlxYtfpz9T5VnESXzVmB3Ey+PlKQ0NBQlCNF+K/GXM//uGkAj2GdpT8ZLAQcrfpl5ATCoYWhqpCxaEqshZkAcYMsxXZt6PxJ/QP+MIJiaHm1hsna8yJhEslrtpIXGbxkskIAUOJhk43U9I9LUfmkL7qXeFgi3rzyEh9zcyx5pG+6mo9i7Tnf7+Vf/z3hxYHguFAAjeh2fzjTVD1U4j/Vkwk/9V/MAvQ3Lo/iv8+yTdxkGt/MuECSQTzJfKfN6jzni5pHs6JzFtXOZ557OUbyzh3hxnnqpOIM6WF6X4Eue6471Du5nVK9ikZ8RuN304tE0ipW2fV+N+n/MebcfpN94m4XarjPFPilPySN5+6FzTlfsA82TanS8deGmNtqFzP69T46Bzju1gRvm9+Ew/uh+YYv/VC5xgvs+ZGj/GWfBvpDzwPKvuPPQ/Tx6o84XrjvMydRe4+zw7Ggg+Mx2OO7fk6XHvdhx9X9hc8T/L3Uo8n5jPZJMJtLCAcJ1m/b6S5jtNvXijvf2Wc/rOyb+c7JW31WD25sP5YnS5j9QsqjVXGufWf0/R754MqTAkztkmEsY3dBmFkffZEFWaOMVCNXbjpdNvGHLPTTCoZr5Ep96VUZR/mmc/KZRfzXqncI/H0Ue+nD9MmJ3aWPnA5zbVZsnL/nIGuR2dpr9Xfor3SyWirEb+x+O2MyCRE301H4tzWWfr7DPybZ6k483GrjsRZbg44spdA/LZiapVMaJ7ZQXhHFx0HJd6cLhJv+0DAl8YwWGYNgwHDGge3E8chTGQcyTWHkZRQsn0c7Crh2hBXrcQV9jULBdX2htBg4CNsdB4raU/rEhkLV3UP+/2McPwlnMzlGBMxkTmgyKzoosegAXXHoGzsfqvfM3Y2vf/n1en/Y2P0/3xH/4/rAflv1gPyhNIDMq99bZuRoVndlhcO2/HhFcbBuB6QY9UD8olB2TD81PPpr+GrhjV27JV3Ktvl/0mY++X/JZha+X8D5m75fwtmp/z/R8wd8v/7mN3y/+WY++T/2zxqPFG/DzFh2/8B2/8Jtv+Tbf97bf970qwzzowZjCXW/5eIX74h+xBlPyRpO76pNkHOQk+CzeFkmAanwnSYD1vCKbA=
*/