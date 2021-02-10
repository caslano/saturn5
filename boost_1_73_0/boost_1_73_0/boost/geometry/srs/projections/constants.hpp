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
D5BrIMzv7UxscJQtOjO9jW+0xftsif1Axd/Gc/KWyFjRdAZ6IUxwR/diAqzddpYyA5ZFcw4QzrMiG2fJ1uWgf9UPzk9+6V58Ct5fXV02xQtQ+JYyuR/uh3CBgtsxHNGabdp4UaJ5sMQ9bFmzhRGOtETrnIXqVugxNSGRjd9gYmqxjBj2Tz+AC/7u5Ow5JOw+1c5gyRwaSemmhw3vHSCPes+2uO/psHPROcVYA8OlpOjeY+BKZTNZQZuv70owqai7a2U1WpQtMHwFQi8E95xdNLQMAU4SaSYG+q7RfrUMcCReAWNpRSWLNnezrOD31COCSUtjNOrGa7pOK/vxkKHFHkKtE/Svr4L+efBL55f+4FN1UifiAKC1L6204xZaG5x13l3//O66e3FW3QVIXyQXaM1Uc6ihizEv8HsRkNT5ZDjsDK4osGB1kBvVB+zTcqaqjwE261CttPDC0WREQ7ttewtrVLdj9uOhwBsDt4sEa1mlhNPdKrQf5xyfVUsI9yc8BgbwRqmic/eobou+8fMU4b501oxnOGia+uDrPgNTcGIDrf5g4if0PUiwlo4yAJSeEiV6hkSmv8k8qKowNPkMAdUzlN72SzKwVumjArVjLdRWGzrMvK2n4cf6OR60ne14Ta1STykaQxFubs3y
*/