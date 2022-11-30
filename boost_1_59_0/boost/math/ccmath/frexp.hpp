//  (C) Copyright Christopher Kormanyos 1999 - 2021.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FREXP_HPP
#define BOOST_MATH_CCMATH_FREXP_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>
#include <boost/math/ccmath/isfinite.hpp>

namespace boost::math::ccmath {

namespace detail
{

template <typename Real>
inline constexpr Real frexp_zero_impl(Real arg, int* exp)
{
    *exp = 0;
    return arg;
}

template <typename Real>
inline constexpr Real frexp_impl(Real arg, int* exp)
{
    const bool negative_arg = (arg < Real(0));
    
    Real f = negative_arg ? -arg : arg;
    int e2 = 0;
    constexpr Real two_pow_32 = Real(4294967296);

    while (f >= two_pow_32)
    {
        f = f / two_pow_32;
        e2 += 32;
    }

    while(f >= Real(1))
    {
        f = f / Real(2);
        ++e2;
    }
    
    if(exp != nullptr)
    {
        *exp = e2;
    }

    return !negative_arg ? f : -f;
}

} // namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real frexp(Real arg, int* exp)
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(arg))
    {
        return arg == Real(0)  ? detail::frexp_zero_impl(arg, exp) : 
               arg == Real(-0) ? detail::frexp_zero_impl(arg, exp) :
               boost::math::ccmath::isinf(arg) ? detail::frexp_zero_impl(arg, exp) : 
               boost::math::ccmath::isnan(arg) ? detail::frexp_zero_impl(arg, exp) :
               boost::math::ccmath::detail::frexp_impl(arg, exp);
    }
    else
    {
        using std::frexp;
        return frexp(arg, exp);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double frexp(Z arg, int* exp)
{
    return boost::math::ccmath::frexp(static_cast<double>(arg), exp);
}

inline constexpr float frexpf(float arg, int* exp)
{
    return boost::math::ccmath::frexp(arg, exp);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double frexpl(long double arg, int* exp)
{
    return boost::math::ccmath::frexp(arg, exp);
}
#endif

}

#endif // BOOST_MATH_CCMATH_FREXP_HPP

/* frexp.hpp
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
*/