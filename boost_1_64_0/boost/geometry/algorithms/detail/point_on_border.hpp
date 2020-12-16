// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.Dimension. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP


#include <cstddef>

#include <boost/range.hpp>
#include <boost/static_assert.hpp>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/ring_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>

#include <boost/geometry/util/condition.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_on_border
{


struct get_point
{
    template <typename Point>
    static inline bool apply(Point& destination, Point const& source)
    {
        destination = source;
        return true;
    }
};


struct point_on_range
{
    // Version with iterator
    template<typename Point, typename Iterator>
    static inline bool apply(Point& point, Iterator begin, Iterator end)
    {
        if (begin == end)
        {
            return false;
        }

        geometry::detail::conversion::convert_point_to_point(*begin, point);
        return true;
    }

    // Version with range
    template<typename Point, typename Range>
    static inline bool apply(Point& point, Range const& range)
    {
        return apply(point, boost::begin(range), boost::end(range));
    }
};


struct point_on_polygon
{
    template<typename Point, typename Polygon>
    static inline bool apply(Point& point, Polygon const& polygon)
    {
        return point_on_range::apply(point, exterior_ring(polygon));
    }
};


struct point_on_box
{
    template<typename Point, typename Box>
    static inline bool apply(Point& point, Box const& box)
    {
        detail::assign::assign_box_2d_corner<min_corner, min_corner>(box, point);
        return true;
    }
};


template <typename Policy>
struct point_on_multi
{
    template<typename Point, typename MultiGeometry>
    static inline bool apply(Point& point, MultiGeometry const& multi)
    {
        // Take a point on the first multi-geometry
        // (i.e. the first that is not empty)
        for (typename boost::range_iterator
                <
                    MultiGeometry const
                >::type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            if (Policy::apply(point, *it))
            {
                return true;
            }
        }
        return false;
    }
};


}} // namespace detail::point_on_border
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename GeometryTag>
struct point_on_border
{};

template <>
struct point_on_border<point_tag>
    : detail::point_on_border::get_point
{};

template <>
struct point_on_border<linestring_tag>
    : detail::point_on_border::point_on_range
{};

template <>
struct point_on_border<ring_tag>
    : detail::point_on_border::point_on_range
{};

template <>
struct point_on_border<polygon_tag>
    : detail::point_on_border::point_on_polygon
{};

template <>
struct point_on_border<box_tag>
    : detail::point_on_border::point_on_box
{};


template <>
struct point_on_border<multi_polygon_tag>
    : detail::point_on_border::point_on_multi
        <
            detail::point_on_border::point_on_polygon
        >
{};


template <>
struct point_on_border<multi_linestring_tag>
    : detail::point_on_border::point_on_multi
        <
            detail::point_on_border::point_on_range
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief Take point on a border
\ingroup overlay
\tparam Geometry geometry type. This also defines the type of the output point
\param point to assign
\param geometry geometry to take point from
\return TRUE if successful, else false.
    It is only false if polygon/line have no points
\note for a polygon, it is always a point on the exterior ring
 */
