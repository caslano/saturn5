// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP


#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/geometry/core/exception.hpp>

namespace boost { namespace geometry
{

namespace detail
{

// Adapts pointer, on points, to a Boost.Range
template <typename Point, int MaxSize>
class points_view
{
    // Iterates over a series of points (indicated by pointer
    // to have it lightweight). Probably there is already an
    // equivalent of this within Boost. If so, TODO: use that one.
    // This used to be "box_iterator" and "segment_iterator".
    // ALTERNATIVE: use boost:array and its iterators
    struct points_iterator
        : public boost::iterator_facade
            <
                points_iterator,
                Point const,
                boost::random_access_traversal_tag
            >
    {
        // Constructor: Begin iterator
        inline points_iterator(Point const* p)
            : m_points(p)
            , m_index(0)
        {}

        // Constructor: End iterator
        inline points_iterator(Point const* p, bool)
            : m_points(p)
            , m_index(MaxSize)
        {}

        // Constructor: default (for Range Concept checking).
        inline points_iterator()
            : m_points(NULL)
            , m_index(MaxSize)
        {}

        typedef std::ptrdiff_t difference_type;

    private:
        friend class boost::iterator_core_access;

        inline Point const& dereference() const
        {
            if (m_index >= 0 && m_index < MaxSize)
            {
                return m_points[m_index];
            }

            // If it index larger (or smaller) return first point
            // (assuming initialized)
            return m_points[0];
        }

        inline bool equal(points_iterator const& other) const
        {
            return other.m_index == this->m_index;
        }

        inline void increment()
        {
            m_index++;
        }

        inline void decrement()
        {
            m_index--;
        }

        inline difference_type distance_to(points_iterator const& other) const
        {
            return other.m_index - this->m_index;
        }

        inline void advance(difference_type n)
        {
            m_index += n;
        }

        Point const* m_points;
        difference_type m_index;
    };

public :

    typedef points_iterator const_iterator;
    typedef points_iterator iterator; // must be defined

    const_iterator begin() const { return const_iterator(m_points); }
    const_iterator end() const { return const_iterator(m_points, true); }

    // It may NOT be used non-const, so commented:
    //iterator begin() { return m_begin; }
    //iterator end() { return m_end; }

protected :

    template <typename CopyPolicy>
    explicit points_view(CopyPolicy const& copy)
    {
       copy.apply(m_points);
    }

private :
    // Copy points here - box might define them otherwise
    Point m_points[MaxSize];
};

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_POINTS_VIEW_HPP

/* points_view.hpp
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
*/