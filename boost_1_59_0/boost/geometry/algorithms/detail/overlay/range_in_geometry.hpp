// Boost.Geometry

// Copyright (c) 2017-2020 Oracle and/or its affiliates.
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
                            Strategy const& strategy)
    {
        return geometry::covered_by(point, box, strategy) ? 1 : -1;
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

    for ( ; it != end; ++it)
    {
        result = point_in_geometry_helper<Geometry2>::apply(*it, geometry2, strategy);
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
    int result = point_in_geometry_helper<Geometry2>::apply(first_point1, geometry2, strategy);
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