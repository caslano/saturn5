// Boost.Geometry

// Copyright (c) 2017-2019, Oracle and/or its affiliates.

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

private:
    typename strategy_detail::get_radius
        <
            RadiusTypeOrSphere
        >::type m_radius;
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
F9f/1Kcsbu0VISVqJbDqvbR2cestE++jBFxKtHHnIb+n+S49MWJ0Y9OycCttbtoMj3MpJ7tHBxm8FHCtt0+RRJrenuepTr+WWcvuN2x0srAodri6n3RYPMPNpppR/VEP57DacjK+/VMnMlwKedAO9GK3hRZixD1d3NscYPX7bs0dNzwFd2FrLaRm38mYr32JBjsjM7D2xeVt1qNLdgSgUeK+eZDk9D2q3jh7fyLASgBlTDigry6j/tf6Tvxnw8Ji+T7z2nmoV3ugN5rUznqmzY032sEPJ2AJ8/ZJMgEa2VoRALl5YcnUTTIbYZRXoaqT1vk8M9I+Ffc6PgfI60gFGIXtYZFETMbnARzfSgn5LG8RYT3pcGR9OVV9+zt+6IeFSkU7L+H5vRxEYuQsGtbS5TZ2Ly2UOkZ/ksXfaRin75B3j02Rxd8mnMtn7R9avTm3ue21ltsWqyx7MuT3JEQRqp7IRhwbHiIizdpOszhHdhLZ9Bo9SxgE7xMtq29es3i1CdgSvm91dN5aWdw8xJJZXXvPGHFGsbiyijzsJfO8qboM5NK5RfN6CLV6dfbrzEsf7gaa0Lrw4DvHHh7nmBzSMqY1c2psHQy54Al9aq/wFuuWSbXcMHsNwjZfdvS/b4sjutj6mCYO9jhVHMY5+BHQV0AWvgkCiMIyNZqACudLmh6elt5Tn1Gc2xYDzY9TC00XMgQzGtaYPJqL1zLI
*/