// Boost.Geometry

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DENSIFY_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DENSIFY_HPP


#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/cross_product.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <boost/geometry/arithmetic/normalize.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/formulas/spherical.hpp>
#include <boost/geometry/formulas/interpolate_point_spherical.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/srs/sphere.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/strategies/spherical/get_radius.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace densify
{


/*!
\brief Densification of spherical segment.
\ingroup strategies
\tparam RadiusTypeOrSphere \tparam_radius_or_sphere
\tparam CalculationType \tparam_calculation

\qbk{
[heading See also]
[link geometry.reference.algorithms.densify.densify_4_with_strategy densify (with strategy)]
}
 */
template
<
    typename RadiusTypeOrSphere = double,
    typename CalculationType = void
>
class spherical
{
public:
    typedef typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type radius_type;

    // For consistency with area strategy the radius is set to 1
    inline spherical()
        : m_radius(1.0)
    {}

    template <typename RadiusOrSphere>
    explicit inline spherical(RadiusOrSphere const& radius_or_sphere)
        : m_radius(strategy_detail::get_radius
                    <
                        RadiusOrSphere
                    >::apply(radius_or_sphere))
    {}

    template <typename Point, typename AssignPolicy, typename T>
    inline void apply(Point const& p0, Point const& p1, AssignPolicy & policy, T const& length_threshold) const
    {
        typedef typename AssignPolicy::point_type out_point_t;
        typedef typename select_most_precise
            <
                typename coordinate_type<Point>::type,
                typename coordinate_type<out_point_t>::type,
                CalculationType
            >::type calc_t;

        calc_t angle01;

        formula::interpolate_point_spherical<calc_t> formula;
        formula.compute_angle(p0, p1, angle01);

        BOOST_GEOMETRY_ASSERT(length_threshold > T(0));

        signed_size_type n = signed_size_type(angle01 * m_radius / length_threshold);
        if (n <= 0)
            return;

        formula.compute_axis(p0, angle01);

        calc_t step = angle01 / (n + 1);

        calc_t a = step;
        for (signed_size_type i = 0 ; i < n ; ++i, a += step)
        {
            out_point_t p;
            formula.compute_point(a, p);

            geometry::detail::conversion::point_to_point
                <
                    Point, out_point_t,
                    2, dimension<out_point_t>::value
                >::apply(p0, p);

            policy.apply(p);
        }
    }

    inline radius_type radius() const
    {
        return m_radius;
    }

private:
    radius_type m_radius;
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <>
struct default_strategy<spherical_equatorial_tag>
{
    typedef strategy::densify::spherical<> type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::densify


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP

/* densify.hpp
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
*/