//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_FLOOR_HPP
#define BOOST_MATH_CCMATH_FLOOR_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/math/tools/is_constant_evaluated.hpp>
#include <boost/math/ccmath/abs.hpp>
#include <boost/math/ccmath/isinf.hpp>
#include <boost/math/ccmath/isnan.hpp>

namespace boost::math::ccmath {

namespace detail {

template <typename T>
inline constexpr T floor_pos_impl(T arg) noexcept
{
    T result = 1;

    if(result < arg)
    {
        while(result < arg)
        {
            result *= 2;
        }
        while(result > arg)
        {
            --result;
        }

        return result;
    }
    else
    {
        return T(0);
    }
}

template <typename T>
inline constexpr T floor_neg_impl(T arg) noexcept
{
    T result = -1;

    if(result > arg)
    {
        while(result > arg)
        {
            result *= 2;
        }
        while(result < arg)
        {
            ++result;
        }
        if(result != arg)
        {
            --result;
        }
    }

    return result;
}

template <typename T>
inline constexpr T floor_impl(T arg) noexcept
{
    if(arg > 0)
    {
        return floor_pos_impl(arg);
    }
    else
    {
        return floor_neg_impl(arg);
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real floor(Real arg) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(arg))
    {
        return boost::math::ccmath::abs(arg) == Real(0) ? arg :
               boost::math::ccmath::isinf(arg) ? arg :
               boost::math::ccmath::isnan(arg) ? arg :
               boost::math::ccmath::detail::floor_impl(arg);
    }
    else
    {
        using std::floor;
        return floor(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double floor(Z arg) noexcept
{
    return boost::math::ccmath::floor(static_cast<double>(arg));
}

inline constexpr float floorf(float arg) noexcept
{
    return boost::math::ccmath::floor(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double floorl(long double arg) noexcept
{
    return boost::math::ccmath::floor(arg);
}
#endif

} // Namespaces

#endif // BOOST_MATH_CCMATH_FLOOR_HPP

/* floor.hpp
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
*/