// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP

#include <boost/range.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/iterators/base.hpp>

namespace boost { namespace geometry
{

/*!
    \brief Iterator which ever circles through a range
    \tparam Iterator iterator on which this class is based on
    \ingroup iterators
    \details If the iterator arrives at range.end() it restarts from the
     beginning. So it has to be stopped in another way.
    Don't call for(....; it++) because it will turn in an endless loop
    \note Name inspired on David Bowie's
    "Chant Of The Ever Circling Skeletal Family"
*/
template <typename Iterator>
struct ever_circling_iterator :
    public detail::iterators::iterator_base
    <
        ever_circling_iterator<Iterator>,
        Iterator
    >
{
    friend class boost::iterator_core_access;

    explicit inline ever_circling_iterator(Iterator begin, Iterator end,
            bool skip_first = false)
      : m_begin(begin)
      , m_end(end)
      , m_skip_first(skip_first)
    {
        this->base_reference() = begin;
    }

    explicit inline ever_circling_iterator(Iterator begin, Iterator end, Iterator start,
            bool skip_first = false)
      : m_begin(begin)
      , m_end(end)
      , m_skip_first(skip_first)
    {
        this->base_reference() = start;
    }

    /// Navigate to a certain position, should be in [start .. end], if at end
    /// it will circle again.
    inline void moveto(Iterator it)
    {
        this->base_reference() = it;
        check_end();
    }

private:

    inline void increment(bool possibly_skip = true)
    {
        (this->base_reference())++;
        check_end(possibly_skip);
    }

    inline void check_end(bool possibly_skip = true)
    {
        if (this->base() == this->m_end)
        {
            this->base_reference() = this->m_begin;
            if (m_skip_first && possibly_skip)
            {
                increment(false);
            }
        }
    }

    Iterator m_begin;
    Iterator m_end;
    bool m_skip_first;
};

template <typename Range>
struct ever_circling_range_iterator
    : public boost::iterator_facade
    <
        ever_circling_range_iterator<Range>,
        typename boost::range_value<Range>::type const,
        boost::random_access_traversal_tag,
        typename boost::range_reference<Range const>::type,
        typename boost::range_difference<Range>::type
    >
{
private:
    typedef boost::iterator_facade
        <
            ever_circling_range_iterator<Range>,
            typename boost::range_value<Range>::type const,
            boost::random_access_traversal_tag,
            typename boost::range_reference<Range const>::type,
            typename boost::range_difference<Range>::type
        > base_type;

public:
    /// Constructor including the range it is based on
    explicit inline ever_circling_range_iterator(Range& range)
        : m_range(&range)
        , m_iterator(boost::begin(range))
        , m_size(boost::size(range))
        , m_index(0)
    {}

    /// Default constructor
    explicit inline ever_circling_range_iterator()
        : m_range(NULL)
        , m_size(0)
        , m_index(0)
    {}

    typedef typename base_type::reference reference;
    typedef typename base_type::difference_type difference_type;

private:
    friend class boost::iterator_core_access;

    inline reference dereference() const
    {
        return *m_iterator;
    }

    inline difference_type distance_to(ever_circling_range_iterator<Range> const& other) const
    {
        return other.m_index - this->m_index;
    }

    inline bool equal(ever_circling_range_iterator<Range> const& other) const
    {
        return this->m_range == other.m_range
            && this->m_index == other.m_index;
    }

    inline void increment()
    {
        ++m_index;
        if (m_index >= 0 && m_index < m_size)
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
        --m_index;
        if (m_index >= 0 && m_index < m_size)
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
        if (m_index >= 0 && m_index < m_size
            && m_index + n >= 0 && m_index + n < m_size)
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
        while (m_index < 0)
        {
            m_index += m_size;
        }
        m_index = m_index % m_size;
        this->m_iterator = boost::begin(*m_range) + m_index;
    }

    Range* m_range;
    typename boost::range_iterator<Range>::type m_iterator;
    difference_type m_size;
    difference_type m_index;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP

/* ever_circling_iterator.hpp
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
*/