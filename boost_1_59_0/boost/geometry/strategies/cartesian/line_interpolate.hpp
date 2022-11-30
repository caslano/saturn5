// Boost.Geometry

// Copyright (c) 2018-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a cartesian segment.
\ingroup strategies
\tparam CalculationType \tparam_calculation
\tparam DistanceStrategy The underlying point-point distance strategy

\qbk{
[heading See also]
\* [link geometry.reference.algorithms.line_interpolate.line_interpolate_4_with_strategy line_interpolate (with strategy)]
}

*/
template
<
    typename CalculationType = void,
    typename DistanceStrategy = distance::pythagoras<CalculationType>
>
class cartesian
{
public:
    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction,
                      Point & p,
                      Distance const&) const
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType, Point
            >::type calc_t;
        typedef typename coordinate_type<Point>::type coord_t;

        //segment convex combination: p0*fraction + p1*(1-fraction)
        Fraction const one_minus_fraction = 1-fraction;
        geometry::detail::for_each_dimension<Point>([&](auto dimension)
        {
            // NOTE: numeric_cast is a leftover from convert, it could probably be ommited.
            // NOTE: the order of points is different than in the formula above
            //       this is also a leftover from the previous implementation
            calc_t coord0 = boost::numeric_cast<calc_t>(get<dimension>(p0));
            calc_t coord1 = boost::numeric_cast<calc_t>(get<dimension>(p1));
            calc_t result = calc_t(coord1 * fraction) + calc_t(coord0 * one_minus_fraction);
            set<dimension>(p, boost::numeric_cast<coord_t>(result));
        });
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef strategy::line_interpolate::cartesian<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
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
*/