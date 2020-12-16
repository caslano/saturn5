/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_floating_point.hpp
 *
 * This header defines \c is_floating_point type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __float128 a floating point type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_FLOAT128)
#include <type_traits>
#else
#include <boost/type_traits/is_floating_point.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_FLOAT128)
using std::is_floating_point;
#else
using boost::is_floating_point;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_FLOATING_POINT_HPP_INCLUDED_

/* is_floating_point.hpp
1t5r4CXTt9IYzi0vKC0zvatd/46RvpUQ07dG0hxl+povxf9+yLdvNfEzzbpmjfjvDlVa2/UYPeQ6jjEDsJpUzj53ztwC7XMj+Rxm2tPn4v80FNT3bpfw90LS95r0P7VcfaJp/89IGS6xDrbOMv3Z5JftY4Ws4nE/SM+QKnEj5X3L6sOszEP2t5a0n1sl8eMsV79sxpXvpQxVUuYquTLFs51riKdIvlM4D36jl43MlfSW89jppsl3ImcWFNtl1z75CIk3M9TLOiIkx0g7TY4NDyVafUOuftKc706Jc1TQ+fz6S7OGHBJZD1V/yFou/raW3fe0bUabbcG6Oe0mvuLSxB6JGc2S4sPN4pLCrSJ9T253XECfmaJ93RQpz+GhMGeRY0auUmTqHbLb9gnk18rRtsvr2ra060nStl3t2rTl2Gzw7n/ZtFPxc53r2rba2x0j7VbaihzL9Wm3eabdSt2WY4XedmvWvhe0NPtFyZxZDu6rLvTRr9StBcrq3NR8btpmTmMcNWN2yJpv7ivmSvxTrC78r+1Y80gxey6cbvdx3Ru0S7TXcYwdIuep299cy7wiqTbiW7gU5U32fZynzEX5kb1hD5J+ppT6VWLKR3wzzo3Cv038f+A83CGpTcR47Z/KImuMJl07K1X7p63if5a7gXjrXpyjTudPn8P9h+5hkQb/JnEfsw5Hotu1HVfKty3KuGvNN/Uy74+yrxb+dFMvs+VYf2k1znujFO1LjpfwIq5CK0e+02vtrXTNPkvizLBO5D7aHtcqWtJfJvLdXOp0UvM0yz0+dtA4ndB5lR0nLicpvjkjPXE8463GzYrEbVlR4Y6jdUHqQM/utm1lw+0jUv8Pkvov19DU//HaJspcNh0jdF21HydvA/vCpfaeWH/01JHS0nL6hOB7fU1ziGXGH72nlvpgwjtYHXT8+U78nUKD+P8V3G6pS6YPms7Di7nXXbTec69rxovTJGwC48URpg/8Vo6l+/VpZp+UmRLntzw9JDKXf6Cp/5bW/w5aF76tLXfItlRZh/sO56g306g4+AdJO2wmebYO2fdeK7m+vVpF7vs6JIXxu+tNJF62iVexkHs0b/3SeAta6b1c3NykFs25U/WrXxp3RSTugRXXmziu/DbY5+1OnLSKNc0SktJZD/LrhySN2k6L/wyOnykutnqZ5XM/Ncz0y1JPTDz0yjHRa73+bEeyvgeqtumzcJdSV0v+VFdXZ2BaMlUvtX3t13cR22c9UjfeXidpRmndjeTR1bduDzfh6ea5Zqn48yy/e61sE/9I3+fRVPy3Sfip4i8y8Q/zr6/aBu6QOAOoqXFWBs71zBPNpuc0pz0GOkG/Ridm3d99fbJ8xs1hUcbItvod/O24zsrLbNuHV32vz1Sepnz1x/XQNN3M3kdDxP8i1527Nu0nbuxdawsRuU8ZbtIVcXeZptcuZH0ux9KII3sr8uPWq3BaKeO9uReeL3Gutco13UiTLuw7hlwsYVdYxcR3Ppun6Bh5m4TPxgq3mx4LWUvlWC7Xb4iUZUeajmdaFrW9FJuwmmTqd4r2CeH8pPjRUZ4XNf7SlEh7L7F8xxO91yshzvEwyrPT4NbSrwyQejE6FDL3TO76YJf7Rmmvch2MTSeycczIVr+e2A1A193SlbdQT7L/XFdPZk8rm16oYw4567gQqSdmzNE0vY3ezxf/iaE5jnuGkI7tZh8xifMv7u7TWGtN0noSyauH9hEh63XxH+y5L0rVOlMq4UNDOfQbi1gtlrZv8ulq6tFL4k+XfDbJXEv+TJ4Wzb3GSglfz71OmuOZaHY+b4yYe/ydEife2Bx+Lf4L1e84h3meKSpm72ozfiZWi223hPPtRsk=
*/