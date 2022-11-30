// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP

#include <type_traits>

#include <boost/geometry/algorithms/assign.hpp>

#include <boost/geometry/core/make.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace make
{

/*!
\brief Construct a geometry
\ingroup make
\tparam Geometry \tparam_geometry
\tparam Range \tparam_range_point
\param range \param_range_point
\return The constructed geometry, here: a linestring or a ring
\qbk{distinguish, with a range}
\qbk{
[heading Example]
[make_with_range] [make_with_range_output]
[heading See also]
\* [link geometry.reference.algorithms.assign.assign_points assign]
}
 */
template <typename Geometry, typename Range>
inline Geometry make_points(Range const& range)
{
    concepts::check<Geometry>();

    Geometry geometry;
    geometry::append(geometry, range);
    return geometry;
}

}} // namespace detail::make
#endif // DOXYGEN_NO_DETAIL

/*!
\brief Construct a geometry
\ingroup make
\details
\note It does not work with array-point types, like int[2]
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param c1 \param_x
\param c2 \param_y
\return The constructed geometry, here: a 2D point

\qbk{distinguish, 2 coordinate values}
\qbk{
[heading Example]
[make_2d_point] [make_2d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_values_3_2_coordinate_values assign]
}
*/
template
<
    typename Geometry,
    typename Type,
    std::enable_if_t<! traits::make<Geometry>::is_specialized, int> = 0
>
inline Geometry make(Type const& c1, Type const& c2)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2);
    return geometry;
}


template
<
    typename Geometry,
    typename Type,
    std::enable_if_t<traits::make<Geometry>::is_specialized, int> = 0
>
constexpr inline Geometry make(Type const& c1, Type const& c2)
{
    concepts::check<Geometry>();

    // NOTE: This is not fully equivalent to the above because assign uses
    //       numeric_cast which can't be used here since it's not constexpr.
    return traits::make<Geometry>::apply(c1, c2);
}


/*!
\brief Construct a geometry
\ingroup make
\tparam Geometry \tparam_geometry
\tparam Type \tparam_numeric to specify the coordinates
\param c1 \param_x
\param c2 \param_y
\param c3 \param_z
\return The constructed geometry, here: a 3D point

\qbk{distinguish, 3 coordinate values}
\qbk{
[heading Example]
[make_3d_point] [make_3d_point_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_values_4_3_coordinate_values assign]
}
 */
template
<
    typename Geometry,
    typename Type,
    std::enable_if_t<! traits::make<Geometry>::is_specialized, int> = 0
>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3);
    return geometry;
}

template
<
    typename Geometry,
    typename Type,
    std::enable_if_t<traits::make<Geometry>::is_specialized, int> = 0
>
constexpr inline Geometry make(Type const& c1, Type const& c2, Type const& c3)
{
    concepts::check<Geometry>();

    // NOTE: This is not fully equivalent to the above because assign uses
    //       numeric_cast which can't be used here since it's not constexpr.
    return traits::make<Geometry>::apply(c1, c2, c3);
}


template <typename Geometry, typename Type>
inline Geometry make(Type const& c1, Type const& c2, Type const& c3, Type const& c4)
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign
        <
            typename tag<Geometry>::type,
            Geometry,
            geometry::dimension<Geometry>::type::value
        >::apply(geometry, c1, c2, c3, c4);
    return geometry;
}





/*!
\brief Construct a box with inverse infinite coordinates
\ingroup make
\details The make_inverse function initializes a 2D or 3D box with large coordinates, the
    min corner is very large, the max corner is very small. This is useful e.g. in combination
    with the expand function, to determine the bounding box of a series of geometries.
\tparam Geometry \tparam_geometry
\return The constructed geometry, here: a box

\qbk{
[heading Example]
[make_inverse] [make_inverse_output]

[heading See also]
\* [link geometry.reference.algorithms.assign.assign_inverse assign_inverse]
}
 */
template <typename Geometry>
inline Geometry make_inverse()
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign_inverse
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

/*!
\brief Construct a geometry with its coordinates initialized to zero
\ingroup make
\details The make_zero function initializes a 2D or 3D point or box with coordinates of zero
\tparam Geometry \tparam_geometry
\return The constructed and zero-initialized geometry
 */
template <typename Geometry>
inline Geometry make_zero()
{
    concepts::check<Geometry>();

    Geometry geometry;
    dispatch::assign_zero
        <
            typename tag<Geometry>::type,
            Geometry
        >::apply(geometry);
    return geometry;
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP

/* make.hpp
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
*/