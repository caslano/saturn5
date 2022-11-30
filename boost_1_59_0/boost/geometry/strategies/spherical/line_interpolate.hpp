// Boost.Geometry

// Copyright (c) 2018-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/formulas/interpolate_point_spherical.hpp>
#include <boost/geometry/srs/spheroid.hpp>
#include <boost/geometry/strategies/line_interpolate.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{


/*!
\brief Interpolate point on a spherical segment.
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
    typename DistanceStrategy = distance::haversine<double, CalculationType>
>
class spherical
{
public:

    typedef typename DistanceStrategy::radius_type radius_type;

    spherical() = default;

    explicit inline spherical(typename DistanceStrategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline spherical(DistanceStrategy const& s)
        : m_strategy(s)
    {}

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

        formula::interpolate_point_spherical<calc_t> formula;

        calc_t angle01;
        formula.compute_angle(p0, p1, angle01);
        formula.compute_axis(p0, angle01);

        calc_t a = angle01 * fraction;
        formula.compute_point(a, p);
    }

    inline radius_type radius() const
    {
        return m_strategy.radius();
    }

private :
    DistanceStrategy m_strategy;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::line_interpolate::spherical<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::line_interpolate


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
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
*/