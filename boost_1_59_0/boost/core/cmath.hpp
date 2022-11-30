#ifndef BOOST_CORE_CMATH_HPP_INCLUDED
#define BOOST_CORE_CMATH_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// boost/core/cmath.hpp
//
// Floating point classification and sign manipulation functions
// Extracted from https://github.com/boostorg/lexical_cast/pull/37
//
// Copyright 2020, 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <cmath>

#if defined(BOOST_CORE_USE_GENERIC_CMATH) || (!defined(_MSC_VER) && !defined(FP_SUBNORMAL))

#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <limits>
#include <cstring>

namespace boost
{
namespace core
{

// fpclassify return values

int const fp_zero = 0;
int const fp_subnormal = 1;
int const fp_normal = 2;
int const fp_infinite = 3;
int const fp_nan = 4;

// Classification functions

template<class T> bool isfinite( T x )
{
    return x <= (std::numeric_limits<T>::max)() && x >= -(std::numeric_limits<T>::max)();
}

template<class T> bool isinf( T x )
{
    return x > (std::numeric_limits<T>::max)() || x < -(std::numeric_limits<T>::max)();
}

template<class T> bool isnan( T x )
{
    return !isfinite( x ) && !isinf( x );
}

template<class T> bool isnormal( T x )
{
    return isfinite( x ) && ( x >= (std::numeric_limits<T>::min)() || x <= -(std::numeric_limits<T>::min)() );
}

template<class T> int fpclassify( T x )
{
    if( x == 0 ) return fp_zero;

    if( x < 0 ) x = -x;

    if( x > (std::numeric_limits<T>::max)() ) return fp_infinite;

    if( x >= (std::numeric_limits<T>::min)() ) return fp_normal;

    if( x < (std::numeric_limits<T>::min)() ) return fp_subnormal;

    return fp_nan;
}

// Sign manipulation functions

inline bool signbit( float x )
{
    boost::int32_t y;

    BOOST_STATIC_ASSERT( sizeof( x ) == sizeof( y ) );

    std::memcpy( &y, &x, sizeof( y ) );

    return y < 0;
}

inline bool signbit( double x )
{
    boost::int64_t y;

    BOOST_STATIC_ASSERT( sizeof( x ) == sizeof( y ) );

    std::memcpy( &y, &x, sizeof( y ) );

    return y < 0;
}

inline bool signbit( long double x )
{
    return signbit( static_cast<double>( x ) );
}

template<class T> T copysign( T x, T y )
{
    return signbit( x ) == signbit( y )? x: -x;
}

} // namespace core
} // namespace boost

#else // defined(BOOST_CORE_USE_GENERIC_CMATH)

#if defined(_MSC_VER) && _MSC_VER < 1800
# include <float.h>
#endif

namespace boost
{
namespace core
{
#if defined(_MSC_VER) && _MSC_VER < 1800

template<class T> T copysign( T x, T y )
{
    return static_cast<T>( _copysign( static_cast<double>( x ), static_cast<double>( y ) ) );
}

template<class T> bool isnan( T x )
{
    return _isnan( static_cast<double>( x ) ) != 0;
}

template<class T> bool isfinite( T x )
{
    return _finite( static_cast<double>( x ) ) != 0;
}

template<class T> bool isinf( T x )
{
    return ( _fpclass( static_cast<double>( x ) ) & ( _FPCLASS_PINF | _FPCLASS_NINF ) ) != 0;
}

inline bool isnormal( float x )
{
    // no _fpclassf in 32 bit mode
    unsigned y = reinterpret_cast< unsigned const& >( x );
    unsigned exp = ( y >> 23 ) & 0xFF;
    return exp != 0 && exp != 0xFF;
}

inline bool isnormal( double x )
{
    return ( _fpclass( x ) & ( _FPCLASS_PN | _FPCLASS_NN ) ) != 0;
}

inline bool isnormal( long double x )
{
    return boost::core::isnormal( static_cast<double>( x ) );
}

template<class T> bool signbit( T x )
{
    return _copysign( 1.0, static_cast<double>( x ) ) < 0.0;
}

int const fp_zero = 0;
int const fp_subnormal = 1;
int const fp_normal = 2;
int const fp_infinite = 3;
int const fp_nan = 4;

inline int fpclassify( float x )
{
    switch( _fpclass( x ) )
    {
    case _FPCLASS_SNAN:
    case _FPCLASS_QNAN:

        return fp_nan;

    case _FPCLASS_NINF:
    case _FPCLASS_PINF:

        return fp_infinite;

    case _FPCLASS_NZ:
    case _FPCLASS_PZ:

        return fp_zero;

    default:

        return boost::core::isnormal( x )? fp_normal: fp_subnormal;
    }
}

inline int fpclassify( double x )
{
    switch( _fpclass( x ) )
    {
    case _FPCLASS_SNAN:
    case _FPCLASS_QNAN:

        return fp_nan;

    case _FPCLASS_NINF:
    case _FPCLASS_PINF:

        return fp_infinite;

    case _FPCLASS_NZ:
    case _FPCLASS_PZ:

        return fp_zero;

    case _FPCLASS_ND:
    case _FPCLASS_PD:

        return fp_subnormal;

    default:

        return fp_normal;
    }
}

inline int fpclassify( long double x )
{
    return boost::core::fpclassify( static_cast<double>( x ) );
}

#else

using std::isfinite;
using std::isnan;
using std::isinf;
using std::isnormal;
using std::fpclassify;

int const fp_zero = FP_ZERO;
int const fp_subnormal = FP_SUBNORMAL;
int const fp_normal = FP_NORMAL;
int const fp_infinite = FP_INFINITE;
int const fp_nan = FP_NAN;

using std::signbit;

// std::copysign doesn't exist in libstdc++ under -std=c++03

#if !defined(__GNUC__)

template<class T> T copysign( T x, T y )
{
    return std::copysign( x, y );
}

#else

namespace detail
{

// ::copysignl is unreliable, use the built-ins

inline float copysign_impl( float x, float y )
{
    return __builtin_copysignf( x, y );
}

inline double copysign_impl( double x, double y )
{
    return __builtin_copysign( x, y );
}

inline long double copysign_impl( long double x, long double y )
{
    return __builtin_copysignl( x, y );
}

} // namespace detail

template<class T> T copysign( T x, T y )
{
    return boost::core::detail::copysign_impl( x, y );
}

#endif // !defined(__GNUC__)
#endif // #if defined(_MSC_VER) && _MSC_VER < 1800

} // namespace core
} // namespace boost

#endif // defined(BOOST_CORE_USE_GENERIC_CMATH)

#endif  // #ifndef BOOST_CORE_CMATH_HPP_INCLUDED

/* cmath.hpp
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
*/