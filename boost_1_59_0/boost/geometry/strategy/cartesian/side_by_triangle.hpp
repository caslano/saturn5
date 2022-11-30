// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_BY_TRIANGLE_HPP
#define BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_BY_TRIANGLE_HPP


#include <type_traits>

#include <boost/geometry/core/config.hpp>
#include <boost/geometry/arithmetic/determinant.hpp>

#include <boost/geometry/core/access.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

/*!
\brief Check at which side of a segment a point lies:
    left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam CalculationType \tparam_calculation
 */
template <typename CalculationType = void>
class side_by_triangle
{
    template <typename Policy>
    struct eps_policy
    {
        eps_policy() {}
        template <typename Type>
        eps_policy(Type const& a, Type const& b, Type const& c, Type const& d)
            : policy(a, b, c, d)
        {}
        Policy policy;
    };

    struct eps_empty
    {
        eps_empty() {}
        template <typename Type>
        eps_empty(Type const&, Type const&, Type const&, Type const&) {}
    };

public :
    typedef cartesian_tag cs_tag;

    // Template member function, because it is not always trivial
    // or convenient to explicitly mention the typenames in the
    // strategy-struct itself.

    // Types can be all three different. Therefore it is
    // not implemented (anymore) as "segment"

    template
    <
        typename CoordinateType,
        typename PromotedType,
        typename P1,
        typename P2,
        typename P,
        typename EpsPolicy
    >
    static inline
    PromotedType side_value(P1 const& p1, P2 const& p2, P const& p, EpsPolicy & eps_policy)
    {
        CoordinateType const x = get<0>(p);
        CoordinateType const y = get<1>(p);

        CoordinateType const sx1 = get<0>(p1);
        CoordinateType const sy1 = get<1>(p1);
        CoordinateType const sx2 = get<0>(p2);
        CoordinateType const sy2 = get<1>(p2);

        PromotedType const dx = sx2 - sx1;
        PromotedType const dy = sy2 - sy1;
        PromotedType const dpx = x - sx1;
        PromotedType const dpy = y - sy1;

        eps_policy = EpsPolicy(dx, dy, dpx, dpy);

        return geometry::detail::determinant<PromotedType>
                (
                    dx, dy,
                    dpx, dpy
                );

    }

    template
    <
        typename CoordinateType,
        typename PromotedType,
        typename P1,
        typename P2,
        typename P
    >
    static inline
    PromotedType side_value(P1 const& p1, P2 const& p2, P const& p)
    {
        eps_empty dummy;
        return side_value<CoordinateType, PromotedType>(p1, p2, p, dummy);
    }


    template
    <
        typename CoordinateType,
        typename PromotedType,
        bool AreAllIntegralCoordinates
    >
    struct compute_side_value
    {
        template <typename P1, typename P2, typename P, typename EpsPolicy>
        static inline PromotedType apply(P1 const& p1, P2 const& p2, P const& p, EpsPolicy & epsp)
        {
            return side_value<CoordinateType, PromotedType>(p1, p2, p, epsp);
        }
    };

    template <typename CoordinateType, typename PromotedType>
    struct compute_side_value<CoordinateType, PromotedType, false>
    {
        template <typename P1, typename P2, typename P, typename EpsPolicy>
        static inline PromotedType apply(P1 const& p1, P2 const& p2, P const& p, EpsPolicy & epsp)
        {
            // For robustness purposes, first check if any two points are
            // the same; in this case simply return that the points are
            // collinear
            if (equals_point_point(p1, p2)
                || equals_point_point(p1, p)
                || equals_point_point(p2, p))
            {
                return PromotedType(0);
            }

            // The side_by_triangle strategy computes the signed area of
            // the point triplet (p1, p2, p); as such it is (in theory)
            // invariant under cyclic permutations of its three arguments.
            //
            // In the context of numerical errors that arise in
            // floating-point computations, and in order to make the strategy
            // consistent with respect to cyclic permutations of its three
            // arguments, we cyclically permute them so that the first
            // argument is always the lexicographically smallest point.

            typedef compare::cartesian<compare::less> less;

            if (less::apply(p, p1))
            {
                if (less::apply(p, p2))
                {
                    // p is the lexicographically smallest
                    return side_value<CoordinateType, PromotedType>(p, p1, p2, epsp);
                }
                else
                {
                    // p2 is the lexicographically smallest
                    return side_value<CoordinateType, PromotedType>(p2, p, p1, epsp);
                }
            }

            if (less::apply(p1, p2))
            {
                // p1 is the lexicographically smallest
                return side_value<CoordinateType, PromotedType>(p1, p2, p, epsp);
            }
            else
            {
                // p2 is the lexicographically smallest
                return side_value<CoordinateType, PromotedType>(p2, p, p1, epsp);
            }
        }
    };


    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename coordinate_type<P1>::type coordinate_type1;
        typedef typename coordinate_type<P2>::type coordinate_type2;
        typedef typename coordinate_type<P>::type coordinate_type3;

        typedef std::conditional_t
            <
                std::is_void<CalculationType>::value,
                typename select_most_precise
                    <
                        coordinate_type1,
                        coordinate_type2,
                        coordinate_type3
                    >::type,
                CalculationType
            > coordinate_type;

        // Promote float->double, small int->int
        typedef typename select_most_precise
            <
                coordinate_type,
                double
            >::type promoted_type;

        bool const are_all_integral_coordinates =
            std::is_integral<coordinate_type1>::value
            && std::is_integral<coordinate_type2>::value
            && std::is_integral<coordinate_type3>::value;

        eps_policy< math::detail::equals_factor_policy<promoted_type> > epsp;
        promoted_type s = compute_side_value
            <
                coordinate_type, promoted_type, are_all_integral_coordinates
            >::apply(p1, p2, p, epsp);

        promoted_type const zero = promoted_type();
        return math::detail::equals_by_policy(s, zero, epsp.policy) ? 0
            : s > zero ? 1
            : -1;
    }

private:
    template <typename P1, typename P2>
    static inline bool equals_point_point(P1 const& p1, P2 const& p2)
    {
        return strategy::within::cartesian_point_point::apply(p1, p2);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<cartesian_tag, CalculationType>
{
    typedef side_by_triangle<CalculationType> type;
};

}

#endif

}} // namespace strategy::side

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_CARTESIAN_SIDE_BY_TRIANGLE_HPP

/* side_by_triangle.hpp
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
*/