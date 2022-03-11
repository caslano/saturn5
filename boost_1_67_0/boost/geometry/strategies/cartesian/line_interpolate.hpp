// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
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

    // point-point strategy getters
    struct distance_pp_strategy
    {
        typedef DistanceStrategy type;
    };

    inline typename distance_pp_strategy::type get_distance_pp_strategy() const
    {
        typedef typename distance_pp_strategy::type distance_type;
        return distance_type();
    }

    template <typename Point, typename Fraction, typename Distance>
    inline void apply(Point const& p0,
                      Point const& p1,
                      Fraction const& fraction,
                      Point & p,
                      Distance const&) const
    {
        typedef typename select_calculation_type_alt
            <
                CalculationType,
                Point
            >::type calc_t;

        typedef model::point
            <
                calc_t,
                geometry::dimension<Point>::value,
                cs::cartesian
            > calc_point_t;

        calc_point_t cp0, cp1;
        geometry::detail::conversion::convert_point_to_point(p0, cp0);
        geometry::detail::conversion::convert_point_to_point(p1, cp1);

        //segment convex combination: p0*fraction + p1*(1-fraction)
        Fraction const one_minus_fraction = 1-fraction;
        for_each_coordinate(cp1, detail::value_operation
                                 <
                                    Fraction,
                                    std::multiplies
                                 >(fraction));
        for_each_coordinate(cp0, detail::value_operation
                                 <
                                    Fraction,
                                    std::multiplies
                                 >(one_minus_fraction));
        for_each_coordinate(cp1, detail::point_operation
                                 <
                                    calc_point_t,
                                    std::plus
                                 >(cp0));

        assert_dimension_equal<calc_point_t, Point>();
        geometry::detail::conversion::convert_point_to_point(cp1, p);
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