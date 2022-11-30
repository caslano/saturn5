//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FMOD_HPP
#define BOOST_MATH_CCMATH_FMOD_HPP

#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/abs.hpp>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>
#include <boost/math/ccmath/isfinite.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename ReturnType, typename T1, typename T2>
inline constexpr ReturnType fmod_impl(T1 x, T2 y) noexcept
{
    if(x == y)
    {
        return ReturnType(0);
    }
    else
    {
        while(x >= y)
        {
            x -= y;
        }

        return static_cast<ReturnType>(x);
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real fmod(Real x, Real y) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        return boost::math::ccmath::abs(x) == Real(0) && y != Real(0) ? x :
               boost::math::ccmath::isinf(x) && !boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::abs(y) == Real(0) && !boost::math::ccmath::isnan(x) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isinf(y) && boost::math::ccmath::isfinite(x) ? x :
               boost::math::ccmath::isnan(x) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               boost::math::ccmath::detail::fmod_impl<Real>(x, y);
    }
    else
    {
        using std::fmod;
        return fmod(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto fmod(T1 x, T2 y) noexcept
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

        return boost::math::ccmath::fmod(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::fmod;
        return fmod(x, y);
    }
}

inline constexpr float fmodf(float x, float y) noexcept
{
    return boost::math::ccmath::fmod(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double fmodl(long double x, long double y) noexcept
{
    return boost::math::ccmath::fmod(x, y);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_FMOD_HPP

/* fmod.hpp
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
*/