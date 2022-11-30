//  (C) Copyright John Maddock 2005-2021.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_HYPOT_HPP
#define BOOST_MATH_CCMATH_HYPOT_HPP

#include <cmath>
#include <array>
#include <limits>
#include <type_traits>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/sqrt.hpp>
#include <boost/math/ccmath/abs.hpp>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>
#include <boost/math/ccmath/detail/swap.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T hypot_impl(T x, T y) noexcept
{
    x = boost::math::ccmath::abs(x);
    y = boost::math::ccmath::abs(y);

    if (y > x)
    {
        boost::math::ccmath::detail::swap(x, y);
    }

    if(x * std::numeric_limits<T>::epsilon() >= y)
    {
        return x;
    }

    T rat = y / x;
    return x * boost::math::ccmath::sqrt(1 + rat * rat);
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real hypot(Real x, Real y) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::abs(x) == Real(0) ? boost::math::ccmath::abs(y) :
               boost::math::ccmath::abs(y) == Real(0) ? boost::math::ccmath::abs(x) :
               boost::math::ccmath::isinf(x) ? std::numeric_limits<Real>::infinity() :
               boost::math::ccmath::isinf(y) ? std::numeric_limits<Real>::infinity() :
               boost::math::ccmath::isnan(x) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::detail::hypot_impl(x, y);
    }
    else
    {
        using std::hypot;
        return hypot(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto hypot(T1 x, T2 y) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(x))
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

        return boost::math::ccmath::hypot(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::hypot;
        return hypot(x, y);
    }
}

inline constexpr float hypotf(float x, float y) noexcept
{
    return boost::math::ccmath::hypot(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double hypotl(long double x, long double y) noexcept
{
    return boost::math::ccmath::hypot(x, y);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_HYPOT_HPP

/* hypot.hpp
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
*/