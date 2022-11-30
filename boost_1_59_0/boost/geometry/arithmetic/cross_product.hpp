// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.

// This file was modified by Oracle on 2016-2020.
// Modifications copyright (c) 2016-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP


#include <cstddef>
#include <type_traits>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/make.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/static_assert.hpp>

#include <boost/geometry/geometries/concepts/point_concept.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <std::size_t Dimension>
struct cross_product
{
    // We define cross product only for 2d (see Wolfram) and 3d.
    // In Math, it is also well-defined for 7-dimension.
    // Generalisation of cross product to n-dimension is defined as
    // wedge product but it is not direct analogue to binary cross product.
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this Dimension.",
        std::integral_constant<std::size_t, Dimension>);
};

template <>
struct cross_product<2>
{
    template <typename P1, typename P2, typename ResultP>
    static void apply(P1 const& p1, P2 const& p2, ResultP& result)
    {
        assert_dimension<P1, 2>();
        assert_dimension<P2, 2>();
        assert_dimension<ResultP, 2>();

        // For 2-dimensions, analog of the cross product U(x,y) and V(x,y) is
        // Ux * Vy - Uy * Vx
        // which is returned as 0-component (or X) of 2d vector, 1-component is undefined.
        set<0>(result, get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
    }
};

template <>
struct cross_product<3>
{
    template <typename P1, typename P2, typename ResultP>
    static void apply(P1 const& p1, P2 const& p2, ResultP& result)
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();
        assert_dimension<ResultP, 3>();

        set<0>(result, get<1>(p1) * get<2>(p2) - get<2>(p1) * get<1>(p2));
        set<1>(result, get<2>(p1) * get<0>(p2) - get<0>(p1) * get<2>(p2));
        set<2>(result, get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
    }

    template <typename ResultP, typename P1, typename P2>
    static constexpr ResultP apply(P1 const& p1, P2 const& p2)
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();
        assert_dimension<ResultP, 3>();

        return traits::make<ResultP>::apply(
                get<1>(p1) * get<2>(p2) - get<2>(p1) * get<1>(p2),
                get<2>(p1) * get<0>(p2) - get<0>(p1) * get<2>(p2),
                get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief Computes the cross product of two vectors.
\details All vectors should have the same dimension, 3 or 2.
\ingroup arithmetic
\param p1 first vector
\param p2 second vector
\return the cross product vector

*/

template
<
    typename ResultP, typename P1, typename P2,
    std::enable_if_t
        <
            dimension<ResultP>::value != 3
         || ! traits::make<ResultP>::is_specialized,
            int
        > = 0
>
inline ResultP cross_product(P1 const& p1, P2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<ResultP>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P2>) );

    ResultP result;
    detail::cross_product<dimension<ResultP>::value>::apply(p1, p2, result);
    return result;
}

template
<
    typename ResultP, typename P1, typename P2,
    std::enable_if_t
        <
            dimension<ResultP>::value == 3
         && traits::make<ResultP>::is_specialized,
            int
        > = 0
>
// workaround for VS2015
#if !defined(_MSC_VER) || (_MSC_VER >= 1910)
constexpr
#endif
inline ResultP cross_product(P1 const& p1, P2 const& p2)
{
    BOOST_CONCEPT_ASSERT((concepts::Point<ResultP>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P1>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P2>));

    return detail::cross_product<3>::apply<ResultP>(p1, p2);
}

/*!
\brief Computes the cross product of two vectors.
\details All vectors should have the same dimension, 3 or 2.
\ingroup arithmetic
\param p1 first vector
\param p2 second vector
\return the cross product vector

\qbk{[heading Examples]}
\qbk{[cross_product] [cross_product_output]}
*/
template
<
    typename P,
    std::enable_if_t
        <
            dimension<P>::value != 3
         || ! traits::make<P>::is_specialized,
            int
        > = 0
>
inline P cross_product(P const& p1, P const& p2)
{
    BOOST_CONCEPT_ASSERT((concepts::Point<P>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P>));

    P result;
    detail::cross_product<dimension<P>::value>::apply(p1, p2, result);
    return result;
}


template
<
    typename P,
    std::enable_if_t
        <
            dimension<P>::value == 3
         && traits::make<P>::is_specialized,
            int
        > = 0
>
// workaround for VS2015
#if !defined(_MSC_VER) || (_MSC_VER >= 1910)
constexpr
#endif
inline P cross_product(P const& p1, P const& p2)
{
    BOOST_CONCEPT_ASSERT((concepts::Point<P>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P>));

    return detail::cross_product<3>::apply<P>(p1, p2);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP

/* cross_product.hpp
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
*/