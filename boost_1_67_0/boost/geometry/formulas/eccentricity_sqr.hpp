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
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
*/