//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FMIN_HPP
#define BOOST_MATH_CCMATH_FMIN_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/isnan.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T fmin_impl(const T x, const T y) noexcept
{
    if (x < y)
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
inline constexpr Real fmin(Real x, Real y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::isnan(x) && boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(x) ? y :
               boost::math::ccmath::isnan(y) ? x :
               boost::math::ccmath::detail::fmin_impl(x, y);
    }
    else
    {
        using std::fmin;
        return fmin(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto fmin(T1 x, T2 y) noexcept
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

        return boost::math::ccmath::fmin(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::fmin;
        return fmin(x, y);
    }
}

inline constexpr float fminf(float x, float y) noexcept
{
    return boost::math::ccmath::fmin(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double fminl(long double x, long double y) noexcept
{
    return boost::math::ccmath::fmin(x, y);
}
#endif

} // Namespace boost::math::ccmath

#endif // BOOST_MATH_CCMATH_FMIN_HPP

/* fmin.hpp
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
*/