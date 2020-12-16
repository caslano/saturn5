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
YVnMRA9cjJ64BP1xBS7FVbgeV+NGzMKncA1uw3W4G9fjXtyIr+MjmIeP4lF8DD/Ex/EkbsXTmI0X8En8Drfhr/gMXsUd6M7x93mcii9gEu5CSw4YeeZbfs8tlgMmoyI5AXAhtsRFaM1hkyHThct09jlsnmI8b3wag/AZ7IzbsRvuwMGYg1pOMN389Llf8qmvL76H9fB9bIJHsTV+gD3wQwzFAhyMH6Nl/vKcNE40mP9iqe8SrI1LsR4uw+64HPviChyIK3EsrrJbH4UdnK+PLJn/GgzCdbI+1sv62CDrYyNatos8x4weBtvlGMtVHj/Davg5Sj14Htl5PR6Vejwm9dgi9Xhc6rFV6vGE1COEKJT5Bcj87HMo5Uk93pR6vIV+eAjr42FkPtRFnhnGMJmPfQ6aPYznjXuxNu7DRvgKtsVXsSsewIF4ELXcWDLfLgbr6XlZ3p3YAV+Q5bpK5Ml0PGfIdPLMgExXk/F80A8DsRZ2wkY4CBtjIjbBNGyOi7AFbsWWuB0DcTe2wmPYGr/EtvgfbIe/YXu8jh2wDvXpiO2wE3bHzhiJXXAqdsOHsDs+jj1wB/bE97EXfoK98TT2wS+xr9a+5LlhrG6w3sIZrzyOQA8cI9MFEyEyXT0it1hO02vSDq7L9vwTa+EN++0l01czKHe8lDsBq2KEXX0zZLqeBtMNlO18L3bBIXbtt0Cma2fQfsvKdOWwLrpjcyyPrbCCtn/Lc7A4nKhU5q/lhvRk+gyZ3wVpf/WV8svI/Nx5H8ETGIgncTCewnF4GmfhF7gAv8Rl+BXmYCHuxTP4MX6NJ/A8FuI3eAW/xSplqANWw/9gPfwe78GL2AZ/wv5YhPF4CWfgFdyAv+EWvIov4B94EK/j63gDP8Cb+BGWKU97RHc8i3ehbGd5rpV9xWA73yXbq7Jspyqo5aLtwXT4uUxnn4uWfUBtl1+g+ow/BmAhtsAz2APP4mg8hzPxPM7Gb3AJfotr8QI+g//Bl/A7fAt/wKP4I36MP2m5suR5Vawr9bPPgXVKxosjTDLeMhnPPjdYlOTqisY6GIONMFbqPwX7YxwmYjw+gNMxAxMwE9l2kvtKng3Fw1KeB6YTkkY5ozouw3q4HBvhCmyHK7EvrsJhuBpj8WGciVm4BNfgJlyLz+I6fAnX4yHcgFp9QpzXZ5bUJ03qM1vqM0fqM1fqky71mSf1mS/1WSD1yZD6LJT6LJL6PCj1yURLe5RnQbG3QXu8JO3qF+yOl+22d4ZM14DIIuy3d2g523i7XRyvUMbzLWE89TlIaFnCeCEujpfRx7X67b7F/O61G69Im9+txiP6ujZeeF/Xys1ycbwCF8tVn/uC5k7Hk/PrfjK/4u1HcsRWxuMYgCek/ZiUkOkWy3T2udVOKNdd+AXeg19ic/wKO2MhjsYzGIdfYyqexXQ8h/PxPGbgN9bz5LLyXJQ8L0W56ntfGCo/TViu+tgcm2I77IbtsS92wpHYGaOxC07DrmjGbjgfu2MG9sDl2BPXY298HPvis9gPd+EAzMVQzJP1+zYOxss4BMtQ6ZFYBUehP47GBjgGm+Ak7I0ROAAjcSpGYQJOxlUYjWsxBvdhLObiFPwUp+JxjMfrOA3LsI4S8B6cgS0wFTvgLOyFaTgSZ2MEzsUYnIeJuABnYwauwoW4FhfhFszEHbgcD+AKfBdX4lFchZ/jajyDD+MVzMJKbM+1WAPXYWPcgF1xIw7AR3AUbsJIfBQT8DFchJtxNW7Bbfg47sGt+Dpm4yF8Cj/Fp/EsbpP9oVkZ7bkrtzw572ko+fH4UXOAB+AP2AJ/xA74E/bEIgzFKzgaf8UI/A2n4lWchb/jYvwD1+E13IDllO0=
*/