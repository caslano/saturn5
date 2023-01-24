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
WFYUoOSxf8f84vXKIA8+44Zn6fzLgEX1eLvpV2cVgBmMlIzPDusfTDC45ROzk9aU2LdIl8Hv6bN8tMws6QF8e2BSaG6wzjBfKCNdaewFJOhPbuoCPt4wf4p39QpVY/tbB8udE80yO+fZmZJ3s0w0bfHWoD4qh58x1ue4l5uXd62BU69IO9zwrdOPJoaOedYZ1lLHbedc7LAXyCVSDn7qjsdt2rlMpRp8YrcWsHXpVMk41iLkWCh/wIRf1G5avRWc3SQX5d0mhBISYIh3X6ADdhK1V0E7hM13MV0wk6zUys9r6sxZVqTalb7XMzvn2jHKwXIagknSx6oEQzXxe4PoyV5bzpEdE60Xm8v3iX+ZTfCkSQUGCYdHXTCQr2cKHctkUceD3v3sP1G4lTBu0zRvxAp/JCwiRMplhYd0rpSnKE/LcSDWn26fG3qibBuiMrPev+tODZ8Dtdb5o0B+X5rxz5wYp4/9AnWcBdS1nfmxu1LfB9xlg5v92/XxBzRB1yyO79kDdyj5H0zIG1R1mGzZenxa79KqIQND9/VZDZD4++i19YjW1nyJ+99lgxIS1JKb9wHckA6ysKYX2Jk7KKStHWTrDuRhU9spxOvM1Yea9qAi3bWR2u4/6xymsJL9jtrw76333mcGHhvspqEHfYet99zr65O+/yDmLIOi8LYArtICElJKKn9EpbtBQEFEQhF26VIaVjp2CUFEJFZA
*/