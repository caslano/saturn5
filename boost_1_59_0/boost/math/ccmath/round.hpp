//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_ROUND_HPP
#define BOOST_MATH_CCMATH_ROUND_HPP

#include <cmath>
#include <type_traits>
#include <stdexcept>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/abs.hpp>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>
#include <boost/math/ccmath/modf.hpp>

namespace boost::math::ccmath {

namespace detail {

// Computes the nearest integer value to arg (in floating-point format), 
// rounding halfway cases away from zero, regardless of the current rounding mode.
template <typename T>
inline constexpr T round_impl(T arg) noexcept
{
    T iptr = 0;
    const T x = boost::math::ccmath::modf(arg, &iptr);
    constexpr T half = T(1)/2;

    if(x >= half && iptr > 0)
    {
        return iptr + 1;
    }
    else if(boost::math::ccmath::abs(x) >= half && iptr < 0)
    {
        return iptr - 1;
    }
    else
    {
        return iptr;
    }
}

template <typename ReturnType, typename T>
inline constexpr ReturnType int_round_impl(T arg)
{
    const T rounded_arg = round_impl(arg);

    if(rounded_arg > static_cast<T>((std::numeric_limits<ReturnType>::max)()))
    {
        if constexpr (std::is_same_v<ReturnType, long long>)
        {
            throw std::domain_error("Rounded value cannot be represented by a long long type without overflow");
        }
        else
        {
            throw std::domain_error("Rounded value cannot be represented by a long type without overflow");
        }
    }
    else
    {
        return static_cast<ReturnType>(rounded_arg);
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real round(Real arg) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(arg))
    {
        return boost::math::ccmath::abs(arg) == Real(0) ? arg :
               boost::math::ccmath::isinf(arg) ? arg :
               boost::math::ccmath::isnan(arg) ? arg :
               boost::math::ccmath::detail::round_impl(arg);
    }
    else
    {
        using std::round;
        return round(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double round(Z arg) noexcept
{
    return boost::math::ccmath::round(static_cast<double>(arg));
}

inline constexpr float roundf(float arg) noexcept
{
    return boost::math::ccmath::round(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double roundl(long double arg) noexcept
{
    return boost::math::ccmath::round(arg);
}
#endif

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr long lround(Real arg)
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(arg))
    {
        return boost::math::ccmath::abs(arg) == Real(0) ? 0l :
               boost::math::ccmath::isinf(arg) ? 0l :
               boost::math::ccmath::isnan(arg) ? 0l :
               boost::math::ccmath::detail::int_round_impl<long>(arg);
    }
    else
    {
        using std::lround;
        return lround(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr long lround(Z arg)
{
    return boost::math::ccmath::lround(static_cast<double>(arg));
}

inline constexpr long lroundf(float arg)
{
    return boost::math::ccmath::lround(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long lroundl(long double arg)
{
    return boost::math::ccmath::lround(arg);
}
#endif

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr long long llround(Real arg)
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(arg))
    {
        return boost::math::ccmath::abs(arg) == Real(0) ? 0ll :
               boost::math::ccmath::isinf(arg) ? 0ll :
               boost::math::ccmath::isnan(arg) ? 0ll :
               boost::math::ccmath::detail::int_round_impl<long long>(arg);
    }
    else
    {
        using std::llround;
        return llround(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr long llround(Z arg)
{
    return boost::math::ccmath::llround(static_cast<double>(arg));
}

inline constexpr long long llroundf(float arg)
{
    return boost::math::ccmath::llround(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long long llroundl(long double arg)
{
    return boost::math::ccmath::llround(arg);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_ROUND_HPP

/* round.hpp
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
*/