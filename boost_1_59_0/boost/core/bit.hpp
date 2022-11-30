#ifndef BOOST_CORE_BIT_HPP_INCLUDED
#define BOOST_CORE_BIT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// boost/core/bit.hpp
//
// A portable version of the C++20 standard header <bit>
//
// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <limits>
#include <cstring>

#if defined(_MSC_VER)

# include <intrin.h>
# pragma intrinsic(_BitScanForward)
# pragma intrinsic(_BitScanReverse)

# if defined(_M_X64)
#  pragma intrinsic(_BitScanForward64)
#  pragma intrinsic(_BitScanReverse64)
# endif

# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
# pragma warning(disable: 4244) // conversion from int to T

#endif // defined(_MSC_VER)

namespace boost
{
namespace core
{

// bit_cast

template<class To, class From>
To bit_cast( From const & from ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(To) == sizeof(From) );

    To to;
    std::memcpy( &to, &from, sizeof(To) );
    return to;
}

// countl

#if defined(__GNUC__) || defined(__clang__)

namespace detail
{

BOOST_CONSTEXPR inline int countl_impl( unsigned char x ) BOOST_NOEXCEPT
{
    return x? __builtin_clz( x ) - ( std::numeric_limits<unsigned int>::digits - std::numeric_limits<unsigned char>::digits ): std::numeric_limits<unsigned char>::digits;
}

BOOST_CONSTEXPR inline int countl_impl( unsigned short x ) BOOST_NOEXCEPT
{
    return x? __builtin_clz( x ) - ( std::numeric_limits<unsigned int>::digits - std::numeric_limits<unsigned short>::digits ): std::numeric_limits<unsigned short>::digits;
}

BOOST_CONSTEXPR inline int countl_impl( unsigned int x ) BOOST_NOEXCEPT
{
    return x? __builtin_clz( x ): std::numeric_limits<unsigned int>::digits;
}

BOOST_CONSTEXPR inline int countl_impl( unsigned long x ) BOOST_NOEXCEPT
{
    return x? __builtin_clzl( x ): std::numeric_limits<unsigned long>::digits;
}

BOOST_CONSTEXPR inline int countl_impl( boost::ulong_long_type x ) BOOST_NOEXCEPT
{
    return x? __builtin_clzll( x ): std::numeric_limits<boost::ulong_long_type>::digits;
}

} // namespace detail

template<class T>
BOOST_CONSTEXPR int countl_zero( T x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countl_impl( x );
}

#else // defined(__GNUC__) || defined(__clang__)

namespace detail
{

inline int countl_impl( boost::uint32_t x ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER)

    unsigned long r;

    if( _BitScanReverse( &r, x ) )
    {
        return 31 - static_cast<int>( r );
    }
    else
    {
        return 32;
    }

#else

    static unsigned char const mod37[ 37 ] = { 32, 31, 6, 30, 9, 5, 0, 29, 16, 8, 2, 4, 21, 0, 19, 28, 25, 15, 0, 7, 10, 1, 17, 3, 22, 20, 26, 0, 11, 18, 23, 27, 12, 24, 13, 14, 0 };

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return mod37[ x % 37 ];

#endif
}

inline int countl_impl( boost::uint64_t x ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && defined(_M_X64)

    unsigned long r;

    if( _BitScanReverse64( &r, x ) )
    {
        return 63 - static_cast<int>( r );
    }
    else
    {
        return 64;
    }

#else

    return static_cast<boost::uint32_t>( x >> 32 ) != 0?
        boost::core::detail::countl_impl( static_cast<boost::uint32_t>( x >> 32 ) ):
        boost::core::detail::countl_impl( static_cast<boost::uint32_t>( x ) ) + 32;

#endif
}

inline int countl_impl( boost::uint8_t x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countl_impl( static_cast<boost::uint32_t>( x ) ) - 24;
}

inline int countl_impl( boost::uint16_t x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countl_impl( static_cast<boost::uint32_t>( x ) ) - 16;
}

} // namespace detail

