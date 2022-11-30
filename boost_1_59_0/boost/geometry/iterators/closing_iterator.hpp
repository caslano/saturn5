// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP


#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>


namespace boost { namespace geometry
{

/*!
\brief Iterator which iterates through a range, but adds first element at end of the range
\tparam Range range on which this class is based on
\ingroup iterators
\note It's const iterator treating the Range as one containing non-mutable elements.
        For both "closing_iterator<Range> and "closing_iterator<Range const>
        const reference is always returned when dereferenced.
\note This class is normally used from "closeable_view" if Close==true
*/
template <typename Range>
struct closing_iterator
    : public boost::iterator_facade
    <
        closing_iterator<Range>,
        typename boost::range_value<Range>::type const,
        boost::random_access_traversal_tag,
        typename boost::range_reference<Range const>::type,
        typename boost::range_difference<Range>::type
    >
{
private:
    typedef boost::iterator_facade
        <
            closing_iterator<Range>,
            typename boost::range_value<Range>::type const,
            boost::random_access_traversal_tag,
            typename boost::range_reference<Range const>::type,
            typename boost::range_difference<Range>::type
        > base_type;

public:
    typedef typename base_type::reference reference;
    typedef typename base_type::difference_type difference_type;

    /// Constructor including the range it is based on
    explicit inline closing_iterator(Range const& range)
        : m_iterator(boost::begin(range))
        , m_begin(boost::begin(range))
        , m_end(boost::end(range))
        , m_size(m_end - m_begin)
        , m_index(0)
    {}

    /// Constructor to indicate the end of a range
    explicit inline closing_iterator(Range const& range, bool)
        : m_iterator(boost::end(range))
        , m_begin(boost::begin(range))
        , m_end(boost::end(range))
        , m_size(m_end - m_begin)
        , m_index((m_size == 0) ? 0 : m_size + 1)
    {}

    /// Default constructor
    inline closing_iterator()
        : m_size(0)
        , m_index(0)
    {}

    template
    <
        typename OtherRange,
        std::enable_if_t
            <
                std::is_convertible
                    <
                        typename boost::range_iterator<OtherRange const>::type,
                        typename boost::range_iterator<Range const>::type
                    >::value,
                int
            > = 0
    >
    inline closing_iterator(closing_iterator<OtherRange> const& other)
        : m_iterator(other.m_iterator)
        , m_begin(other.m_begin)
        , m_end(other.m_end)
        , m_size(other.m_size)
        , m_index(other.m_index)
    {}

private:
    template <typename OtherRange> friend struct closing_iterator;
    friend class boost::iterator_core_access;

    inline reference dereference() const
    {
        return *m_iterator;
    }

    inline difference_type distance_to(closing_iterator<Range> const& other) const
    {
        return other.m_index - this->m_index;
    }

    inline bool equal(closing_iterator<Range> const& other) const
    {
        BOOST_GEOMETRY_ASSERT(m_begin == other.m_begin && m_end == other.m_end);
        return this->m_index == other.m_index;
    }

    inline void increment()
    {
        if (++m_index < m_size)
        {
            ++m_iterator;
        }
        else
        {
            update_iterator();
        }
    }

    inline void decrement()
    {
        if (m_index-- < m_size)
        {
            --m_iterator;
        }
        else
        {
            update_iterator();
        }
    }

    inline void advance(difference_type n)
    {
        if (m_index < m_size && m_index + n < m_size)
        {
            m_index += n;
            m_iterator += n;
        }
        else
        {
            m_index += n;
            update_iterator();
        }
    }

    inline void update_iterator()
    {
        this->m_iterator = m_index <= m_size
            ? m_begin + (m_index % m_size)
            : m_end
            ;
    }

    typename boost::range_iterator<Range const>::type m_iterator;
    typename boost::range_iterator<Range const>::type m_begin;
    typename boost::range_iterator<Range const>::type m_end;
    difference_type m_size;
    difference_type m_index;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP

/* closing_iterator.hpp
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
*/