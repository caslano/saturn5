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

#ifndef BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP


#include <cstddef>

#include <boost/concept/requires.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename P1, typename P2, std::size_t Dimension, std::size_t DimensionCount>
struct dot_product_maker
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static constexpr coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<Dimension>(p1) * get<Dimension>(p2)
            + dot_product_maker<P1, P2, Dimension+1, DimensionCount>::apply(p1, p2);
    }
};

template <typename P1, typename P2, std::size_t DimensionCount>
struct dot_product_maker<P1, P2, DimensionCount, DimensionCount>
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static constexpr coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<DimensionCount>(p1) * get<DimensionCount>(p2);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Computes the dot product (or scalar product) of 2 vectors (points).
    \ingroup arithmetic
    \tparam Point1 \tparam_point
    \tparam Point2 \tparam_point
    \param p1 first point
    \param p2 second point
    \return the dot product
    
    \qbk{[heading Examples]}
    \qbk{[dot_product] [dot_product_output]}

 */
template <typename Point1, typename Point2>
// workaround for VS2015
#if !defined(_MSC_VER) || (_MSC_VER >= 1910)
constexpr
#endif
inline typename select_coordinate_type<Point1, Point2>::type dot_product(
        Point1 const& p1, Point2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<Point2>) );

    return detail::dot_product_maker
        <
            Point1, Point2,
            0, dimension<Point1>::type::value - 1
        >::apply(p1, p2);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_DOT_PRODUCT_HPP

/* dot_product.hpp
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
*/