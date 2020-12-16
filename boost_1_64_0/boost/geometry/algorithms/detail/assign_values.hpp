// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


#include <boost/geometry/util/is_inverse_spheroidal_coordinates.hpp>
#include <boost/geometry/util/for_each_coordinate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace assign
{


template <std::size_t Index, std::size_t Dimension, std::size_t DimensionCount>
struct initialize
{
    template <typename Box>
    static inline void apply(Box& box, typename coordinate_type<Box>::type const& value)
    {
        geometry::set<Index, Dimension>(box, value);
        initialize<Index, Dimension + 1, DimensionCount>::apply(box, value);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct initialize<Index, DimensionCount, DimensionCount>
{
    template <typename Box>
    static inline void apply(Box&, typename coordinate_type<Box>::type const&)
    {}
};


struct assign_zero_point
{
    template <typename Point>
    static inline void apply(Point& point)
    {
        geometry::assign_value(point, 0);
    }
};


struct assign_inverse_box_or_segment
{

    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename point_type<BoxOrSegment>::type point_type;
        typedef typename coordinate_type<point_type>::type bound_type;

        initialize<0, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, geometry::bounds<bound_type>::highest()
        );
        initialize<1, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, geometry::bounds<bound_type>::lowest()
        );
    }

};


struct assign_zero_box_or_segment
{
    template <typename BoxOrSegment>
    static inline void apply(BoxOrSegment& geometry)
    {
        typedef typename coordinate_type<BoxOrSegment>::type coordinate_type;

        initialize<0, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, coordinate_type()
        );
        initialize<1, 0, dimension<BoxOrSegment>::type::value>::apply(
            geometry, coordinate_type()
        );
    }
};


template
<
    std::size_t Corner1, std::size_t Corner2,
    typename Box, typename Point
>
inline void assign_box_2d_corner(Box const& box, Point& point)
{
    // Be sure both are 2-Dimensional
    assert_dimension<Box, 2>();
    assert_dimension<Point, 2>();

    // Copy coordinates
    typedef typename coordinate_type<Point>::type coordinate_type;

    geometry::set<0>(point, boost::numeric_cast<coordinate_type>(get<Corner1, 0>(box)));
    geometry::set<1>(point, boost::numeric_cast<coordinate_type>(get<Corner2, 1>(box)));
}



template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct assign_point_to_index
{

    static inline void apply(Point const& point, Geometry& geometry)
    {
        geometry::set<Index, Dimension>(geometry, boost::numeric_cast
            <
                typename coordinate_type<Geometry>::type
            >(geometry::get<Dimension>(point)));

        assign_point_to_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(point, geometry);
    }
};

template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t DimensionCount
>
struct assign_point_to_index
    <
        Geometry, Point,
        Index,
        DimensionCount, DimensionCount
    >
{
    static inline void apply(Point const& , Geometry& )
    {
    }
};


template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct assign_point_from_index
{

    static inline void apply(Geometry const& geometry, Point& point)
    {
        geometry::set<Dimension>( point, boost::numeric_cast
            <
                typename coordinate_type<Point>::type
            >(geometry::get<Index, Dimension>(geometry)));

        assign_point_from_index
            <
                Geometry, Point, Index, Dimension + 1, DimensionCount
            >::apply(geometry, point);
    }
};

template
<
    typename Geometry, typename Point,
    std::size_t Index,
    std::size_t DimensionCount
>
struct assign_point_from_index
    <
        Geometry, Point,
        Index,
        DimensionCount, DimensionCount
    >
{
    static inline void apply(Geometry const&, Point&)
    {
    }
};


template <typename Geometry>
struct assign_2d_box_or_segment
{
    typedef typename coordinate_type<Geometry>::type coordinate_type;

    // Here we assign 4 coordinates to a box of segment
    // -> Most logical is: x1,y1,x2,y2
    // In case the user reverses x1/x2 or y1/y2, for a box, we could reverse them (THAT IS NOT IMPLEMENTED)

    template <typename Type>
    static inline void apply(Geometry& geometry,
                Type const& x1, Type const& y1, Type const& x2, Type const& y2)
    {
        geometry::set<0, 0>(geometry, boost::numeric_cast<coordinate_type>(x1));
        geometry::set<0, 1>(geometry, boost::numeric_cast<coordinate_type>(y1));
        geometry::set<1, 0>(geometry, boost::numeric_cast<coordinate_type>(x2));
        geometry::set<1, 1>(geometry, boost::numeric_cast<coordinate_type>(y2));
    }
};


}} // namespace detail::assign
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename GeometryTag, typename Geometry, std::size_t DimensionCount>
struct assign
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Point>
struct assign<point_tag, Point, 2>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
    }
};

template <typename Point>
struct assign<point_tag, Point, 3>
{
    typedef typename coordinate_type<Point>::type coordinate_type;

    template <typename T>
    static inline void apply(Point& point, T const& c1, T const& c2, T const& c3)
    {
        set<0>(point, boost::numeric_cast<coordinate_type>(c1));
        set<1>(point, boost::numeric_cast<coordinate_type>(c2));
        set<2>(point, boost::numeric_cast<coordinate_type>(c3));
    }
};

template <typename Box>
struct assign<box_tag, Box, 2>
    : detail::assign::assign_2d_box_or_segment<Box>
{};

