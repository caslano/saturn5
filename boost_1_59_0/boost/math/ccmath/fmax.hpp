//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FMAX_HPP
#define BOOST_MATH_CCMATH_FMAX_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/isnan.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T fmax_impl(const T x, const T y) noexcept
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real fmax(Real x, Real y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::isnan(x) && boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(x) ? y :
               boost::math::ccmath::isnan(y) ? x :
               boost::math::ccmath::detail::fmax_impl(x, y);
    }
    else
    {
        using std::fmax;
        return fmax(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto fmax(T1 x, T2 y) noexcept
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

        return boost::math::ccmath::fmax(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::fmax;
        return fmax(x, y);
    }
}

inline constexpr float fmaxf(float x, float y) noexcept
{
    return boost::math::ccmath::fmax(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double fmaxl(long double x, long double y) noexcept
{
    return boost::math::ccmath::fmax(x, y);
}
#endif

} // Namespace boost::math::ccmath

#endif // BOOST_MATH_CCMATH_FMAX_HPP

/* fmax.hpp
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
*/