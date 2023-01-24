// Boost.Geometry

// Copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP
#define BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct flattening
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (a - b) / a
        return ResultType(get_radius<0>(geometry) - get_radius<2>(geometry))
                    / ResultType(get_radius<0>(geometry));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType flattening(Geometry const& geometry)
{
    return formula_dispatch::flattening<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

/* flattening.hpp
0t6oRNXS0oaL8bnLy1WlH10UX8OpZOFM01T44Ibkoawa/CMWZhOHx6LIIBXiohKHAFCUPo/P3JVYtTidOD4VhSt6IVY3XJ0+BcD0ReFiibcrsWhHHkAMhBMUqcMsmGqGV1UXgDrD8VkSKCNhIBylK6EMonClOH0AQNHAK2mG00fRR48hReH+2sFDUHakSjHhpv4erYcYzv+QNFNRcGGATvy8dh5FweL0r6D4SLTHEKUouJBKaPr7e/h7KFFKFZy/KojtUZCEaqWhv7mu01nblcnjla1TytYpZeuUktYpJm8UsEZRqNcfJmRPa5gkFLjegP/Bn6skJtECDG9KD3/0myhMhFgFk7uvgrOsCaSkwOUDTu0mRJmrAD+O92n0ferY/Izh3EFwbrR/FT5K57EbAWxpEIBzBk53fCr1p5MkzC2EhZuhmH7VioR4sPiqUdwj15aHM+dvlksHc9MrbJZVMm8hyvehiJ+ZKXgEYoJ7QX/YA8I+0OyNIIuOFmRpwYLMI1eQFRZmyExIBuwFM2SCkCFLU2TIKlYFys0wMsvNMCksLK08HtQHad/aRk1tbJsRmybWpOGX9Ui9z2uRz8yrEvPKFXWoxIQlOsT/lPeGvLh3lby4fpFky8+Q15dOEEXSQaL4PYq8O7md5MRvIDmxa0huTAjJi1nyz+O/z6N5KHzznBRmZ5KXt1PJzlXBpPD+ZVJwK4kUpCWSj/Jj
*/