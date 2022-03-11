// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_BY_TRIANGLE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_BY_TRIANGLE_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/strategies/cartesian/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/cartesian/envelope.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/strategies/side.hpp>

#include <boost/geometry/algorithms/detail/equals/point_point.hpp>


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

    typedef strategy::envelope::cartesian<CalculationType> envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return envelope_strategy_type();
    }

    typedef strategy::disjoint::segment_box disjoint_strategy_type;

    static inline disjoint_strategy_type get_disjoint_strategy()
    {
        return disjoint_strategy_type();
    }

    typedef strategy::within::cartesian_point_point equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

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

        typedef typename boost::mpl::if_c
            <
                boost::is_void<CalculationType>::type::value,
                typename select_most_precise
                    <
                        typename select_most_precise
                            <
                                coordinate_type1, coordinate_type2
                            >::type,
                        coordinate_type3
                    >::type,
                CalculationType
            >::type coordinate_type;

        // Promote float->double, small int->int
        typedef typename select_most_precise
            <
                coordinate_type,
                double
            >::type promoted_type;

        bool const are_all_integral_coordinates =
            boost::is_integral<coordinate_type1>::value
            && boost::is_integral<coordinate_type2>::value
            && boost::is_integral<coordinate_type3>::value;

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
        typedef equals_point_point_strategy_type strategy_t;
        return geometry::detail::equals::equals_point_point(p1, p2, strategy_t());
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


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_SIDE_BY_TRIANGLE_HPP

/* side_by_triangle.hpp
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
*/