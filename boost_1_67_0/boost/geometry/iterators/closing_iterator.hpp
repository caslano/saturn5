// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP

#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>



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
    explicit inline closing_iterator(Range& range)
        : m_range(&range)
        , m_iterator(boost::begin(range))
        , m_end(boost::end(range))
        , m_size(static_cast<difference_type>(boost::size(range)))
        , m_index(0)
    {}

    /// Constructor to indicate the end of a range
    explicit inline closing_iterator(Range& range, bool)
        : m_range(&range)
        , m_iterator(boost::end(range))
        , m_end(boost::end(range))
        , m_size(static_cast<difference_type>(boost::size(range)))
        , m_index((m_size == 0) ? 0 : m_size + 1)
    {}

    /// Default constructor
    explicit inline closing_iterator()
        : m_range(NULL)
        , m_size(0)
        , m_index(0)
    {}

private:
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
        return this->m_range == other.m_range
            && this->m_index == other.m_index;
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
            ? boost::begin(*m_range) + (m_index % m_size)
            : boost::end(*m_range)
            ;
    }

    Range* m_range;
    typename boost::range_iterator<Range>::type m_iterator;
    typename boost::range_iterator<Range>::type m_end;
    difference_type m_size;
    difference_type m_index;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP

/* closing_iterator.hpp
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
*/