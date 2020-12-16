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
cP+6pnJ0/5pVObp/Ta4c3b9GVs43BnLl6P51dOXfPmZ1zXN+2pFyVrhescZs6kGwjb+kVymknOMdf2X3NTQ60/CUO9QfR7ycl1fPLecB1RPr0Sqn/FrlTjs8Z9oX+yWmNcuZ9kxiWovWOdOuzp2W+Gy73GmJbVQhMe2wI3O20SFVo9vkhSp5ytj79OqR/sGS9/uTpw+Y6pHze8aY3LN0uL7/rXofTgiTi5k3OM285WsUsj1CZy65G2TH6327A3K3R1bNRLkk6v2DudMSZf+3xLTmR+ZM65877YicaUflTktsj001Cu4zL9QouM9cWSO6T0yrEd0nJtaI7hODa+z8eTzn+vXbUN5txJ7iSDEpdl9XK3uZ8funxLPhHX8WXeDZ/W/ca0/dL4wLKaqKg8UJjn/T43nQb3C/ft0HH3t8766d+8ZGsd2ZZ9Rz4+XgqB3qHi8zTd4yJ+TLR1bIx4GioqghesrH6mT50IXRztzjdq8c8hFN0zE9jCEmqoh6ord5s5KkGe86edfSDOue089LyuR89WBz9YLrnlVVPagdyUevHr1ja77jefiqavL1Tt+/4Hp/Z94hBdKLr/XOlPVXVXd8vTftX3C9ZyiLxYl8DDy82ZGDe3bs0TnWVet285DTB+IH8bHKfWXmm7l89zeZNQrW97621fqCabpqSo91TbtT679fhbD+ee7P7syu87EljZg4fnh0W/ycJD/p/lH+wCT5mZgxalfzkrMtliX2v+i2GFgz9JUtyomKop9y6R3Nh82gDo4du9085F32xpoF1/FEy06PLDtR3Ntdds769StfsKw37xsp68hziiEHFMzHSfKxPF8+FPMu5SFext4XUsabDii4350vI1mR9Hd+n5uyA/tczhjsm2vFl3BZOMfP4vfy26xOdh6c4lvo+Sx1uEe/sccnQ3Ua7+Y81l/0qHE7+izjxnrbf5bRLHLvPzRp37Nd/btPvCw9d4ivW7vIs4vwvCyyvqEMos8WIv0zptSOZ7hkeLZQJDxbSD+oQBmERwuKYvSI0cNd+uxKH3B5jj+2dWjLLqEaXMCLY/c+B+ekndPj3NjR7tky0+JP33c6zXBtGDkH5++rK/a+Xp4y3zvSF+QZ4Vlczjl7eL7+HM8sUsf7xon5U8elZ57tCn186ki/NRiRNjhjeMak7H7DRlnobOsd277rDgnXfa4Dz5DxxQNifYBkzxorp8T8q8L8lepH58/KO3/oa2x+WOYlyjH2/oN87xvUz3kf7ad8WZ14AX4kaoj3xK3+st78YVukpOWpA/43bEf2gcKe3f3NH5X7ZDu5afE+2JbGp8UqeP7+4LLzvrhBaIdaIXqtPqpuPMFXQh1+IdThrPj8HkfmZDzyyC7xIGDH6rF7xkaF339E+99OH5cRnjFG+7E3Pd85eGy93P5RD+THnGXbdGgc8h7phtEtTMqo1F0p971Dua+Jl3GizDPz9M0X7Q8x9KWXsx3i36mNyv7xTu56hWPS8MQxqXViWoZpuX1oXmqdpOurEJPzP2c9KIxjGspgSyiD5U0LKYPU4UphR8qgZIUrmiW22R9WJgeEdQ/7+ni9ZvvNQHpm3ufKrZOUTYd8ZVM9Mn5EWE7vNF2gRsunwyGx/5unpP4N2Iqx8qndvJDyGalm70L/2wcdUXj/297rfztaVquLFiyrtUWjZVU9lOml8eX4fZiimjjG+TP8XoJhzI+UUH759iV9MuaZ3jXfPpa3jo6onHN+HDw8c3Lo0zbfvlcx0v+231fk6a89XKukOuHEjnCm532mkDLS4WL86JTca+u22fNbGYMNuEyKnFfXhYuVziVsMzbhHNtsfatCtlm6S550z3Ri3XSGbVe62G8=
*/