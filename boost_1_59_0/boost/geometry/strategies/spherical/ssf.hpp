// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016-2021.
// Modifications copyright (c) 2016-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_SSF_HPP


#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#include <boost/geometry/strategy/spherical/envelope.hpp>

#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/spherical/disjoint_segment_box.hpp>
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