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
AtQWHUtUwVyi0xLcJn7rFL3MHWKV+YOHma5nsnXDyRgkE5nDB2biKKBe6ribQjacbt8yZjqqlfUFICN6ymbzC7NFghbU75EJUYipBN6gO/kdB9E6UCLK87u+AWxBP/n6AGTkMdLhXpClmd4GK0wUfItLXEZISqXytHWnu46IJiNZ5v1fn6Qd1ekWPsEpapERFIbUtkoDn/nsxThtiGS61gKxWWFMSTIYYpEsTlE5jU6A9IfBuR8es3HUl4Z/ob6gSEjCb36O+FC1781q8kCZztM3F8b8kXsmgK/124/2JHRNOnY4BKFBCSmTarvxFQ14S+cVlGE9oZOjv0FEKUg1+wjNo2iPnD8J5Y/RgnQohU2NDKKVTXYfKVFF5cG286bYiQIOzN+wjwD/IgGMNkss59B2TqA0QsfwcmGDMqIvryHM5x3c86i6DrJWzS1xbqMmV2X1uRhj1LUg5bO14a5EK8tyHzyLBJSyhNvPannPHqjMZMFmtX7JHDpOhgNPR+8gOgN95QOGrsue5HvQbjCC45Z+zHs//vaN8HtWofSRt5ObPyiE3hbWdxaJ3g==
*/