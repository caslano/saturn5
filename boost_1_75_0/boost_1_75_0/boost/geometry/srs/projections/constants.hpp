// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_PROJECTIONS_CONSTANTS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CONSTANTS_HPP


#include <boost/geometry/util/math.hpp>
#include <boost/math/constants/constants.hpp>


namespace boost { namespace geometry { namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename T>
inline T fourth_pi() { return T(0.78539816339744830961566084581988); }
template <typename T>
inline T third_pi() { return boost::math::constants::third_pi<T>(); }
template <typename T>
inline T half_pi() { return boost::math::constants::half_pi<T>(); }
template <typename T>
inline T pi() { return boost::math::constants::pi<T>(); }
template <typename T>
inline T one_and_half_pi() { return T(4.7123889803846898576939650749193); }
template <typename T>
inline T two_pi() { return boost::math::constants::two_pi<T>(); }
template <typename T>
inline T two_and_half_pi() { return T(7.8539816339744830961566084581988); }

template <typename T>
inline T two_div_pi() { return boost::math::constants::two_div_pi<T>(); }
template <typename T>
inline T half_pi_sqr() { return T(2.4674011002723396547086227499689); }
template <typename T>
inline T pi_sqr() { return boost::math::constants::pi_sqr<T>(); }

template <typename T>
inline T sixth() { return boost::math::constants::sixth<T>(); }
template <typename T>
inline T third() { return boost::math::constants::third<T>(); }
template <typename T>
inline T two_thirds() { return boost::math::constants::two_thirds<T>(); }


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections
#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PROJECTS_HPP

/* constants.hpp
plwIZvMH0VvaUXnOjZlbTFZt+3+bAhGP1GYvm2ain9XuJpGwSFCheYx+Kq/pV+43BmtBO6nT+YnshsX71Xg3K73cacUY96/c/IJBjomEgk0TPESb83MEdXRmxzbtxMiSOTU3hGRoCBt/ZDl8xWI14zLWVurtiqkTv1NUB43yhqHfUm97oGUDdBUYA3h4ivIJqbnEs6ZmFgQF7g4i3Msj47/6tN+Y+FbnubBvxDbeuzVrVfYyRtzX4jx6lTqXjrl9ISRvxI90mY2n2Wfj9vuAqS3Jo+31CtJcruBfeiRjkyot7oId6K1kuBu/aAzADDTKHHKUyYDYTPuHGth+9Z+LJ+Dic2tprKG0ZhwzYLayt6zdvliuI+tb993qcajqorFzvshZ3kkkaoZK+KeoKDGvhXdo2Kw+zi4j+g1MS7o9Zl4cFRIF9G2KdkqFFmP+LuwgMoJOOPWt/i5FDpufMLmyEFEQr/GYf0u8uPp1naiN9LJZPd+hW3zvkiITxiNe7jTpGjlSKZRaq5E7eI9MvYcjhJ18UHyiDHPL8rOJ/7nCYL6ov+NN61Np052l29yPX52UnEcjTaNqDOt4VY1mvvJ0ZZA09XwPDdEaufDZWHqPrnhJjaFLwo5AxF22wVKv+XOxoTumLXzkf6yoI4uSKuUpNZJb707HXCW7FLpnwBdDZrdPz6q3k8ZQtwi17Dws06CFMrljU3lGGGbCjBS4
*/