template<class T>
int countl_zero( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) == sizeof(boost::uint8_t) || sizeof(T) == sizeof(boost::uint16_t) || sizeof(T) == sizeof(boost::uint32_t) || sizeof(T) == sizeof(boost::uint64_t) );

    if( sizeof(T) == sizeof(boost::uint8_t) )
    {
        return boost::core::detail::countl_impl( static_cast<boost::uint8_t>( x ) );
    }
    else if( sizeof(T) == sizeof(boost::uint16_t) )
    {
        return boost::core::detail::countl_impl( static_cast<boost::uint16_t>( x ) );
    }
    else if( sizeof(T) == sizeof(boost::uint32_t) )
    {
        return boost::core::detail::countl_impl( static_cast<boost::uint32_t>( x ) );
    }
    else
    {
        return boost::core::detail::countl_impl( static_cast<boost::uint64_t>( x ) );
    }
}

#endif // defined(__GNUC__) || defined(__clang__)

template<class T>
BOOST_CONSTEXPR int countl_one( T x ) BOOST_NOEXCEPT
{
    return boost::core::countl_zero( static_cast<T>( ~x ) );
}

// countr

#if defined(__GNUC__) || defined(__clang__)

namespace detail
{

BOOST_CONSTEXPR inline int countr_impl( unsigned char x ) BOOST_NOEXCEPT
{
    return x? __builtin_ctz( x ): std::numeric_limits<unsigned char>::digits;
}

BOOST_CONSTEXPR inline int countr_impl( unsigned short x ) BOOST_NOEXCEPT
{
    return x? __builtin_ctz( x ): std::numeric_limits<unsigned short>::digits;
}

BOOST_CONSTEXPR inline int countr_impl( unsigned int x ) BOOST_NOEXCEPT
{
    return x? __builtin_ctz( x ): std::numeric_limits<unsigned int>::digits;
}

BOOST_CONSTEXPR inline int countr_impl( unsigned long x ) BOOST_NOEXCEPT
{
    return x? __builtin_ctzl( x ): std::numeric_limits<unsigned long>::digits;
}

BOOST_CONSTEXPR inline int countr_impl( boost::ulong_long_type x ) BOOST_NOEXCEPT
{
    return x? __builtin_ctzll( x ): std::numeric_limits<boost::ulong_long_type>::digits;
}

} // namespace detail

template<class T>
BOOST_CONSTEXPR int countr_zero( T x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countr_impl( x );
}

#else // defined(__GNUC__) || defined(__clang__)

namespace detail
{

inline int countr_impl( boost::uint32_t x ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER)

    unsigned long r;

    if( _BitScanForward( &r, x ) )
    {
        return static_cast<int>( r );
    }
    else
    {
        return 32;
    }

#else

    static unsigned char const mod37[ 37 ] = { 32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4, 7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5, 20, 8, 19, 18 };
    return mod37[ ( -(boost::int32_t)x & x ) % 37 ];

#endif
}

inline int countr_impl( boost::uint64_t x ) BOOST_NOEXCEPT
{
#if defined(_MSC_VER) && defined(_M_X64)

    unsigned long r;

    if( _BitScanForward64( &r, x ) )
    {
        return static_cast<int>( r );
    }
    else
    {
        return 64;
    }

#else

    return static_cast<boost::uint32_t>( x ) != 0?
        boost::core::detail::countr_impl( static_cast<boost::uint32_t>( x ) ):
        boost::core::detail::countr_impl( static_cast<boost::uint32_t>( x >> 32 ) ) + 32;

#endif
}

inline int countr_impl( boost::uint8_t x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countr_impl( static_cast<boost::uint32_t>( x ) | 0x100 );
}

inline int countr_impl( boost::uint16_t x ) BOOST_NOEXCEPT
{
    return boost::core::detail::countr_impl( static_cast<boost::uint32_t>( x ) | 0x10000 );
}

} // namespace detail

