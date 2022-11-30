// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019 Tinko Bartels, Berlin, Germany.

// Contributed and/or modified by Tinko Bartels,
//   as part of Google Summer of Code 2019 program.

// This file was modified by Oracle on 2021.
// Modifications copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_ROBUST_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_ROBUST_HPP

#include <boost/geometry/core/config.hpp>
#include <boost/geometry/strategy/cartesian/side_non_robust.hpp>

#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/precise_math.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace side
{

struct epsilon_equals_policy
{
public:
    template <typename Policy, typename T1, typename T2>
    static bool apply(T1 const& a, T2 const& b, Policy const& policy)
    {
        return boost::geometry::math::detail::equals_by_policy(a, b, policy);
    }
};

struct fp_equals_policy
{
public:
    template <typename Policy, typename T1, typename T2>
    static bool apply(T1 const& a, T2 const& b, Policy const&)
    {
        return a == b;
    }
};


/*!
\brief Adaptive precision predicate to check at which side of a segment a point lies:
    left of segment (>0), right of segment (< 0), on segment (0).
\ingroup strategies
\tparam CalculationType \tparam_calculation (numeric_limits<ct>::epsilon() and numeric_limits<ct>::digits must be supported for calculation type ct)
\tparam Robustness std::size_t value from 0 (fastest) to 3 (default, guarantees correct results).
\details This predicate determines at which side of a segment a point lies using an algorithm that is adapted from orient2d as described in "Adaptive Precision Floating-Point Arithmetic and Fast Robust Geometric Predicates" by Jonathan Richard Shewchuk ( https://dl.acm.org/citation.cfm?doid=237218.237337 ). More information and copies of the paper can also be found at https://www.cs.cmu.edu/~quake/robust.html . It is designed to be adaptive in the sense that it should be fast for inputs that lead to correct results with plain float operations but robust for inputs that require higher precision arithmetics.
 */
template
<
    typename CalculationType = void,
    typename EqualsPolicy = epsilon_equals_policy,
    std::size_t Robustness = 3
>
struct side_robust
{

    template <typename CT>
    struct epsilon_policy
    {
        using Policy = boost::geometry::math::detail::equals_factor_policy<CT>;

        epsilon_policy() {}

        template <typename Type>
        epsilon_policy(Type const& a, Type const& b, Type const& c, Type const& d)
            : m_policy(a, b, c, d)
        {}
        Policy m_policy;

    public:

        template <typename T1, typename T2>
        bool apply(T1 a, T2 b) const
        {
            return EqualsPolicy::apply(a, b, m_policy);
        }
    };

public:

    typedef cartesian_tag cs_tag;

    //! \brief Computes the sign of the CCW triangle p1, p2, p
    template
    <
        typename PromotedType,
        typename P1,
        typename P2,
        typename P,
        typename EpsPolicyInternal,
        std::enable_if_t<std::is_fundamental<PromotedType>::value, int> = 0
    >
    static inline PromotedType side_value(P1 const& p1,
                                          P2 const& p2,
                                          P const& p,
                                          EpsPolicyInternal& eps_policy)
    {
        using vec2d = ::boost::geometry::detail::precise_math::vec2d<PromotedType>;
        vec2d pa;
        pa.x = get<0>(p1);
        pa.y = get<1>(p1);
        vec2d pb;
        pb.x = get<0>(p2);
        pb.y = get<1>(p2);
        vec2d pc;
        pc.x = get<0>(p);
        pc.y = get<1>(p);
        return ::boost::geometry::detail::precise_math::orient2d
            <PromotedType, Robustness>(pa, pb, pc, eps_policy);
    }

    template
    <
        typename PromotedType,
        typename P1,
        typename P2,
        typename P,
        typename EpsPolicyInternal,
        std::enable_if_t<!std::is_fundamental<PromotedType>::value, int> = 0
    >
    static inline auto side_value(P1 const& p1, P2 const& p2, P const& p,
                                  EpsPolicyInternal&)
    {
        return side_non_robust<>::apply(p1, p2, p);
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template
    <
        typename P1,
        typename P2,
        typename P
    >
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        using coordinate_type = typename select_calculation_type_alt
            <
                CalculationType,
                P1,
                P2,
                P
            >::type;

        using promoted_type = typename select_most_precise
            <
                coordinate_type,
                double
            >::type;

        epsilon_policy<promoted_type> epsp;
        promoted_type sv = side_value<promoted_type>(p1, p2, p, epsp);
        promoted_type const zero = promoted_type();

        return epsp.apply(sv, zero) ? 0
            : sv > zero ? 1
            : -1;
    }

#endif

};

}} // namespace strategy::side

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_ROBUST_HPP

/* side_robust.hpp
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
*/