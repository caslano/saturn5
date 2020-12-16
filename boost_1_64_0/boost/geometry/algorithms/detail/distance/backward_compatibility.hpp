// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/tags.hpp>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/default_strategies.hpp>
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/algorithms/detail/distance/multipoint_to_geometry.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template<typename Point, typename Segment, typename Strategy>
struct point_to_segment
{
    static inline typename strategy::distance::services::return_type
        <
            Strategy,
            Point,
            typename point_type<Segment>::type
        >::type
    apply(Point const& point, Segment const& segment, Strategy const& )
    {
        typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Segment>::type,
                Strategy
            >::type segment_strategy;

        typename point_type<Segment>::type p[2];
        geometry::detail::assign_point_from_index<0>(segment, p[0]);
        geometry::detail::assign_point_from_index<1>(segment, p[1]);
        return segment_strategy.apply(point, p[0], p[1]);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Point-segment version 1, with point-point strategy
template <typename Point, typename Segment, typename Strategy>
struct distance
<
    Point, Segment, Strategy,
    point_tag, segment_tag, strategy_tag_distance_point_point,
    false
> : detail::distance::point_to_segment<Point, Segment, Strategy>
{};


// Point-line version 1, where point-point strategy is specified
template <typename Point, typename Linestring, typename Strategy>
struct distance
<
    Point, Linestring, Strategy,
    point_tag, linestring_tag, strategy_tag_distance_point_point,
    false
>
{

    static inline typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Linestring>::type
        >::type
    apply(Point const& point,
          Linestring const& linestring,
          Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
                    <
                        Point,
                        typename point_type<Linestring>::type,
                        Strategy
                    >::type ps_strategy_type;

        return detail::distance::point_to_range
            <
                Point, Linestring, closed, ps_strategy_type
            >::apply(point, linestring, ps_strategy_type());
    }
};


// Point-ring , where point-point strategy is specified
template <typename Point, typename Ring, typename Strategy>
struct distance
<
    Point, Ring, Strategy,
    point_tag, ring_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Ring>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
            Ring const& ring,
            Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Ring>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_ring
            <
                Point, Ring,
                geometry::closure<Ring>::value,
                ps_strategy_type
            >::apply(point, ring, ps_strategy_type());
    }
};


// Point-polygon , where point-point strategy is specified
template <typename Point, typename Polygon, typename Strategy>
struct distance
<
    Point, Polygon, Strategy,
    point_tag, polygon_tag, strategy_tag_distance_point_point,
    false
>
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<Polygon>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    Polygon const& polygon,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<Polygon>::type,
                Strategy
            >::type ps_strategy_type;

        return detail::distance::point_to_polygon
            <
                Point,
                Polygon,
                geometry::closure<Polygon>::value,
                ps_strategy_type
            >::apply(point, polygon, ps_strategy_type());
    }
};




template
<
    typename Point,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        Point, MultiGeometry, Strategy,
        point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy, Point, typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(Point const& point,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                Point,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Point, MultiGeometry, ps_strategy_type,
                point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(point, multigeometry, ps_strategy_type());
    }
};


template
<
    typename Geometry,
    typename MultiPoint,
    typename GeometryTag,
    typename Strategy
>
struct distance
    <
        Geometry, MultiPoint, Strategy,
        GeometryTag, multi_point_tag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type,
            typename point_type<Geometry>::type
        >::type return_type;

    static inline return_type apply(Geometry const& geometry,
                                    MultiPoint const& multipoint,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<Geometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                Geometry, MultiPoint, ps_strategy_type,
                GeometryTag, multi_point_tag,
                strategy_tag_distance_point_segment, false
            >::apply(geometry, multipoint, ps_strategy_type());
    }
};


template
<
    typename MultiPoint,
    typename MultiGeometry,
    typename MultiGeometryTag,
    typename Strategy