template<class T>
int countr_zero( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) == sizeof(boost::uint8_t) || sizeof(T) == sizeof(boost::uint16_t) || sizeof(T) == sizeof(boost::uint32_t) || sizeof(T) == sizeof(boost::uint64_t) );

    if( sizeof(T) == sizeof(boost::uint8_t) )
    {
        return boost::core::detail::countr_impl( static_cast<boost::uint8_t>( x ) );
    }
    else if( sizeof(T) == sizeof(boost::uint16_t) )
    {
        return boost::core::detail::countr_impl( static_cast<boost::uint16_t>( x ) );
    }
    else if( sizeof(T) == sizeof(boost::uint32_t) )
    {
        return boost::core::detail::countr_impl( static_cast<boost::uint32_t>( x ) );
    }
    else
    {
        return boost::core::detail::countr_impl( static_cast<boost::uint64_t>( x ) );
    }
}

#endif // defined(__GNUC__) || defined(__clang__)

template<class T>
BOOST_CONSTEXPR int countr_one( T x ) BOOST_NOEXCEPT
{
    return boost::core::countr_zero( static_cast<T>( ~x ) );
}

// popcount

#if defined(__GNUC__) || defined(__clang__)

#if defined(__clang__) && __clang_major__ * 100 + __clang_minor__ < 304
# define BOOST_CORE_POPCOUNT_CONSTEXPR
#else
# define BOOST_CORE_POPCOUNT_CONSTEXPR BOOST_CONSTEXPR
#endif

namespace detail
{

BOOST_CORE_POPCOUNT_CONSTEXPR inline int popcount_impl( unsigned char x ) BOOST_NOEXCEPT
{
    return __builtin_popcount( x );
}

BOOST_CORE_POPCOUNT_CONSTEXPR inline int popcount_impl( unsigned short x ) BOOST_NOEXCEPT
{
    return __builtin_popcount( x );
}

BOOST_CORE_POPCOUNT_CONSTEXPR inline int popcount_impl( unsigned int x ) BOOST_NOEXCEPT
{
    return __builtin_popcount( x );
}

BOOST_CORE_POPCOUNT_CONSTEXPR inline int popcount_impl( unsigned long x ) BOOST_NOEXCEPT
{
    return __builtin_popcountl( x );
}

BOOST_CORE_POPCOUNT_CONSTEXPR inline int popcount_impl( boost::ulong_long_type x ) BOOST_NOEXCEPT
{
    return __builtin_popcountll( x );
}

} // namespace detail

#undef BOOST_CORE_POPCOUNT_CONSTEXPR

template<class T>
BOOST_CONSTEXPR int popcount( T x ) BOOST_NOEXCEPT
{
    return boost::core::detail::popcount_impl( x );
}

#else // defined(__GNUC__) || defined(__clang__)

namespace detail
{

BOOST_CXX14_CONSTEXPR inline int popcount_impl( boost::uint32_t x ) BOOST_NOEXCEPT
{
    x = x - ( ( x >> 1 ) & 0x55555555 );
    x = ( x & 0x33333333 ) + ( ( x >> 2 ) & 0x33333333 );
    x = ( x + ( x >> 4 ) ) & 0x0F0F0F0F;

    return static_cast<unsigned>( ( x * 0x01010101 ) >> 24 );
}

BOOST_CXX14_CONSTEXPR inline int popcount_impl( boost::uint64_t x ) BOOST_NOEXCEPT
{
    x = x - ( ( x >> 1 ) & 0x5555555555555555 );
    x = ( x & 0x3333333333333333 ) + ( ( x >> 2 ) & 0x3333333333333333 );
    x = ( x + ( x >> 4 ) ) & 0x0F0F0F0F0F0F0F0F;

    return static_cast<unsigned>( ( x * 0x0101010101010101 ) >> 56 );
}

} // namespace detail

