// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP
#define BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

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
struct mean_radius
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        return ResultType(get_radius<0>(geometry));
    }
};

template <typename ResultType, typename Geometry>
struct mean_radius<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (2*a + b) / 3
        return (ResultType(2) * ResultType(get_radius<0>(geometry))
                + ResultType(get_radius<2>(geometry)))
             / ResultType(3);
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
inline ResultType mean_radius(Geometry const& geometry)
{
    return formula_dispatch::mean_radius<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_MEAN_RADIUS_HPP

/* mean_radius.hpp
T4eoZxJ92Z7+5PgVM6zhip0PucgUcbFhmXqXcr7zqHhReGp0aFfimbH2VCmkBiTpS7DKphyfFHJgJuj9XJ9h2IDy6DvU1Ac5Fhu3t75r+7xItwZgbQ3ZF73w+gx9Ow7NIP67ixv1qYA+c8DqOLCTXDd4qVpJ+NhAe7h8wwT1EENG1Q3D9TQriqtpZeT3BHPvhz1nJGuv+KwQESSDt0qjVeSbWiXI3Y5wVydPtqsi3N1h6RcvntcRdMDFlign8Vsz0xZ3cIKAvpq02r98SrShq2DiMOtk+IqA0WHR2199Cx18ZDHBP0lV+UbYxKtdPnEvl5+TywpOX25/UxlnBxYtd8GCmAms0gfCX797QspV3oQYE4II8bVfd4PHeZenkcpizC8MT1Y9DLO1OF1e93LRKQeA2I97i9604VeR7IYKkFpKIeMVioY9DdrdKeTT9TZizXmaa0OK1cthkcnr9HS/XiMu4YJ97Mu7T7pMrUbpFoyoCWWDwOsOR+79jFoC1T2b3iC3X128oGeAiMHhQ2UqvGEp+H86DcqbuaTma1tP3y6PipNkuP4t4qkwMw==
*/