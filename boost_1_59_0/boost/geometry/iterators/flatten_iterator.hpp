// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_FLATTEN_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_FLATTEN_ITERATOR_HPP


#include <type_traits>

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
    flatten_iterator() = default;

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
        typename OtherReference,
        std::enable_if_t
            <
                std::is_convertible<OtherOuterIterator, OuterIterator>::value
                && std::is_convertible<OtherInnerIterator, InnerIterator>::value,
                int
            > = 0
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
    {}

    flatten_iterator(flatten_iterator const& other) = default;

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