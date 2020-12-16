// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP
#define BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function converting, if necessary, to "a floating point" type
    \details
        - if input type is integer, type is double
        - else type is input type
    \ingroup utility
 */

template <typename T, typename PromoteIntegerTo = double>
struct promote_floating_point
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_integral<T>,
            PromoteIntegerTo,
            T
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP

/* promote_floating_point.hpp
UP5AQ0OHBoYOFRtuuqGCgYJeFBUK417hKhTYFaGgMK+KhoqFhYVNGy7ccLPCwk0LNyzcdOHCDTdc2LAwceGGTQubrn0ez+ei5+T+2P7b68V99X6d132+58dznvOc5/y4X+y8+K6xB/5M7LJG7+8X4n+bddkV0WWDLvPwQht9dV16Q2YJ0Nv9BmQVR/R++EJmXafLBkBWbfj9EMgi1+i2uhsy30V6G0GQOT/W6wuRdv/uocnGQlb3id7GBMha79bzRUAWtlbv7xRpw7hnmCY6/1WX3S92+UjXJe5aP/T6EiDrTNBlC0Q/Y619ELLGfD2fDbLADt0GDilrxKGHpV3jbPAoZKVhun65orMxPwqk7GJd9pTY9GW93bUy5l/o9RWLTfvrvrFZ8hnx5Tnph7E/eFFsb/Rju+j8il52p8i69DZ+LDZdrtf3Mxm3+3RZtbR7SJftk7F8X+/HW5LPOMP+SvIZflAvtr9L1++o2OCynu93osurer4/yFww5kez2OCEXvaU2M+IdR+JLnZ9fpyV+WHsDzpk3Lw9NNkFKWuM2+fSX+Ne4J9SVt9b4D/IjDsAb5FF6frdClnrQl12O2SlrXq7/SFzDtTzDYYs8EFdNkzyVeq6fBMy33XG/R9k1TN0u4yBzPWZboPxUnaDXvbbks9YAyZDZjP8bypknYYNZkh9E/WysyCrM84QVrGVEV/mQ9Z4VK/vAcisxpxJlbL1et/SIQsz1o9M0W+/Xt8ysamhywrpm3HPkC/jtlHPt1L6docuWyP6GXcAT4v9hurtlkjZnXq+LTKWmfp4vCC2+lwv+wPRb61x/yftPqnXt0vsYvjGT0UX407wdbGLUbZG9DP2SAck34/0sr+UMSrSZe9CFmms00ck3+/1vh0Tnzyot/t70e8ZPd+fpL/+ej9apG/zdNlpacPYK38ibRh9+1TK+uplOyGzHNV96JLYoF7X5UsZo4l6vq+kjXTj/q83yv5Tn6t9IGu9XZfdBpnzcb3snZAF2nWd/SHrDNHLDoWs4oQuGwFZZJOu3z2QWX+qy0Kl7BfG/Z/ke1+X3QdZqWGX70o/fq/LIiELW6TrHC356nTZTGljr277OVJ2u27nRMhcH+t9S5ayx/V2HxJbGeeFNMhs4bosQ+z8F71stuj3iK5fDmSNxp3g45BVJ+uyQin7G72N1SL7lS5bL2WNO5RN4hvGmbNUxveQrt9WGaMjen0vST8Mf/6htGvMt0rpx0Jdtlvqa9Tt/JrUZ8TEN0Vn42y1X2zvpZc9KHaeoOvyjpTdYdz/QVZ3UW+jQfzUiJPHRZe/Gvd/0m68Xt8H0t/Ter5WacO44z4jdjZ+A/qr1HfVuP+TflTrfbso9jPuPC5Lu8Ze9F+QWYy7XGSxNBrrpQ9krZt0WT/IbN66fndAVjFH12WQ1GfslQOk7Ke6vwyHLCxQ12UUZJGb9H7cC1mdMffDpD7DfhMhsxjtfgcy1znj/k/aCDLu/yCzGjE2VvphyGZDVv1NXTYPMuclvb4k6Vu1LlskuryuyxaL7HPdfkulPuO+KUvqa9fjy3LR2bjPeUzG4896fU9CFmicy1xi03d02Tope1ovuxEy39/qujwrOvvpsrJbvu5r26TsB8b9n7RrzN9XJN8/9TGvEp2T9LF8Vfpr7MffEJ2vGvd/IivUZbWQlV7Vyx4SXRx6u7+Wdo317T3Rz/hdrVHqM9bzE+Ivxpn4z2KXZ3Vd/iJljX1Jm7T7lnH/J+026bK/SX0P6bJ/yFwwYlOX+Lhhg6vShrFP9PSBzpXG/R9kYQd1/fpCZk3X6/ODzPJbfU4PhKy11rj/g8z3tJ4vEDKbMR4jIQs09uijISv9h57vW1I=
*/