template <typename Point, typename Geometry>
inline bool point_on_border(Point& point, Geometry const& geometry)
{
    concepts::check<Point>();
    concepts::check<Geometry const>();

    return dispatch::point_on_border
            <
                typename tag<Geometry>::type
            >::apply(point, geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_ON_BORDER_HPP

/* point_on_border.hpp
+Z6/d6WvFPl+cczKumZ2Fg20MtD30vUZnz+XZz/+izrtPfjN+MCYsLOL89idjeoz4SroVzRZ7AVTfQKZVs/Stbe1cz1kwrYe4np++OT83q2ZE2I/+DTZL9t+FhuZReynvNd1L6HzSN+mvC1ThKPquTz7ZmF5MCpmfg4m82Ak6WTXHydj7USlEW9Uch1Zi/CIyaaOJOEI70Ph2DCkWfQtPyDSXM51/JpVLexGChaZ9vah7SmB8kk7+R+HZdo/hLR/GGm/aw/b1IwtK+Qsiq64iCpiCbP5v8zjeb2i5fwdKxradn6Q9CsvosQiHKNwM/mXbEtLhZ3XsG81qLYUMNh5rOrDy/6UXzbKJufXVz8avPa1etCTvO1JD2F7P0Zre3a+pgL1piw/cS/Y/5zuZfufe1H69hPpm5unL4TPC+Ysd+680mRxTyC+w30yPzsbPmPz4pOr74P1wbz45GjTwedg8AlfM8i/vje8KvLSKUeZh07jJ8s5U1VeCV5JeH8v8v0HZMtoLfYiVwkfWRwzMuoXyWxG0Ort1+WDB+m63JS1YF1eIery+ajL40JW3Ja3BjootmzZkjqWqIE53lDMP75d33d2YltcKNIwB7aoEfqdBf4tq5g3A3LqZd86njFz+uxASdNA1Lvh46ov27qlg+uTjxp75lGfNIHfdJMO1AWYY7DzugMkuh+wZ8Zk1y14vGvuS86YB/GCezxnCLsMOrssrqP/hGUkKPqMdZ5x5RmZUbR3LdjHMZ1B2cexNuZzHLNlHyeP+7799mumstksCg+6Opnr+LNE/3QO4bd7wfHETqcbh2/1qApPmLsZgvOmdxo+aixyt5NloX7a7vNMu5Zq3dTd59q2dRl7vqYe60wfE2ndJW1b11i3UNYbGh51frFAHqZcHYpytbSguXR6ZZD+q52e8MsF5n7nzZsx3fGdCb5Rcw+vHjJ07uHjFGfLbmW7fTkUn+e6joAszCuYvg+vGSyYrOvUvbw69IHqVZ3SwP1mp1MRsVqYZz+5CjzmE72sWxttmkS/GH6+SOT9VptvC1X7jHDU2anccdz+FpKh16GKsLeU7MdvvETl0VEUX+fRMpOeovztsTzMHkVD7dEk7VFk0tG4sJHThnBOe+SIA3s0wx7h8bs6kq3yMJoIU3zfR1YSD93utAjdn7b5smRho6whAZD142Pjsm8u+LxXWz44KwjeR0veu9FR1ruUTOa7JoTvsczX0Pa310q2HMzVp8wdJ3jHvkG0dWUw93o8yS7mfgzeqxL6FNu+xcqGWjahCCMv/HOAuj90ohxvFpt48hggwjn9aPnC2YHtxiJMcU4MkW3Dk428ziQ1IBzuKM60dnVnw7uK3borjwn2Gto2zEffv1X2tfby9V68vK4hQQpZxTTQ2r0/cF60TpxHrefvkV6DeE9hIX/H1HnQfdV50HJ5HlSsW9Ziv3e70PmE3HaM6IPnn05TnpOq/j7voKF+vk7otMXe1yedVoSj/CF3HJbdFVIvnCxl27S1NDYuZGeUAF5f0m2jCb852sTv6t3ocZjaDFqu30j9JvTNu4WsbaYuXJNoqG9gWQyQddBwrEXUqXeumincJsuvum+42IO/Qr8+4/tmzlOtWdN8ojmpRpEBs36RHEwl2zNmO5Tv6ymh+0kF7N2Sa4oPHMTrjrRXCnNvak0zTXL4HKHaxzFAOPQfRPzwvTwbJ4szf3H6qX0ymya7sIFjDRN4lsWytV4VkFUB2s0OF/taWba/swV+Dx3sHqgzCCZ1OBN9nAdD1li/iTVWisf6SV4V6t6Gc8DrAfCStHqt+rzJyAfgw/LhAra1ocm9b+qiyVjbFrSPlUXRl3jboOs90FXIyZmnFyM=
*/