>
struct distance
    <
        MultiPoint, MultiGeometry, Strategy,
        multi_point_tag, MultiGeometryTag,
        strategy_tag_distance_point_point, false
    >
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<MultiPoint>::type, 
            typename point_type<MultiGeometry>::type
        >::type return_type;

    static inline return_type apply(MultiPoint const& multipoint,
                                    MultiGeometry const& multigeometry,
                                    Strategy const&)
    {
        typedef typename detail::distance::default_ps_strategy
            <
                typename point_type<MultiPoint>::type,
                typename point_type<MultiGeometry>::type,
                Strategy
            >::type ps_strategy_type;
    
        return distance
            <
                MultiPoint, MultiGeometry, ps_strategy_type,
                multi_point_tag, MultiGeometryTag,
                strategy_tag_distance_point_segment, false
            >::apply(multipoint, multigeometry, ps_strategy_type());
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_BACKWARD_COMPATIBILITY_HPP

/* backward_compatibility.hpp
jCxycaza/vCT8rm22NwHwz5I8AY11BjPraEXWCxH+OYc1+0BV7vCvS30zbWf4A/vGhM7ZErWi1+ip98Jc/XIZfVfle3bCKth7h3894041Kcl7hOp20OO74qna8azxcpz8uaBNnrcXDQUtulOV9g4GSaw2d6i/AnjHl2l9vlOi4fhHQ1/ozkfX69nP1Pv8R68vpT+oI5F8PEm3+tSyRoErGvZ096D98X0JHUnDf6w54lU9ZoO95U8+05fNHQDG7WE6SXo0OK0gvnk1r/O9/sc6tWZsOO1afpWPGGVmvOHUdaTd/FHCzXhPDm8G88epX8RK/O2y9eLxUky/8PirdYzC+7j8+N0lU/pdmxUuD9/bFNbG4jtTGJ1E3zNS7MfKOZwucxs8JF4b2OeE2HtCbF1gA06bMZxblbPz2XfhfBK/lRSL67TDw6B8ZO36xHUpjfqw45frU98yV+3wUXxvZ9N07brj2bBiaH4JUw/ukItbWdNOKueGo8ettV39XiZcP02X6vjOdQsPWExmL8Zb0u9lo58BUxYbG1ypmsvxKf0lF27il+4lbhHbZp8K1VWTsGIF0vzr174aHdYCXvqZGHHLuoke7xZJLIPw9rvjXL8PbxDTz+oos+b6u/6ylX4fYX4Wa4vaERr6f8xjKDL1Fd3PvgVj+ffQ+J8SxsaX6o+/hBcoSXMSuDqC3QQ48tXHj7lUdN/FEulzduYfoV5neRmYl9gbvHXKydenaiR97IRHlftBXNrYf/Bdyfvqzg8ncT+Dcw8gVMdMObL4HuZxJ5PtfwNWp59ikv16+vfxAfnqbGb4fPP8tYcV/7AJuxZnvZavXjivnvpoJ84/1E54777tjhUY1j0ySgcLyWEdnhQHpyxKI1zCv+0tw42V/3LUTaWPs7VFfGgfvpFHGLhs/q3QfwnHusNsZdF/Na9yj1Ls8z7NX7D5UvdSqc19+XyrxJs/LpXSH/jeyv9eRE8LWWI/TYwZ/Ea9oDnVX12qE7cZGhbcnLZ2/oS4+6blrjXU+8jpvqwxS2wei4dOMZ32Z+CFVX0ftbMPjpHTPTRM8asAbBJ654wsQHsPEbHaKN+4lVPXENHFf+5d8gz+PVzJn1eJpqa/XMd2HzvKljHv23g1BI19n01P5WtkqvBN7W+0P1qHiwakGaYG1x7Gx28H4y9lO+rw9PNeBmtrqk9aGPUsZ3mufJF44aN3xb12Wux9DWToZfRM2+DLz+plfrXPJvoDmI78yg56fhnW9Fw4EqoJEaLwQd4/yEf7ME9rvfzkptcu5e6u0Zfp86VFP8Xs2/15mozjlFLrXgJ3t3Dfz/BipG9rMXewK5H6C6J99jLm3ZOv7YBv9Z07lFsMR5vSMatutNQLzfvmrBP7hW4EEdWC4fT04rYg7mwDL2kOV/3hOPwtPdY9r1BX8qXP6xjgy3qnNi742W5BIfL4WK/tIFdj8P6Y3TVrngWLWACvpSWbD0BPvyQxZ6RCjjgpbBqlLWcPfAcLsVh0QS9fafn4B2MyvYGv8GgSq3E/npxOdlcnf+bNXoDfck0PjsbdxleW//f9aRWMEAu7F0aNFKwkn+7wsE2VeFDYfs9aUANS6oz42BeYl+uaz4KK7aUp0mk6tXoXBNHW+Nkm31045xD9Jbs2WOQfbEf4cfXwSD/v/Ylsb7A2rhY7Xc+/aFQoG8wcFa62ZsJrVOtgA2z6TqXDsIJxO3kYnQxY14o3jfOTNwvbf8kGzcbo6+ZRIdO9DOv+t4P1vlg7LTV4hJGdoGV0zfDcbn+NG32ON48+SZrLt/CtqG4kxoVk2/ffx7xgfoHF8r4eYxr5ja3s6wTfPKQ4+H6kgE0F7i8/UH1rCU8o4sc+sA=
*/