template<class T>
BOOST_CXX14_CONSTEXPR int popcount( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) <= sizeof(boost::uint64_t) );

    if( sizeof(T) <= sizeof(boost::uint32_t) )
    {
        return boost::core::detail::popcount_impl( static_cast<boost::uint32_t>( x ) );
    }
    else
    {
        return boost::core::detail::popcount_impl( static_cast<boost::uint64_t>( x ) );
    }
}

#endif // defined(__GNUC__) || defined(__clang__)

// rotating

template<class T>
BOOST_CXX14_CONSTEXPR T rotl( T x, int s ) BOOST_NOEXCEPT
{
    unsigned const mask = std::numeric_limits<T>::digits - 1;
    return x << (s & mask) | x >> ((-s) & mask);
}

template<class T>
BOOST_CXX14_CONSTEXPR T rotr( T x, int s ) BOOST_NOEXCEPT
{
    unsigned const mask = std::numeric_limits<T>::digits - 1;
    return x >> (s & mask) | x << ((-s) & mask);
}

// integral powers of 2

template<class T>
BOOST_CONSTEXPR bool has_single_bit( T x ) BOOST_NOEXCEPT
{
    return x != 0 && ( x & ( x - 1 ) ) == 0;
}

// bit_width should return int, https://cplusplus.github.io/LWG/issue3656

template<class T>
BOOST_CONSTEXPR T bit_width( T x ) BOOST_NOEXCEPT
{
    return static_cast<T>(
        std::numeric_limits<T>::digits - boost::core::countl_zero( x ) );
}

template<class T>
BOOST_CONSTEXPR T bit_floor( T x ) BOOST_NOEXCEPT
{
    return x == 0? 0: T(1) << ( boost::core::bit_width( x ) - 1 );
}

namespace detail
{

BOOST_CXX14_CONSTEXPR inline boost::uint32_t bit_ceil_impl( boost::uint32_t x ) BOOST_NOEXCEPT
{
    if( x == 0 )
    {
        return 0;
    }

    --x;

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    ++x;

    return x;
}

BOOST_CXX14_CONSTEXPR inline boost::uint64_t bit_ceil_impl( boost::uint64_t x ) BOOST_NOEXCEPT
{
    if( x == 0 )
    {
        return 0;
    }

    --x;

    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;

    ++x;

    return x;
}

} // namespace detail

template<class T>
BOOST_CXX14_CONSTEXPR T bit_ceil( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( sizeof(T) <= sizeof(boost::uint64_t) );

    if( sizeof(T) <= sizeof(boost::uint32_t) )
    {
        return static_cast<T>( boost::core::detail::bit_ceil_impl( static_cast<boost::uint32_t>( x ) ) );
    }
    else
    {
        return static_cast<T>( boost::core::detail::bit_ceil_impl( static_cast<boost::uint64_t>( x ) ) );
    }
}

// endian

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

# define BOOST_CORE_BIT_NATIVE_INITIALIZER =little

#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

# define BOOST_CORE_BIT_NATIVE_INITIALIZER =big

#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__

# define BOOST_CORE_BIT_NATIVE_INITIALIZER

#elif defined(__LITTLE_ENDIAN__)

# define BOOST_CORE_BIT_NATIVE_INITIALIZER =little

#elif defined(__BIG_ENDIAN__)

# define BOOST_CORE_BIT_NATIVE_INITIALIZER =big

#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)

# define BOOST_CORE_BIT_NATIVE_INITIALIZER =little

#else

# define BOOST_CORE_BIT_NATIVE_INITIALIZER

#endif

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum class endian
{
    big,
    little,
    native BOOST_CORE_BIT_NATIVE_INITIALIZER
};

typedef endian endian_type;

#else

namespace endian
{

enum type
{
    big,
    little,
    native BOOST_CORE_BIT_NATIVE_INITIALIZER
};

} // namespace endian

typedef endian::type endian_type;

#endif

#undef BOOST_CORE_BIT_NATIVE_INITIALIZER

} // namespace core
} // namespace boost

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif  // #ifndef BOOST_CORE_BIT_HPP_INCLUDED

/* bit.hpp
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
*/