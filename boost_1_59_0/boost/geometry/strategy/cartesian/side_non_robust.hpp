// Boost.Geometry

// Copyright (c) 2020-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_NON_ROBUST_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_NON_ROBUST_HPP

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/precise_math.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace side
{

/*!
\brief Predicate to check at which side of a segment a point lies:
    left of segment (>0), right of segment (< 0), on segment (0).
\ingroup strategies
\tparam CalculationType \tparam_calculation
\details This predicate determines at which side of a segment a point lies
*/
template
<
    typename CalculationType = void
>
struct side_non_robust
{
public:
    //! \brief Computes double the signed area of the CCW triangle p1, p2, p
    template
    <
        typename P1,
        typename P2,
        typename P
    >
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType,
                P1,
                P2,
                P
            >::type CoordinateType;
        typedef typename select_most_precise
            <
                CoordinateType,
                double
            >::type PromotedType;

        CoordinateType const x = get<0>(p);
        CoordinateType const y = get<1>(p);

        CoordinateType const sx1 = get<0>(p1);
        CoordinateType const sy1 = get<1>(p1);
        CoordinateType const sx2 = get<0>(p2);
        CoordinateType const sy2 = get<1>(p2);

        //non-robust 1
        //the following is 2x slower in some generic cases when compiled with g++
        //(tested versions 9 and 10)
        //
        //auto detleft = (sx1 - x) * (sy2 - y);
        //auto detright = (sy1 - y) * (sx2 - x);
        //return detleft > detright ? 1 : (detleft < detright ? -1 : 0 );

        //non-robust 2
        PromotedType const dx = sx2 - sx1;
        PromotedType const dy = sy2 - sy1;
        PromotedType const dpx = x - sx1;
        PromotedType const dpy = y - sy1;

        PromotedType sv = geometry::detail::determinant<PromotedType>
                (
                    dx, dy,
                    dpx, dpy
                );
        PromotedType const zero = PromotedType();

        return sv == zero ? 0 : sv > zero ? 1 : -1;
    }

};

}} // namespace strategy::side

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_NON_ROBUST_HPP

/* side_non_robust.hpp
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
*/