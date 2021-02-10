// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

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

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
    {
        return get<Dimension>(p1) * get<Dimension>(p2)
            + dot_product_maker<P1, P2, Dimension+1, DimensionCount>::apply(p1, p2);
    }
};

template <typename P1, typename P2, std::size_t DimensionCount>
struct dot_product_maker<P1, P2, DimensionCount, DimensionCount>
{
    typedef typename select_coordinate_type<P1, P2>::type coordinate_type;

    static inline coordinate_type apply(P1 const& p1, P2 const& p2)
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
ke4s7XJYlt/pm5bFNy6Lk49wzjTWTn+lj3CuiIezaSuseH6vVS6pe0pL1DVld5HGvyHsHjE+lxJwlYCgKOetejZ8ThMFG658hvApXSxJoJTZku9lqDowiE/tM8ZhX9kaQecIMORujdHhGLqhPGOLVS2VbAu9PD1CYMroiEKMQb7xSUxjn8ckX3Y5hUR0KxgMBKuwuAGRtVm4eDuQ8NDQY1/HO2zZo4iI5z2a7EvxtywMclEqL2F25D79X1Y4vh+xcX8FLPfcCg+XAAIryEZsBTlyKAow3KQUydnZkY1HTnbk4JGbHQny0K2IDaiyCAn9ylwLBBE/7OyHk/0QuCQDBJKcb3YC+dvlE1yE8gmUwuXVjNxiMSYampxnCdbh99U6jEmCd3DVR7dnUmr0+m3SUyrgbgkDwTUOzvpOz+51zTbR9Cq8U0JBeJ3D6wY+g+LCOW2Fvl1CQfgOh3c023UYY22ir9BfFd/g8F6356ge9RrF73JwULTnmDptFt/k8LTfUQ1T6zSL3xPiuIY56Kpas/h9Dm8O+uqg7zZbf8DB+7ZheD3Utkl8TXgXV8KubWvN8mvCv/1B13F79hb214SDTXugapquN8dPR1po0O9pg84WKggPU7M3MDp9toUK0scD21D7uvRBkRB6JSHO
*/