// Boost.Geometry

// Copyright (c) 2016, 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP
#define BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct eccentricity_sqr
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct eccentricity_sqr<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // 1 - (b / a)^2
        return ResultType(1) - math::sqr(ResultType(get_radius<2>(geometry))
                                       / ResultType(get_radius<0>(geometry)));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType eccentricity_sqr(Geometry const& geometry)
{
    return formula_dispatch::eccentricity_sqr<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_ECCENCRICITY_SQR_HPP

/* eccentricity_sqr.hpp
mImBjpQihXR4f71nRwy+XRvnaqMP1ujawJNxF+N4+uOBlnWU7Z8OSTFqrmKaWVvxhyN7ZzD4KubxlpvFWpyVJvKcjASeF5HANmR/QlSuHXjNOkd4IodOtgMGdNcVy5hC3K8/J7dL4oJanBBsbH7I/OSoLmjHHiSd42gHz6a01teWcn/txLWrswmPsJKvJC3FIq4Zcb6OEcU9+SmHVQr+pfTZWLhOx0BSSTZ2zEj39Bv/B0jMrD4mxru9clowjF4XrCBPQwrwMLc6yzQnA+UcM7FQwm/pi85ShoFXygDIOB14UjX0qErW2GWxQxeoUxfEo4GVUdKVbtVCVGIhKHHVcP5hwufKbkJz1nr2lUp6h51z+PDosC1w4jVzW/0vP6Jt64fEV3mBrFi6qyLhrWCbGA1fI7REFDwlgR7HLI4eidhOQplW5gPv+PIV/J/EjynuEh15GHR5HkTuNH0lg3uN6qBE6koviM8H7vr71DiMRdio7RBTAD81zJTb5VOldDetIRSeRTzDEQZVfFhxZSu9Sp6M1CC8DAd0srHy8nJHeAb3/xvpfdS8UxF4xoFA7NihoabrQkQ0waqwszLeBU/QMHegf4vVQQXVyq3Y2+4c/X7YPm4YC6kGbHHnu+qgB3YD32utLcDXI9dkuvuT
*/