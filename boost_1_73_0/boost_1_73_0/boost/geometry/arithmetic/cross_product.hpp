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
3ADzcIk9FmBjsrcROlwVd2W/3lG42hsMgmT8tKRgLPKA7x5LOe4Z+IEGmTzFZrIXBUH0wBsz3FZ+I31yy8o77pwFxj/oIMKDn7GhPkGiQPs3T6Dng8jEjWH8jpYpUuH7577DQ77Nm0+xB57m+8a4psbs54QM302uL++mZ5efyNV1vg/drt9xJq084UBv+tUPnoizTCGKIQRfvZucZjckXh0o5UADiTwWJ2JXYhQFoNJNsJzbIINoFVdcVs1b7lnKlYO6AZ5wUuDb0fexTYVFgWE7jfMfwfUapYsZX2dd0qJhDsnNBMyQTnlNWUF/8CFK3EjhAcLNFGLIzxfQduynEOgExzAahmAhcfch9Pz7ZZwZXOZAvhOziKM0QsoJmdPUmWWF6uckyybsacAwIvbKtlmxA44dNoOgjRnEhXuUVcY5L4pzEBbdgeUPvIfUeKrFOM2kpRsk6UMEarsMxHARscolKQUJIPtzjLb7iAZJfl9oRSweYlGcUtsPoJpyC2AqIDzIKdKbp8qc0TCVQ4ZHcXGCUAfzpli+8AS/BRUlCVZvsM4E6quob0gjWoD1/W+0mKoQU3Z+PO/A40uHZdkilgz/m8gbikkv/FVyZcV5KGn5TsgxJmN4zzemajvRpLYVXella3pUIDxcj9Et
*/