template <typename Segment>
struct assign<segment_tag, Segment, 2>
    : detail::assign::assign_2d_box_or_segment<Segment>
{};



template <typename GeometryTag, typename Geometry>
struct assign_zero {};


template <typename Point>
struct assign_zero<point_tag, Point>
    : detail::assign::assign_zero_point
{};

template <typename Box>
struct assign_zero<box_tag, Box>
    : detail::assign::assign_zero_box_or_segment
{};

template <typename Segment>
struct assign_zero<segment_tag, Segment>
    : detail::assign::assign_zero_box_or_segment
{};


template <typename GeometryTag, typename Geometry>
struct assign_inverse {};

template <typename Box>
struct assign_inverse<box_tag, Box>
    : detail::assign::assign_inverse_box_or_segment
{};

template <typename Segment>
struct assign_inverse<segment_tag, Segment>
    : detail::assign::assign_inverse_box_or_segment
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_ASSIGN_VALUES_HPP

/* assign_values.hpp
671qfZt4T5W8seaKtHn/CMqQx3963mg69LgH8ml+k63Z35J2T4onGiErrSWAtpb+SnyTt4NgB0FeqQ9ZGdTfUvq9n77HjGC8HoY4wrN52VfRzpHrSEQ729FSeQX9qzlOLqbbv1LJRHQHBHxJZvqUTAdCx1t5jtOlM1+ssR7s0mHZ54FmNcp4PvR0iNDxXPw+MXq+GvcNUUeE0gjmqpPyPmAqF9snT8SH+u0Jbh++gHjH7By/R2MpN099aKU8C2PtnW6QaW+t6wquXJNAvedutVq3Owx5WlRZ4PzdjqVTeoQouyPBdwv0k7L8Eq6/xfrJcfioSqMfynJqiGb7WIekn6xrzKEb8imkmwF6q4FxSB8Yi0Cn1Pey6lyAMyRHC93NLeI+HtgE96XqlB0uqXSftLN66LOB/sqxX9b4XbQR2lc2gcdhwjbl3qYBtceoBWlUeJANZXsM+FSgbFv9eoj9QTJuBXi0qTztWuY+madjRR7lPZBT9H096Lt0AX8K/MVKCvs4BMP4V9oh3ScWgTNRzXOtFXV8K+SU+wmPrwzrrULN23+wMrzPrpbbxsA/z1Dzd+tYrqD91f2ZXtF+bo3o+8l2pN/XO/pxYm8m06Ui6NZDdlpHs7IvnOC9IsPb0Z87AeFBytuqwm1p46p2Og3WuNa1mssbu5rb3O3hBTEwxhiqLLRmn0uom2AZIP3EiPATSVHPUsomT650nyzLNPSYEb54RPnvnGpXN4LmFEGTVDSbQUO0lmYLaD4EPFkPPij6sVl8UsbTfXvEHiMqm1BbtxW8H1BjtDNF+0Y0Fvcjwg4pnvybxqE3bCqDsNyfRbhifwN8Eb5zKt13ghpvfFzoW68JZr3Ra4mUP+vLzld5Pkbl+QIV36zit/n5RHw7fZ30SV9xYSX2xwHnCPqOpu8w+pbQtx99B4RoJnkX+f1R0Myjb4HGI/k/o3jvRd8swfMwfJL3JSpPh6k8fU6VC/YEUTjsP6+otGvpXK4Utvm9UvAflmUF/lcJP3884oZhv190cVRfxd1SyuavVv79GsFvWNWh61gWoouw068SLHK+7V28Q/L1SufL/jrRC4UXU3iMM7At7XX9/el4JtOW7ugZWR+3SeWNzXtv2crOxo4VbfTGH3d6QhD4wu3cd5JnO/pSGdrOwmfKbHnkMvH0SDKbwJti+h4VvK/w7cri5rVmhM40pk7O9QzxPPF3LI9+ksmdybuhUp7Ja29rbalfe+zKulZzBNjPm4IWmDtlBTbZN5B8Bgos+1HfVTZ3k7Krm+ELv1c55t1HTszuFW0NXCoKLsrm1iBd+h3UgduUPLdDnu+j3twBee4EXoG7YdLxk6UcCCP9H4K+KS/9qvnm+bQmNK+Ck45hnndXhs9qZ9WY45YycY7IHs3muxKo7DM5t0kkOLN9lxlnMJzEB/6T5hyROCv5o0o7Z9drp8YJxvN2BLNvk6CffU+lPKu9cb65I9DMqNmMBcG8d2yiPqwQ9wUyQNrUvZWF9uc2NrS096SzmyUbBYM+7/f55LmX+L7KkEzi7tz0QN/CefMMMHx3bv+KTguUdXzTIXPnonr4a6AON5EmtSfTm5n3T2x68f4Ey0rlJO8EHkimhzvimWQu3Rdv6TdHgGnwmBZyJdr9lAL/kI6vN0/YpeP9LQ2SXyIF2QN5RkLxPR+AvOBDPibad+1OvuunRfquPfPMyT8Av7UIfutnIb+1tJEuY6lr7V5Rt5zrvoIR7zHO7oXdnOWRJw728RDs48Cwv03S+zCb/b2cD1u5jQu2ZZEhnfIbn49E+N7Rflf4XJkO6nFDcrgnMdJu0+QxsK3nqLcSgcrH9/s/j0i7ezm9DERTZEH6ElrA77M=
*/