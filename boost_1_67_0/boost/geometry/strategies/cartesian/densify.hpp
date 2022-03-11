// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

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
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        typedef model::point<calc_t, geometry::dimension<Point>::value, cs::cartesian> calc_point_t;
        
        calc_point_t cp0, cp1;
        geometry::detail::conversion::convert_point_to_point(p0, cp0);
        geometry::detail::conversion::convert_point_to_point(p1, cp1);

        // dir01 = xy1 - xy0
        calc_point_t dir01 = cp1;
        geometry::subtract_point(dir01, cp0);
        calc_t const dot01 = geometry::dot_product(dir01, dir01);
        calc_t const len = math::sqrt(dot01);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(len / length_threshold);
        if (n <= 0)
        {
            return;
        }

        // NOTE: Normalization will not work for integral coordinates
        // normalize
        //geometry::divide_value(dir01, len);

        calc_t step = len / (n + 1);

        calc_t d = step;
        for (signed_size_type i = 0 ; i < n ; ++i, d += step)
        {
            // pd = xy0 + d * dir01
            calc_point_t pd = dir01;

            // without normalization
            geometry::multiply_value(pd, calc_t(i + 1));
            geometry::divide_value(pd, calc_t(n + 1));
            // with normalization
            //geometry::multiply_value(pd, d);
            
            geometry::add_point(pd, cp0);

            // NOTE: Only needed if types calc_point_t and out_point_t are different
            // otherwise pd could simply be passed into policy
            out_point_t p;
            assert_dimension_equal<calc_point_t, out_point_t>();
            geometry::detail::conversion::convert_point_to_point(pd, p);
            
            policy.apply(p);
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