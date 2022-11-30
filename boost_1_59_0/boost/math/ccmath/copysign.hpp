//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_COPYSIGN_HPP
#define BOOST_MATH_CCMATH_COPYSIGN_HPP

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/abs.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T copysign_impl(const T mag, const T sgn) noexcept
{
    if(sgn >= 0)
    {
        return boost::math::ccmath::abs(mag);
    }
    else
    {
        return -boost::math::ccmath::abs(mag);
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real copysign(Real mag, Real sgn) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(mag))
    {
        return boost::math::ccmath::detail::copysign_impl(mag, sgn);
    }
    else
    {
        using std::copysign;
        return copysign(mag, sgn);
    }
}

template <typename T1, typename T2>
inline constexpr auto copysign(T1 mag, T2 sgn) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(mag))
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

        return boost::math::ccmath::copysign(promoted_type(mag), promoted_type(sgn));
    }
    else
    {
        using std::copysign;
        return copysign(mag, sgn);
    }
}

inline constexpr float copysignf(float mag, float sgn) noexcept
{
    return boost::math::ccmath::copysign(mag, sgn);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double copysignl(long double mag, long double sgn) noexcept
{
    return boost::math::ccmath::copysign(mag, sgn);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_COPYSIGN_HPP

/* copysign.hpp
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
*/