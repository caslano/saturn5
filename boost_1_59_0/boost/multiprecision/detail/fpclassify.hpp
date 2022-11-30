///////////////////////////////////////////////////////////////////////////////
//  Copyright 2022 Matt Borland. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_DETAIL_FPCLASSIFY_HPP
#define BOOST_MP_DETAIL_FPCLASSIFY_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/float128_functions.hpp>

#ifdef BOOST_MP_MATH_AVAILABLE
#include <boost/math/special_functions/fpclassify.hpp>

#define BOOST_MP_ISNAN(x) (boost::math::isnan)(x)
#define BOOST_MP_ISINF(x) (boost::math::isinf)(x)
#define BOOST_MP_FPCLASSIFY(x) (boost::math::fpclassify)(x)
#define BOOST_MP_ISFINITE(x) (!(boost::math::isnan)(x) && !(boost::math::isinf)(x))

#else

namespace boost { namespace multiprecision { namespace detail {

template <typename T, typename std::enable_if<std::is_floating_point<T>::value
                      #ifdef BOOST_HAS_FLOAT128
                      || std::is_same<T, float128_type>::value
                      #endif
                      , bool>::type = true>
inline bool isnan BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    BOOST_MP_FLOAT128_USING;
    using std::isnan;
    return static_cast<bool>((isnan)(x));
}

template <typename T, typename std::enable_if<!std::is_floating_point<T>::value
                      #ifdef BOOST_HAS_FLOAT128
                      && !std::is_same<T, float128_type>::value
                      #endif
                      , bool>::type = true>
inline bool isnan BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    return x != x;
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value
                      #ifdef BOOST_HAS_FLOAT128
                      || std::is_same<T, float128_type>::value
                      #endif
                      , bool>::type = true>
inline bool isinf BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    BOOST_MP_FLOAT128_USING;
    using std::isinf;
    return static_cast<bool>((isinf)(x));
}

template <typename T, typename std::enable_if<!std::is_floating_point<T>::value
                      #ifdef BOOST_HAS_FLOAT128
                      && !std::is_same<T, float128_type>::value
                      #endif
                      , bool>::type = true>
inline bool isinf BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    return x == std::numeric_limits<T>::infinity() || x == -std::numeric_limits<T>::infinity();
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
inline int fpclassify BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    using std::fpclassify;
    return fpclassify(x);
}

template <typename T, typename std::enable_if<!std::is_floating_point<T>::value, bool>::type = true>
inline int fpclassify BOOST_PREVENT_MACRO_SUBSTITUTION (const T x)
{
    BOOST_MP_FLOAT128_USING;
    using std::isnan;
    using std::isinf;
    using std::abs;

    return (isnan)(x) ? FP_NAN :
           (isinf)(x) ? FP_INFINITE :
           abs(x) == T(0) ? FP_ZERO :
           abs(x) > 0 && abs(x) < (std::numeric_limits<T>::min)() ? FP_SUBNORMAL : FP_NORMAL;
}

}}} // Namespace boost::multiprecision::detail

#define BOOST_MP_ISNAN(x) (boost::multiprecision::detail::isnan)(x)
#define BOOST_MP_ISINF(x) (boost::multiprecision::detail::isinf)(x)
#define BOOST_MP_FPCLASSIFY(x) (boost::multiprecision::detail::fpclassify)(x)
#define BOOST_MP_ISFINITE(x) (!(boost::multiprecision::detail::isnan)(x) && !(boost::multiprecision::detail::isinf)(x))

#endif

#endif // BOOST_MP_DETAIL_FPCLASSIFY_HPP

/* fpclassify.hpp
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
*/