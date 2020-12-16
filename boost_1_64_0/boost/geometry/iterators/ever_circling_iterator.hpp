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
Zpk5HtQvV7RDuJdN5Lo32PYljFvb1/7taMe7qfcVidKOA7R9b/PQKNWUmzZGlhyHdrwgSfah6HmPtf9ov6OuKkoWFpUtYvLhVkcS3n9M19N+JqBQ9t53Ev2Z2ZiHzbHMys/UqRMLRk2bUVBJe2RTHyouC5ZWlqjplHX9WqWZ4WZXrdB5E1n5dpFfzVX0BEnrbTykwrSIjmVWv9Q6Or9ohI7OiP5S8kDZVB70t29IFzedrirzmMj5jRjnDR6jzKln6zKrwZuZ5OyqkmJV2sgcz+UbQyKbeNRzEs3kesi3ehz7ZNfJvv8eRnSceJx85Tjy5chOpUt+RKbHUfdtNpSf8nD9tvGEOcfR+YnVLmLmB5mjt4nysx1tApmmtwm3byE524NzLtcmpf5ctYc5flnlLKisqqAj97PuKzr/uOo2L2GJQX8byjYepcGNyr91o/urlV+VhuMekto8qve4nfBp8rrXyqupuDrSNgpmXVSwqGhhiZFJnsoDtjpXzjrvIjtA6yj+BDthjQtE9/CT1vhTTmasa6Nl+imZc7B/pOyV7HfxSB3oMVmFyYKHVJhlRql8M6pUx5Or2sxAq9VpXeLvK7+LjCJ0GXdkHDfPX2xmf/PF1E3YO8qcxPhDiaFu5j+hWNdG7gWJ55huXeTbUDgoewG9ta/r9fKrMB30/SGngT6ULW2uXN0fHXWs9SlTh/ipOlRuebiRLm6RdAen5ao0DeOnGc57xoEY+/dnm+1Tha+27qeNeJaywie6PkuJf6PbaGOel8ZIGXZLjJmYFDHPIb/VKkPl/IKpU6blF+RPOXPa6aOmjTtzsvnvmHETT7fpYj8lTV3b+YYuk8iLbvmByp8q1mXS/noM8elv1jVcvlxIepRFpaev40DlRhp1yleYVr98L5r98ujlQ3e6e/n21sm//xjzb+Z1fGS+FiOvL5n3/KPmFT3aBYuWLlhg6PwEG5Efez2tS6+f9iukbUw/atpLF0rbPpBRr56Qd9ZTUiPyFakn4pN6cua1tEXsNptz1LyWL60sdb2myDfcZnPqlCXUhLI0pc2Ozahfvtdwyztq+ZYVLVha4nYtRD5T67lGF3pxZH7YAubVKV9KE8pHevXKRxq4qTQc87w9mVYMvUikA2wJDyJfKOWrXFBQVFwsx3RKSxYsWKwnMQXMaGLNY0T2fPz0dx7ws+5X65XfX63rqMP2sOohUOcZRfufqOzTsX9L2T2edF1vC4tWmCIikwmvVGH+ruxlOo6uuq1xZ1iASnF9L9+s/N8zws7vCOhnqUWEeUqFec5I1v5lyi/LrNcZ6lrJPdxjjFL28cQWbb+GmldE53GTVJgwMpPSJlLfh1ty7yJcODTD0T/VvVXCZFG4f6r7eodQKNQlNDGQHPZlWWEi8ZyWiX8aJrn6Dd12JJ7INzM3p2Jknph7lHlifnSeqOwzot/CUG2rEDvXTd/PMnEr1e1Nrk2dNpcrCxT3Sn9i3zdtDjPD3ubkaFQj25wlm2pkyndeDyn7LUZvQpdgbG1RhZkQkSEXnZn3zDC61W2DKly+LRzzS6McU6/tSdgyW9h+uMxljSRWnQ86Sp3n1anzsXXqPD9Gnc+IXed6/SEsE/f7yGML4aPmvfdcXec8HBYsLJpf4nhuyq73LGJO9Xnqjo5lEkc7VX+PqLFu8dIqPVaLP7nMlD78irLf5DmVJ/tBngQlVx6wdP0vkLnwZMKNOM8M19fzqJFBGNONWbByS4vKyH0hU/ryqyruG4jbQ9x8H1X3eV0q/R2T11XYjZ4+1FRvj1f1xf5ZllLugNmHEltH7+HSh7pKmBnZyJphUqrvYpkknO5LpTcmnxgIhf3V1UbMufpFKu//4Lw=
*/