// Boost.Geometry

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of cartesian segment.
\ingroup strategies
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
}
 */
template
<
    typename CalculationType = void
>
class cartesian
{
public:
    template <typename Point, typename AssignPolicy, typename T>
    static inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold)
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename coordinate_type<out_point_t>::type out_coord_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type, out_coord_t,
                CalculationType
            >::type calc_t;

        typedef model::point<calc_t, geometry::dimension<Point>::value, cs::cartesian> calc_point_t;
        
        assert_dimension_equal<calc_point_t, out_point_t>();

        calc_point_t cp0, dir01;
        // dir01 = p1 - p0
        geometry::detail::for_each_dimension<calc_point_t>([&](auto index)
        {
            calc_t const coord0 = boost::numeric_cast<calc_t>(get<index>(p0));
            calc_t const coord1 = boost::numeric_cast<calc_t>(get<index>(p1));
            set<index>(cp0, coord0);
            set<index>(dir01, coord1 - coord0);
        });

        calc_t const dot01 = geometry::dot_product(dir01, dir01);
        calc_t const len = math::sqrt(dot01);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type const n = signed_size_type(len / length_threshold);
        if (n <= 0)
        {
            return;
        }

        calc_t const den = calc_t(n + 1);
        for (signed_size_type i = 0 ; i < n ; ++i)
        {
            out_point_t out;
            
            calc_t const num = calc_t(i + 1);
            geometry::detail::for_each_dimension<out_point_t>([&](auto index)
            {
                // out = p0 + d * dir01
                calc_t const coord = get<index>(cp0) + get<index>(dir01) * num / den;

                set<index>(out, boost::numeric_cast<out_coord_t>(coord));
            });

            policy.apply(out);
        }
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef strategy::densify::cartesian<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DENSIFY_HPP

/* densify.hpp
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
*/