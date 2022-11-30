//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FDIM_HPP
#define BOOST_MATH_CCMATH_FDIM_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/isnan.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T fdim_impl(const T x, const T y) noexcept
{
    if (x <= y)
    {
        return 0;
    }
    else if ((y < 0) && (x > (std::numeric_limits<T>::max)() + y))
    {
        return std::numeric_limits<T>::infinity();
    }
    else
    {
        return x - y;
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real fdim(Real x, Real y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::isnan(x) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::detail::fdim_impl(x, y);
    }
    else
    {
        using std::fdim;
        return fdim(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto fdim(T1 x, T2 y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        // If the type is an integer (e.g. epsilon == 0) then set the epsilon value to 1 so that type is at a minimum 
        // cast to double
        constexpr auto T1p = std::numeric_limits<T1>::epsilon() > 0 ? std::numeric_limits<T1>::epsilon() : 1;
        constexpr auto T2p = std::numeric_limits<T2>::epsilon() > 0 ? std::numeric_limits<T2>::epsilon() : 1;
        
        using promoted_type = 
                              #ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
                              std::conditional_t<T1p <= LDBL_EPSILON && T1p <= T2p, T1,
                              std::conditional_t<T2p <= LDBL_EPSILON && T2p <= T1p, T2,
                              #endif
                              std::conditional_t<T1p <= DBL_EPSILON && T1p <= T2p, T1,
                              std::conditional_t<T2p <= DBL_EPSILON && T2p <= T1p, T2, double
                              #ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
                              >>>>;
                              #else
                              >>;
                              #endif

        return boost::math::ccmath::fdim(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::fdim;
        return fdim(x, y);
    }
}

inline constexpr float fdimf(float x, float y) noexcept
{
    return boost::math::ccmath::fdim(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double fdiml(long double x, long double y) noexcept
{
    return boost::math::ccmath::fdim(x, y);
}
#endif

} // Namespace boost::math::ccmath

#endif // BOOST_MATH_CCMATH_FDIM_HPP

/* fdim.hpp
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
*/