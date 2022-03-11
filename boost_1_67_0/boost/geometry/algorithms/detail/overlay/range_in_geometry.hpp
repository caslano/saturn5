// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP


#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/iterators/point_iterator.hpp>

#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct points_range
{
    typedef geometry::point_iterator<Geometry const> iterator_type;

    explicit points_range(Geometry const& geometry)
        : m_geometry(geometry)
    {}

    iterator_type begin() const
    {
        return geometry::points_begin(m_geometry);
    }

    iterator_type end() const
    {
        return geometry::points_end(m_geometry);
    }

    Geometry const& m_geometry;
};
// Specialized because point_iterator doesn't support boxes
template <typename Box>
struct points_range<Box, box_tag>
{
    typedef typename geometry::point_type<Box>::type point_type;
    typedef const point_type * iterator_type;

    explicit points_range(Box const& box)
    {
        detail::assign_box_corners(box,
            m_corners[0], m_corners[1], m_corners[2], m_corners[3]);
    }

    iterator_type begin() const
    {
        return m_corners;
    }

    iterator_type end() const
    {
        return m_corners + 4;
    }

    point_type m_corners[4];
};

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct point_in_geometry_helper
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Geometry const& geometry,
                            Strategy const& strategy)
    {
        return detail::within::point_in_geometry(point, geometry, strategy);
    }
};
// Specialized because point_in_geometry doesn't support Boxes
template <typename Box>
struct point_in_geometry_helper<Box, box_tag>
{
    template <typename Point, typename Strategy>
    static inline int apply(Point const& point, Box const& box,
                            Strategy const&)
    {
        return geometry::covered_by(point, box) ? 1 : -1;
    }
};

// This function returns
// when it finds a point of geometry1 inside or outside geometry2
template <typename Geometry1, typename Geometry2, typename Strategy>
static inline int range_in_geometry(Geometry1 const& geometry1,
                                    Geometry2 const& geometry2,
                                    Strategy const& strategy,
                                    bool skip_first = false)
{
    int result = 0;
    points_range<Geometry1> points(geometry1);
    typedef typename points_range<Geometry1>::iterator_type iterator_type;
    iterator_type const end = points.end();
    iterator_type it = points.begin();
    if (it == end)
    {
        return result;
    }
    else if (skip_first)
    {
        ++it;
    }

    typename Strategy::template point_in_geometry_strategy
        <
            Geometry1, Geometry2
        >::type const in_strategy
        = strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>();

    for ( ; it != end; ++it)
    {
        result = point_in_geometry_helper<Geometry2>::apply(*it, geometry2, in_strategy);
        if (result != 0)
        {
            return result;
        }
    }
    // all points contained entirely by the boundary
    return result;
}

// This function returns if first_point1 is inside or outside geometry2 or
// when it finds a point of geometry1 inside or outside geometry2
template <typename Point1, typename Geometry1, typename Geometry2, typename Strategy>
inline int range_in_geometry(Point1 const& first_point1,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
{
    // check a point on border of geometry1 first
    int result = point_in_geometry_helper<Geometry2>::apply(first_point1, geometry2,
                    strategy.template get_point_in_geometry_strategy<Point1, Geometry2>());
    if (result == 0)
    {
        // if a point is on boundary of geometry2
        // check points of geometry1 until point inside/outside is found
        // NOTE: skip first point because it should be already tested above
        result = range_in_geometry(geometry1, geometry2, strategy, true);
    }    
    return result;
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_RANGE_IN_GEOMETRY_HPP

/* range_in_geometry.hpp
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
*/