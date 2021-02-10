// Boost.Geometry

// Copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP
#define BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

#include <boost/geometry/core/radius.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Spheroid>
inline ResultType unit_spheroid_b(Spheroid const& spheroid)
{
    return ResultType(get_radius<2>(spheroid))
         / ResultType(get_radius<0>(spheroid));
}

template <typename ResultSpheroid, typename Spheroid>
inline ResultSpheroid unit_spheroid(Spheroid const& spheroid)
{
    typedef typename radius_type<ResultSpheroid>::type radius_t;
    return ResultSpheroid(radius_t(1),
                          unit_spheroid_b<radius_t>(spheroid));
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_UNIT_SPHEROID_HPP

/* unit_spheroid.hpp
8y8jBARGW8uez2kvXfoBuv7gbYgxwnGTk409252J8W5EM9Y0ehiF2EmiTjsadyoumzsVQpL8FvRAwInh3oT8PNRL2OSAKrsk3850a7yGS5RaC2e0aopT6WaJAGs7Bq01tL3LADTodIa8km4A7M3jo2dGjrtrRhB3sbMQkXfN3fRu79nz9P6nF0/T+2e7e0J0tnbYwTcWvao9Nut3g4H16hXsf803gq9+8+SoeX40fNfuniGreyDYMOvu/sYl9YvM7ZHTmEzdK2/mzxtfokacXC8a2wjenZiPYL2gNR3hLDmWcCqQzsC4mX3F0UEETWlUHYO8dSTZ2NadLhEwgTOd2B4wANw9YD+6mgSozJosUTmDkwFuMZfzk+8OfIIdAQIMTAVPH5uiOR+DWy6cYGlzSM/XiFvgmKA7ZKarQE/lVsy5lIvBNuSc/gh9Ily99P9+/FH0evSN1T8LkzuoD+p1V5HDcTmI5FSEGChP2wLQtpKid/3+Wa9Gi6peIe0CMA+hCxbEBDOLNphbtYFPztgSvS5cp44dgSPS4LrGovVPulY//EnMYoJJEql5CFEKM40Dg31lP79AdQ/wrf30kdETXv8HaU5XP43U1krM5ECKGdYPo4Gf8kPALQhtdPRZ7wZ25Iyd2DNeGPL5ND9G
*/