// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP
#define BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

template<class CT>
struct bounds
{
  static CT lowest  () { return boost::numeric::bounds<CT>::lowest(); }
  static CT highest () { return boost::numeric::bounds<CT>::highest(); }
};

template <typename Box>
bool is_inverse_spheroidal_coordinates(Box const& box)
{
    typedef typename point_type<Box>::type point_type;
    typedef typename coordinate_type<point_type>::type bound_type;

    bound_type high = bounds<bound_type>::highest();
    bound_type low = bounds<bound_type>::lowest();

    return (geometry::get<0, 0>(box) == high) &&
           (geometry::get<0, 1>(box) == high) &&
           (geometry::get<1, 0>(box) == low) &&
           (geometry::get<1, 1>(box) == low);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_IS_INVERSE_SPHEROIDAL_COORDINATES_HPP

/* is_inverse_spheroidal_coordinates.hpp
/A/ACzZA5Eq6jxFgSniiDralfFNOkwiE4+SaauQveNPRc4mMg/V6CRX6p0zM5hdIXgAWueNnhFBsubB8SQp9Pyi+2sy7C1dKgyldaSTe1bKCr7og4OYqaNZT3Yg2304C7+ElSftcMk/llLkRIB9dYoN5sgOz1vlVKMw+R7kgUrvyQRRnAu9ALHruHgvkUmoPlaSU3CWue3EliOYvRNFmRbXw5kj+awCfBus0V/fiB4C48iYeiB25/M+FcJcpZOisHxKvzNaK9qQKMfmwOAt9tPW/hs+QQ6GSUHu63yb4ZrKHmjpxZoDhV9P3wrAznh4Dw5EaYc30ZOii0D/804YCF3nKhDAdy7+Z8iIAJXdpaAL17LiO+P3jb4FMom4H7BjXC8kfBj6FDghZMxn2fcLChUWPUitQcYJ/Rk61M/2xLHJJskpgK6aHPyw8EXjseB71E1Vf+/4pKAhLbJ+lej6DA2L3hPQJ6QY6EqpTvM1mIaWtaXlZInwRSS3MD+X7+LFre40Fe0yZqoJgMW1GIHS87/xonmZzowY6y+5Jck+euxIBNtCiqFYfagYuww==
*/