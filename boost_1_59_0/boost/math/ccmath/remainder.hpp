//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_REMAINDER_HPP
#define BOOST_MATH_CCMATH_REMAINDER_HPP

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/abs.hpp>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>
#include <boost/math/ccmath/isfinite.hpp>
#include <boost/math/ccmath/modf.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T remainder_impl(const T x, const T y) noexcept
{
    T n = 0;
    const T fractional_part = boost::math::ccmath::modf((x / y), &n);

    if(fractional_part > T(1.0/2))
    {
        ++n;
    }
    else if(fractional_part < T(-1.0/2))
    {
        --n;
    }

    return x - n*y;
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real remainder(Real x, Real y) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::isinf(x) && !boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::abs(y) == Real(0) && !boost::math::ccmath::isnan(x) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(x) || boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::detail::remainder_impl<Real>(x, y);
    }
    else
    {
        using std::remainder;
        return remainder(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto remainder(T1 x, T2 y) noexcept
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

        return boost::math::ccmath::remainder(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::remainder;
        return remainder(x, y);
    }
}

inline constexpr float remainderf(float x, float y) noexcept
{
    return boost::math::ccmath::remainder(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double remainderl(long double x, long double y) noexcept
{
    return boost::math::ccmath::remainder(x, y);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_REMAINDER_HPP

/* remainder.hpp
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
*/