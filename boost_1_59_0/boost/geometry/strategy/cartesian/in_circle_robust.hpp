// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019 Tinko Bartels, Berlin, Germany.

// Contributed and/or modified by Tinko Bartels,
//   as part of Google Summer of Code 2019 program.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_IN_CIRCLE_ROBUST_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_IN_CIRCLE_ROBUST_HPP

#include<boost/geometry/util/precise_math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace in_circle
{

/*!
\brief Adaptive precision predicate to check whether a fourth point lies inside the circumcircle of the first three points:
    inside (>0), outside (< 0), on the boundary (0).
\ingroup strategies
\tparam CalculationType \tparam_calculation (numeric_limits<ct>::epsilon() and numeric_limits<ct>::digits must be supported for calculation type ct)
\tparam Robustness std::size_t value from 0 (fastest) to 2 (default, most precise).
\details This predicate determines whether a fourth point lies inside the circumcircle of the first three points using an algorithm that is adapted from incircle as described in "Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric Predicates" by Jonathan Richard Shewchuk ( https://dl.acm.org/citation.cfm?doid=237218.237337 ). More information and copies of the paper can also be found at https://www.cs.cmu.edu/~quake/robust.html . It is designed to be adaptive in the sense that it should be fast for inputs that lead to correct results with plain float operations but robust for inputs that require higher precision arithmetics.
 */
template <typename CalculationType = double, std::size_t Robustness = 2>
class in_circle_robust
{
public:
    template <typename P1, typename P2, typename P3, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P3 const& p3, P const& p)
    {
        std::array<CalculationType, 2> pa {
            { boost::geometry::get<0>(p1), boost::geometry::get<1>(p1) }};
        std::array<CalculationType, 2> pb {
            { boost::geometry::get<0>(p2), boost::geometry::get<1>(p2) }};
        std::array<CalculationType, 2> pc {
            { boost::geometry::get<0>(p3), boost::geometry::get<1>(p3) }};
        std::array<CalculationType, 2> pd {
            { boost::geometry::get<0>(p), boost::geometry::get<1>(p) }};
        CalculationType det =
            boost::geometry::detail::precise_math::incircle
                <
                    CalculationType,
                    Robustness
                >(pa, pb, pc, pd);
        return det > 0 ? 1
                       : det < 0 ? -1 : 0;
    }

};

} // namespace in_circle

} // namespace strategy

}} // namespace boost::geometry::strategy

#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_IN_CIRCLE_ROBUST_HPP

/* in_circle_robust.hpp
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
*/