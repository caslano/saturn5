// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>


namespace boost { namespace geometry
{



template
<
    typename Iterator1,
    typename Iterator2,
    typename Value,
    typename Reference = Value&
>
class concatenate_iterator
    : public boost::iterator_facade
        <
            concatenate_iterator<Iterator1, Iterator2, Value, Reference>,
            Value,
            boost::bidirectional_traversal_tag,
            Reference
        >
{
private:
    Iterator1 m_it1, m_end1;
    Iterator2 m_begin2, m_it2;

public:
    typedef Iterator1 first_iterator_type;
    typedef Iterator2 second_iterator_type;

    // default constructor
    concatenate_iterator() {}

    // for begin
    concatenate_iterator(Iterator1 it1, Iterator1 end1,
                         Iterator2 begin2, Iterator2 it2)
        : m_it1(it1), m_end1(end1), m_begin2(begin2), m_it2(it2)
    {}

    // for end
    concatenate_iterator(Iterator1 end1, Iterator2 begin2, Iterator2 end2)
        : m_it1(end1), m_end1(end1), m_begin2(begin2), m_it2(end2)
    {}

    template
    <
        typename OtherIt1,
        typename OtherIt2,
        typename OtherValue,
        typename OtherReference
    >
    concatenate_iterator(concatenate_iterator
                         <
                             OtherIt1,
                             OtherIt2,
                             OtherValue,
                             OtherReference
                         > const& other)
        : m_it1(other.m_it1)
        , m_end1(other.m_end1)
        , m_begin2(other.m_begin2)
        , m_it2(other.m_it2)
    {
        static const bool are_conv
            = boost::is_convertible<OtherIt1, Iterator1>::value
           && boost::is_convertible<OtherIt2, Iterator2>::value;

        BOOST_MPL_ASSERT_MSG((are_conv),
                             NOT_CONVERTIBLE,
                             (types<OtherIt1, OtherIt2>));
    }

private:
    friend class boost::iterator_core_access;

    template <typename It1, typename It2, typename V, typename R>
    friend class concatenate_iterator;

    inline Reference dereference() const
    {
        if ( m_it1 == m_end1 )
        {
            return *m_it2;
        }
        return *m_it1;
    }

    template
    <
        typename OtherIt1,
        typename OtherIt2,
        typename OtherValue,
        typename OtherReference
    >
    inline bool equal(concatenate_iterator
                      <
                          OtherIt1,
                          OtherIt2,
                          OtherValue,
                          OtherReference
                      > const& other) const
    {
        return m_it1 == other.m_it1 && m_it2 == other.m_it2;
    }

    inline void increment()
    {
        if ( m_it1 == m_end1 )
        {
            ++m_it2;
        }
        else
        {
            ++m_it1;
        }
    }

    inline void decrement()
    {
        if ( m_it2 == m_begin2 )
        {
            --m_it1;
        }
        else
        {
            --m_it2;
        }
    }
};



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP

/* concatenate_iterator.hpp
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
*/