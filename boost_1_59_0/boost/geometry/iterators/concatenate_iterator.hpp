// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CONCATENATE_ITERATOR_HPP


#include <type_traits>

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
    concatenate_iterator() = default;

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
        typename OtherReference,
        std::enable_if_t
            <
                std::is_convertible<OtherIt1, Iterator1>::value
                && std::is_convertible<OtherIt2, Iterator2>::value,
                int
            > = 0
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
    {}

    concatenate_iterator(concatenate_iterator const& other) = default;

    concatenate_iterator& operator=(concatenate_iterator const& other) = default;

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