//  Copyright (c) 2013 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This is a partial header, do not include on it's own!!!
//
// Linear combination for bessel derivatives are defined here
#ifndef BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP
#define BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math{ namespace detail{

template <class T, class Tag, class Policy>
inline T bessel_j_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_j_imp<T>(v-1, x, tag, pol) - boost::math::detail::cyl_bessel_j_imp<T>(v+1, x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T bessel_j_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_j_imp<T>(itrunc(v-1), x, tag, pol) - boost::math::detail::cyl_bessel_j_imp<T>(itrunc(v+1), x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T sph_bessel_j_derivative_linear(unsigned v, T x, Policy pol)
{
   return (v / x) * boost::math::detail::sph_bessel_j_imp<T>(v, x, pol) - boost::math::detail::sph_bessel_j_imp<T>(v+1, x, pol);
}

template <class T, class Policy>
inline T bessel_i_derivative_linear(T v, T x, Policy pol)
{
   T result = boost::math::detail::cyl_bessel_i_imp<T>(v - 1, x, pol);
   if(result >= tools::max_value<T>())
      return result;  // result is infinite
   T result2 = boost::math::detail::cyl_bessel_i_imp<T>(v + 1, x, pol);
   if(result2 >= tools::max_value<T>() - result)
      return result2;  // result is infinite
   return (result + result2) / 2;
}

template <class T, class Tag, class Policy>
inline T bessel_k_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   T result = boost::math::detail::cyl_bessel_k_imp<T>(v - 1, x, tag, pol);
   if(result >= tools::max_value<T>())
      return -result;  // result is infinite
   T result2 = boost::math::detail::cyl_bessel_k_imp<T>(v + 1, x, tag, pol);
   if(result2 >= tools::max_value<T>() - result)
      return -result2;  // result is infinite
   return (result + result2) / -2;
}

template <class T, class Policy>
inline T bessel_k_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_bessel_k_imp<T>(itrunc(v-1), x, tag, pol) + boost::math::detail::cyl_bessel_k_imp<T>(itrunc(v+1), x, tag, pol)) / -2;
}

template <class T, class Tag, class Policy>
inline T bessel_y_derivative_linear(T v, T x, Tag tag, Policy pol)
{
   return (boost::math::detail::cyl_neumann_imp<T>(v-1, x, tag, pol) - boost::math::detail::cyl_neumann_imp<T>(v+1, x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T bessel_y_derivative_linear(T v, T x, const bessel_int_tag& tag, Policy pol)
{
   return (boost::math::detail::cyl_neumann_imp<T>(itrunc(v-1), x, tag, pol) - boost::math::detail::cyl_neumann_imp<T>(itrunc(v+1), x, tag, pol)) / 2;
}

template <class T, class Policy>
inline T sph_neumann_derivative_linear(unsigned v, T x, Policy pol)
{
   return (v / x) * boost::math::detail::sph_neumann_imp<T>(v, x, pol) - boost::math::detail::sph_neumann_imp<T>(v+1, x, pol);
}

}}} // namespaces

#endif // BOOST_MATH_SF_DETAIL_BESSEL_DERIVATIVES_LINEAR_HPP

/* bessel_derivatives_linear.hpp
+ymJPuLOKNTv6BPie6NQfpYuz/g+963tIZdvDbH9ZsrH6ncwP7/a5nvQzi+xdvFaCMmTmWBMMq677lP7FPypPYTFPusnPkzb99CryT7wfe1J6jvf1R5RqLGj5nlp/rU+Id/m+vO0+V5ryO4ehaSlPVTP9e7IIXAYRRreg7ymNRStWZT9Hne8LBKbbPK9seJaeTSBwdft99ndehs8o1X28dwNx79prHmw3e8hwml/8WyP1+yktlB1TQz7wC/Z9d3sX6mOfcUavttdPsvzmh5se6A9NOgd6b9C9/CSvjvZ4XNjYXvID7R/2Bi+ep/On2+xPxH7Tnf8CbrZt6voezDRJR1h46UdofizjhCpnwzWh/0Zgu/bFw/V/7fbQ8278ME72vU/a++QrftO+X+VtZ0Ufw1Un/7xoCjk/86maXBNp2Elx9ChVNbWZR0hlucbE9Qdyl5jcKRuYXAUdtV/fiKM3sGl2VGo4EbtrJ7savc9Urb9Snvd+QyW3vsKVXOQ6lv06slHZ/UKO97cEXLtrcFvcfgNN9zo1xZyQ+wl8AecTcMEFo3RGXvh8N+WELJXRfaETFnL9T6VtfX67s731X65T8jxdaKN4ht0fEi9mdpcpI7fcg8l61ziPmfumx1O3mwLyU9hWpXvZuFBkz4XGA/MmwpHsO9+5SX8zr9JybtQI9pCaZLrurzXdTD9n2HHe3Q9UuyM4/tlxogh/LoOTyY5toS/L4B3LcKR1lAbq61r9NNoC/HjeFKyv1vsPajj9CPu8x+HUPgeO8Vd/LY4s+eRfS9D/g16FeWLV9ipbg7/S3zV2AA/feT8DnzyDn38Rn49j3P/DCH8Ga/6Gd/pmT0IBuKlhtONHnDyTKPU4Cv8qWy18XUxYi+Exkf2qnW8kW72fXscfceztNP0Owc+14vhG1vN9VJiHZ9W06Gkr8187P24PnwY/wof9seDKfK739wu0yPbZb+Hc427/s8OEl/2TkpG0enytL0v8fM948vObX5XBI4j9Ona3CFtYWftFUr0W0VXa2qVB8XwJvfsBdf6/l4JXqVuxrRO9pwjPk7Tp/0Xi+IybEe3FB6e5fMHONcKP+9lVV/uJj/4nZlTtNHkOXfSJ5TEa3Vui+fx7Ps821uIvSCy9kItzUzZG4KOd4uXYfYLkqeS9fLdoWxQJzmXL8+Ts4L773txaXt4wzq7Gg774a4YL1/lHbev4gmJ7mLD9vJLN9dcLIcc5ti+7tf/1Sc0foknjldmG8O+pf659H4DLr+Fx2t46/tmya+1KQ+HLufqYvccORWWydukSf/iLH+cnOB8nlQruPGpvJeH+2NtIepOzzNx93y2qdu4FD8ryg7XbTQGiJtYnGWvlb/Xh1CFc/4Dud1cvyyW67Pky5/Aagi+yEnJZv75hziHSWG8PR38bn10Ih77nP2n4y18KBdV1SmRMqlsVpLgO525KBNyzpeegItzWcfj2/nyIP+/LWbfjkI1pW06JKu2rtXwFYxz6uXeEs/nsvULYsnn+kt8NVbMz2LTXX6PI6LrCz3MC1vEBWy68L2zFS64OEjffJfgSnSrfIpTJTo3rsF1PCuOb3PvLb68y16Tp4oX8Jmcm6wRZz1gP0I8PMBeHKqcz2fyVlyTj9nQ2EwXErE/7ICH/q/Cry6n1O6LxKDz+s6zO6gTFsu5v4k8Y2/1rAt3p9lX80f0eIOftVc6GPfkmPD5jhDW4PrWuo6H4TixBn9G8O3Bzj8hHk7Aywdw5zTn7VUS3ywPeU9v+Rz59U456EU8Ubf02NY5G+wu7hPKaxzj08YSudPaXe5lfPiALhkxJ3dVtjj2oTb5t3RRiz36vF5xXUeo3gOnL8L8QPnoH7g=
*/