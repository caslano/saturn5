// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_MAKE_HPP

#include <boost/geometry/algorithms/assign.hpp>

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
template <typename Geometry, typename Type>
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
template <typename Geometry, typename Type>
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