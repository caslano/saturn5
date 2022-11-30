// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2021.
// Modifications copyright (c) 2020-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP


#include <type_traits>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>

#include <boost/geometry/iterators/detail/iterator_base.hpp>


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
    ever_circling_iterator() = default;

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

    template
    <
        typename OtherIterator,
        std::enable_if_t<std::is_convertible<OtherIterator, Iterator>::value, int> = 0
    >
    inline ever_circling_iterator(ever_circling_iterator<OtherIterator> const& other)
        : m_begin(other.m_begin)
        , m_end(other.m_end)
        , m_skip_first(other.m_skip_first)
    {}

    /// Navigate to a certain position, should be in [start .. end], if at end
    /// it will circle again.
    inline void moveto(Iterator it)
    {
        this->base_reference() = it;
        check_end();
    }

private:
    template <typename OtherIterator> friend struct ever_circling_iterator;
    friend class boost::iterator_core_access;

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
    explicit inline ever_circling_range_iterator(Range const& range)
        : m_begin(boost::begin(range))
        , m_iterator(boost::begin(range))
        , m_size(boost::size(range))
        , m_index(0)
    {}

    /// Default constructor
    explicit inline ever_circling_range_iterator()
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
    inline ever_circling_range_iterator(ever_circling_range_iterator<OtherRange> const& other)
        : m_begin(other.m_begin)
        , m_iterator(other.m_iterator)
        , m_size(other.m_size)
        , m_index(other.m_index)
    {}

    typedef typename base_type::reference reference;
    typedef typename base_type::difference_type difference_type;

private:
    template <typename OtherRange> friend struct ever_circling_range_iterator;
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
        BOOST_GEOMETRY_ASSERT(m_begin == other.m_begin);
        return this->m_index == other.m_index;
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
        this->m_iterator = m_begin + m_index;
    }

    typename boost::range_iterator<Range const>::type m_begin;
    typename boost::range_iterator<Range const>::type m_iterator;
    difference_type m_size;
    difference_type m_index;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_EVER_CIRCLING_ITERATOR_HPP

/* ever_circling_iterator.hpp
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
*/