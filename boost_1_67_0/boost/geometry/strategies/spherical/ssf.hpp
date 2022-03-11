// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016, 2018, 2019.
// Modifications copyright (c) 2016-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
#include <boost/geometry/strategies/spherical/envelope.hpp>
//#include <boost/geometry/strategies/concepts/side_concept.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace side
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename T>
int spherical_side_formula(T const& lambda1, T const& delta1,
                           T const& lambda2, T const& delta2,
                           T const& lambda, T const& delta)
{
    // Create temporary points (vectors) on unit a sphere
    T const cos_delta1 = cos(delta1);
    T const c1x = cos_delta1 * cos(lambda1);
    T const c1y = cos_delta1 * sin(lambda1);
    T const c1z = sin(delta1);

    T const cos_delta2 = cos(delta2);
    T const c2x = cos_delta2 * cos(lambda2);
    T const c2y = cos_delta2 * sin(lambda2);
    T const c2z = sin(delta2);

    // (Third point is converted directly)
    T const cos_delta = cos(delta);

    // Apply the "Spherical Side Formula" as presented on my blog
    T const dist
        = (c1y * c2z - c1z * c2y) * cos_delta * cos(lambda)
        + (c1z * c2x - c1x * c2z) * cos_delta * sin(lambda)
        + (c1x * c2y - c1y * c2x) * sin(delta);

    T zero = T();
    return math::equals(dist, zero) ? 0
        : dist > zero ? 1
        : -1; // dist < zero
}

}
#endif // DOXYGEN_NO_DETAIL

/*!
\brief Check at which side of a Great Circle segment a point lies
         left of segment (> 0), right of segment (< 0), on segment (0)
\ingroup strategies
\tparam CalculationType \tparam_calculation
 */
template <typename CalculationType = void>
class spherical_side_formula
{

public :
    typedef spherical_tag cs_tag;

    typedef strategy::envelope::spherical<CalculationType> envelope_strategy_type;

    static inline envelope_strategy_type get_envelope_strategy()
    {
        return envelope_strategy_type();
    }

    typedef strategy::disjoint::segment_box_spherical disjoint_strategy_type;

    static inline disjoint_strategy_type get_disjoint_strategy()
    {
        return disjoint_strategy_type();
    }

    typedef strategy::within::spherical_point_point equals_point_point_strategy_type;
    static inline equals_point_point_strategy_type get_equals_point_point_strategy()
    {
        return equals_point_point_strategy_type();
    }

    template <typename P1, typename P2, typename P>
    static inline int apply(P1 const& p1, P2 const& p2, P const& p)
    {
        typedef typename promote_floating_point
            <
                typename select_calculation_type_alt
                    <
                        CalculationType,
                        P1, P2, P
                    >::type
            >::type calculation_type;

        calculation_type const lambda1 = get_as_radian<0>(p1);
        calculation_type const delta1 = get_as_radian<1>(p1);
        calculation_type const lambda2 = get_as_radian<0>(p2);
        calculation_type const delta2 = get_as_radian<1>(p2);
        calculation_type const lambda = get_as_radian<0>(p);
        calculation_type const delta = get_as_radian<1>(p);

        return detail::spherical_side_formula(lambda1, delta1,
                                              lambda2, delta2,
                                              lambda, delta);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

/*template <typename CalculationType>
struct default_strategy<spherical_polar_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};*/

template <typename CalculationType>
struct default_strategy<spherical_equatorial_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};

template <typename CalculationType>
struct default_strategy<geographic_tag, CalculationType>
{
    typedef spherical_side_formula<CalculationType> type;
};

}
#endif

}} // namespace strategy::side

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP

/* ssf.hpp
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
*/