// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP
#define BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP


#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

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
    BOOST_MPL_ASSERT_MSG((false),
                         NOT_IMPLEMENTED_FOR_THIS_DIMENSION,
                         (mpl::size_t<Dimension>));
};

template <>
struct cross_product<2>
{
    template <typename P1, typename P2, typename ResultP>
    static inline void apply(P1 const& p1, P2 const& p2, ResultP& result)
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
    static inline void apply(P1 const& p1, P2 const& p2, ResultP& result)
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();
        assert_dimension<ResultP, 3>();

        set<0>(result, get<1>(p1) * get<2>(p2) - get<2>(p1) * get<1>(p2));
        set<1>(result, get<2>(p1) * get<0>(p2) - get<0>(p1) * get<2>(p2));
        set<2>(result, get<0>(p1) * get<1>(p2) - get<1>(p1) * get<0>(p2));
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
template <typename ResultP, typename P1, typename P2>
inline ResultP cross_product(P1 const& p1, P2 const& p2)
{
    BOOST_CONCEPT_ASSERT( (concepts::Point<ResultP>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P1>) );
    BOOST_CONCEPT_ASSERT( (concepts::ConstPoint<P2>) );

    ResultP result;
    detail::cross_product<dimension<ResultP>::value>::apply(p1, p2, result);
    return result;
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
template <typename P>
inline P cross_product(P const& p1, P const& p2)
{
    BOOST_CONCEPT_ASSERT((concepts::Point<P>));
    BOOST_CONCEPT_ASSERT((concepts::ConstPoint<P>));

    P result;
    detail::cross_product<dimension<P>::value>::apply(p1, p2, result);
    return result;
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ARITHMETIC_CROSS_PRODUCT_HPP

/* cross_product.hpp
r9lMMJl2M0GcZyGB8HVcyaqc11Deaf5Ef80m4EkzN/d9liVsCpNXinxoivltqSJSiZJQsASb5zgl7PdKcuqRz4rk1GN6jGuxDtt/YKFypKXw3/bE+/LXBb9yP+zXMjaXP27dP/qNdrDc6FsPQkcbk+bd09R2LJcXx1HALyZfZJoHo8B4ijfFuUTDFSsh5OIlF9H9KArLBInXwFN4HXeyxp7etr3K5sov1uj2vkEb5ep00CJNP6TbfSuOPuJ/PAvKuR1fYwtf/rz0wEW81KYQGACqV0FnBwzafsW6cqbfWG9GkJfgLuEvb8754r+asDe97JK0aI2NgAMRkfKZssJCgAuo6GrHl4ZWaFvlH0DA28jDPbBawW77j4IDl4bejiza3IrXF6Wdy+pHulObkJomRpmvPsa23aH9RYYTtSVuRq4+m5HPsejYSloCJlNLb0SlzHxrRyCF0qPngdgiPBVGh2Skq7TfRjL2n5CKS7c39EiThnm5hjkRfDFY08zNoTl6FeLiE/Iz90euv7N3JYBRFWd4rxxAYMMRiHIYIdyCgaBNCGA2JLoLG4yASpUKCsHQIqRhFxGpJi5owiMUrVpqrVJrrbXWKrUakGJClATwAKmKRy1Va1+MB6ICgmX7/d/MHoFwWWxtuwP55r25dmbe3PMfa1mIuLVtJH5XhKEDAqJNJZhx4mBTDqnmvj/iLV69pZlN8pao3gaYb+CNAxveTkpeEKkEXJNVg91bqwtwk5KB9Vcp3RRp3dOpKSIzmA92B+NjL1wyXIrtwUudQoapqLGNA/nGPpdmvJ/j0pz3F7s06/2YwKIsKyjJjFVT1KmrcIOXT5fxYzwc3VGOReJ4rru658glVktNugybw/A2QN4c8tYHbz3kzUZWfbwlqTe9XF+h6U9KXOtZp9WlQff2j9zBTVCiYXUNfsbnEkhz5TzjvxDKpSGCEvKiX5bTwcZ27G/ZLuOD5hHYMPnPjvg9rPx6FhifNadiA9wl4nUrvVzOgi+FB98z+DP/HdKrSrzGzPQiUTHiCiSlW71Ca4JEvfCCQFVUpPQ6kp1MUUFsS6FjDVWu3hLZH6ee4Oc85eZY41vDBk1z9YlHBrXNaho3v8CskfkGRGDtv8mKiXxHXrZju68jZZ8eiC/7hDoR8JXyDO92R+CLoD+hXV3TPnwiEWCQ0+gbTB271DxSFiX0ZBI+7rpCOJh/u5RL8Ge0Eqpl+LnRq8hPvMWinKrg5DXU+CmSiEaYcYP42Rqzr8jyj9Y6I1+AP7xG9uAM2p+Jy2/H2fmDbwdCQvmHmGXqJy9CCC1rwijpse9Ztum5WVPTRziXyipdZF6fM6qbf2j5eQ7fJZKWE2lJwpLgrYEIHcjZ5hkqSZEEMgr0aIMRvfy8OF+axEpBrObGw34J5YtHIIrxDjP458tYKMql8nGTQuHa+SNByyU3VVkXWn3tlTSIjaQF/RvAf3r5eTZ/4r5nrUhQcbHIpVLTykOSe6e5FpOCpyo+rNJtKLWWy0ahaT6CyBRTgoxDkCL0BPzpEuwfdtmw3pLrK2kZ69pb4pivT34fYfcaIT9wNmPfuVJTrEgK7qplsrc+9XPQv9PkKlY/JWbwiafYIdT87hWK9T3kv1gHT+lDJZ7q2UG5yCj1VvftBTVZHEi91UPi8eze/iEkmFPFg/OJbksgdTCz1gNhMh197UX4d11yYH+bsk+aJ+GCue4dh8f+Z5/IHjb/+qRqATlyj2Z+KJve/UHfkHyj3bp2+Bj5xlgHBid+HUhSx1fR8kLiJXzlBCu1NAUa8Peh1X8zByQZsEq1ylTkxjN4r5sqG7JkvXeKNSFk1hbK2iU7aaMvCbJyQHJS9qlI9jPyNzo=
*/