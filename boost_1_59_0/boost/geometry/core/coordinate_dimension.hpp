// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP


#include <cstddef>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/util/type_traits_std.hpp>

namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating the number of dimensions of a point
\par Geometries:
    - point
\par Specializations should provide:
    - value (e.g. derived from std::integral_constant<std::size_t, D>)
\ingroup traits
*/
template <typename Point, typename Enable = void>
struct dimension
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Point type.",
        Point);
};

} // namespace traits

#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

// Base class derive from its own specialization of point-tag
template <typename T, typename G>
struct dimension
    : dimension<point_tag, typename point_type<T, G>::type>::type
{};

template <typename P>
struct dimension<point_tag, P>
    : std::integral_constant
        <
            std::size_t,
            traits::dimension<util::remove_cptrref_t<P>>::value
        >
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        (traits::dimension<util::remove_cptrref_t<P>>::value > 0),
        "Dimension has to be greater than 0.",
        traits::dimension<util::remove_cptrref_t<P>>
    );
};

} // namespace core_dispatch
#endif

/*!
\brief \brief_meta{value, number of coordinates (the number of axes of any geometry), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_dimension.qbk]}
*/
template <typename Geometry>
struct dimension
    : core_dispatch::dimension
        <
            typename tag<Geometry>::type,
            typename util::remove_cptrref<Geometry>::type
        >
{};

/*!
\brief assert_dimension, enables compile-time checking if coordinate dimensions are as expected
\ingroup utility
*/
template <typename Geometry, std::size_t Dimensions>
constexpr inline void assert_dimension()
{
    BOOST_STATIC_ASSERT(( dimension<Geometry>::value == Dimensions ));
}

/*!
\brief assert_dimension, enables compile-time checking if coordinate dimensions are as expected
\ingroup utility
*/
template <typename Geometry, std::size_t Dimensions>
constexpr inline void assert_dimension_less_equal()
{
    BOOST_STATIC_ASSERT(( dimension<Geometry>::value <= Dimensions ));
}

template <typename Geometry, std::size_t Dimensions>
constexpr inline void assert_dimension_greater_equal()
{
    BOOST_STATIC_ASSERT(( dimension<Geometry>::value >= Dimensions ));
}

/*!
\brief assert_dimension_equal, enables compile-time checking if coordinate dimensions of two geometries are equal
\ingroup utility
*/
template <typename G1, typename G2>
constexpr inline void assert_dimension_equal()
{
    BOOST_STATIC_ASSERT(( dimension<G1>::value == dimension<G2>::value ));
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_COORDINATE_DIMENSION_HPP

/* coordinate_dimension.hpp
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
*/