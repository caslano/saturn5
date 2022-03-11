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
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
*/