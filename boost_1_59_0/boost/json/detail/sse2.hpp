//
// Copyright (c) 2019 Peter Dimov (pdimov at gmail dot com),
//                    Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_SSE2_HPP
#define BOOST_JSON_DETAIL_SSE2_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/detail/utf8.hpp>
#include <cstddef>
#include <cstring>
#ifdef BOOST_JSON_USE_SSE2
# include <emmintrin.h>
# include <xmmintrin.h>
# ifdef _MSC_VER
#  include <intrin.h>
# endif
#endif

BOOST_JSON_NS_BEGIN
namespace detail {

#ifdef BOOST_JSON_USE_SSE2

template<bool AllowBadUTF8>
inline
const char*
count_valid(
    char const* p,
    const char* end) noexcept
{
    __m128i const q1 = _mm_set1_epi8( '\x22' ); // '"'
    __m128i const q2 = _mm_set1_epi8( '\\' ); // '\\'
    __m128i const q3 = _mm_set1_epi8( 0x1F );

    while(end - p >= 16)
    {
        __m128i v1 = _mm_loadu_si128( (__m128i const*)p );
        __m128i v2 = _mm_cmpeq_epi8( v1, q1 ); // quote
        __m128i v3 = _mm_cmpeq_epi8( v1, q2 ); // backslash
        __m128i v4 = _mm_or_si128( v2, v3 ); // combine quotes and backslash
        __m128i v5 = _mm_min_epu8( v1, q3 );
        __m128i v6 = _mm_cmpeq_epi8( v5, v1 ); // controls
        __m128i v7 = _mm_or_si128( v4, v6 ); // combine with control

        int w = _mm_movemask_epi8( v7 );

        if( w != 0 )
        {
            int m;
#if defined(__GNUC__) || defined(__clang__)
            m = __builtin_ffs( w ) - 1;
#else
            unsigned long index;
            _BitScanForward( &index, w );
            m = index;
#endif
            return p + m;
        }

        p += 16;
    }

    while(p != end)
    {
        const unsigned char c = *p;
        if(c == '\x22' || c == '\\' || c < 0x20)
            break;
        ++p;
    }

    return p;
}

template<>
inline
const char*
count_valid<false>(
    char const* p,
    const char* end) noexcept
{
    __m128i const q1 = _mm_set1_epi8( '\x22' ); // '"'
    __m128i const q2 = _mm_set1_epi8( '\\' );
    __m128i const q3 = _mm_set1_epi8( 0x20 );

    while(end - p >= 16)
    {
        __m128i v1 = _mm_loadu_si128( (__m128i const*)p );

        __m128i v2 = _mm_cmpeq_epi8( v1, q1 );
        __m128i v3 = _mm_cmpeq_epi8( v1, q2 );
        __m128i v4 = _mm_cmplt_epi8( v1, q3 );

        __m128i v5 = _mm_or_si128( v2, v3 );
        __m128i v6 = _mm_or_si128( v5, v4 );

        int w = _mm_movemask_epi8( v6 );

        if( w != 0 )
        {
            int m;
#if defined(__GNUC__) || defined(__clang__)
            m = __builtin_ffs( w ) - 1;
#else
            unsigned long index;
            _BitScanForward( &index, w );
            m = index;
#endif
            p += m;
            break;
        }

        p += 16;
    }

    while(p != end)
    {
        const unsigned char c = *p;
        if(c == '\x22' || c == '\\' || c < 0x20)
            break;
        if(c < 0x80)
        {
            ++p;
            continue;
        }
        // validate utf-8
        uint16_t first = classify_utf8(c & 0x7F);
        uint8_t len = first & 0xFF;
        if(BOOST_JSON_UNLIKELY(end - p < len))
            break;
        if(BOOST_JSON_UNLIKELY(! is_valid_utf8(p, first)))
            break;
        p += len;
    }

    return p;
}

#else

template<bool AllowBadUTF8>
char const*
count_valid(
    char const* p,
    char const* end) noexcept
{
    while(p != end)
    {
        const unsigned char c = *p;
        if(c == '\x22' || c == '\\' || c < 0x20)
            break;
        ++p;
    }

    return p;
}

template<>
inline
char const*
count_valid<false>(
    char const* p,
    char const* end) noexcept
{
    while(p != end)
    {
        const unsigned char c = *p;
        if(c == '\x22' || c == '\\' || c < 0x20)
            break;
        if(c < 0x80)
        {
            ++p;
            continue;
        }
        // validate utf-8
        uint16_t first = classify_utf8(c & 0x7F);
        uint8_t len = first & 0xFF;
        if(BOOST_JSON_UNLIKELY(end - p < len))
            break;
        if(BOOST_JSON_UNLIKELY(! is_valid_utf8(p, first)))
            break;
        p += len;
    }

    return p;
}

#endif

// KRYSTIAN NOTE: does not stop to validate
// count_unescaped

#ifdef BOOST_JSON_USE_SSE2

inline
size_t
count_unescaped(
    char const* s,
    size_t n) noexcept
{

    __m128i const q1 = _mm_set1_epi8( '\x22' ); // '"'
    __m128i const q2 = _mm_set1_epi8( '\\' ); // '\\'
    __m128i const q3 = _mm_set1_epi8( 0x1F );

    char const * s0 = s;

    while( n >= 16 )
    {
        __m128i v1 = _mm_loadu_si128( (__m128i const*)s );
        __m128i v2 = _mm_cmpeq_epi8( v1, q1 ); // quote
        __m128i v3 = _mm_cmpeq_epi8( v1, q2 ); // backslash
        __m128i v4 = _mm_or_si128( v2, v3 ); // combine quotes and backslash
        __m128i v5 = _mm_min_epu8( v1, q3 );
        __m128i v6 = _mm_cmpeq_epi8( v5, v1 ); // controls
        __m128i v7 = _mm_or_si128( v4, v6 ); // combine with control

        int w = _mm_movemask_epi8( v7 );

        if( w != 0 )
        {
            int m;
#if defined(__GNUC__) || defined(__clang__)
            m = __builtin_ffs( w ) - 1;
#else
            unsigned long index;
            _BitScanForward( &index, w );
            m = index;
#endif

            s += m;
            break;
        }

        s += 16;
        n -= 16;
    }

    return s - s0;
}

#else

inline
std::size_t
count_unescaped(
    char const*,
    std::size_t) noexcept
{
    return 0;
}

#endif

// count_digits

#ifdef BOOST_JSON_USE_SSE2

// assumes p..p+15 are valid
inline int count_digits( char const* p ) noexcept
{
    __m128i v1 = _mm_loadu_si128( (__m128i const*)p );
    v1 = _mm_add_epi8(v1, _mm_set1_epi8(70));
    v1 = _mm_cmplt_epi8(v1, _mm_set1_epi8(118));

    int m = _mm_movemask_epi8(v1);

    int n;

    if( m == 0 )
    {
        n = 16;
    }
    else
    {
#if defined(__GNUC__) || defined(__clang__)
        n = __builtin_ffs( m ) - 1;
#else
        unsigned long index;
        _BitScanForward( &index, m );
        n = static_cast<int>(index);
#endif
    }

    return n;
}

#else

// assumes p..p+15 are valid
inline int count_digits( char const* p ) noexcept
{
    int n = 0;

    for( ; n < 16; ++n )
    {
        unsigned char const d = *p++ - '0';
        if(d > 9) break;
    }

    return n;
}

#endif

// parse_unsigned

inline uint64_t parse_unsigned( uint64_t r, char const * p, std::size_t n ) noexcept
{
    while( n >= 4 )
    {
        // faster on on clang for x86,
        // slower on gcc
#ifdef __clang__
        r = r * 10 + p[0] - '0';
        r = r * 10 + p[1] - '0';
        r = r * 10 + p[2] - '0';
        r = r * 10 + p[3] - '0';
#else
        uint32_t v;
        std::memcpy( &v, p, 4 );

        v -= 0x30303030;

        unsigned w0 = v & 0xFF;
        unsigned w1 = (v >> 8) & 0xFF;
        unsigned w2 = (v >> 16) & 0xFF;
        unsigned w3 = (v >> 24);

#ifdef BOOST_JSON_BIG_ENDIAN
        r = (((r * 10 + w3) * 10 + w2) * 10 + w1) * 10 + w0;
#else
        r = (((r * 10 + w0) * 10 + w1) * 10 + w2) * 10 + w3;
#endif
#endif
        p += 4;
        n -= 4;
    }

    switch( n )
    {
    case 0:
        break;
    case 1:
        r = r * 10 + p[0] - '0';
        break;
    case 2:
        r = r * 10 + p[0] - '0';
        r = r * 10 + p[1] - '0';
        break;
    case 3:
        r = r * 10 + p[0] - '0';
        r = r * 10 + p[1] - '0';
        r = r * 10 + p[2] - '0';
        break;
    }
    return r;
}

// KRYSTIAN: this function is unused
// count_leading

/*
#ifdef BOOST_JSON_USE_SSE2

// assumes p..p+15
inline std::size_t count_leading( char const * p, char ch ) noexcept
{
    __m128i const q1 = _mm_set1_epi8( ch );

    __m128i v = _mm_loadu_si128( (__m128i const*)p );

    __m128i w = _mm_cmpeq_epi8( v, q1 );

    int m = _mm_movemask_epi8( w ) ^ 0xFFFF;

    std::size_t n;

    if( m == 0 )
    {
        n = 16;
    }
    else
    {
#if defined(__GNUC__) || defined(__clang__)
        n = __builtin_ffs( m ) - 1;
#else
        unsigned long index;
        _BitScanForward( &index, m );
        n = index;
#endif
    }

    return n;
}

#else

// assumes p..p+15
inline std::size_t count_leading( char const * p, char ch ) noexcept
{
    std::size_t n = 0;

    for( ; n < 16 && *p == ch; ++p, ++n );

    return n;
}

#endif
*/

// count_whitespace

#ifdef BOOST_JSON_USE_SSE2

inline const char* count_whitespace( char const* p, const char* end ) noexcept
{
    if( p == end )
    {
        return p;
    }

    if( static_cast<unsigned char>( *p ) > 0x20 )
    {
        return p;
    }

    __m128i const q1 = _mm_set1_epi8( ' ' );
    __m128i const q2 = _mm_set1_epi8( '\n' );
    __m128i const q3 = _mm_set1_epi8( 4 ); // '\t' | 4 == '\r'
    __m128i const q4 = _mm_set1_epi8( '\r' );

    while( end - p >= 16 )
    {
        __m128i v0 = _mm_loadu_si128( (__m128i const*)p );

        __m128i w0 = _mm_or_si128(
            _mm_cmpeq_epi8( v0, q1 ),
            _mm_cmpeq_epi8( v0, q2 ));
        __m128i v1 = _mm_or_si128( v0, q3 );
        __m128i w1 = _mm_cmpeq_epi8( v1, q4 );
        __m128i w2 = _mm_or_si128( w0, w1 );

        int m = _mm_movemask_epi8( w2 ) ^ 0xFFFF;

        if( m != 0 )
        {
#if defined(__GNUC__) || defined(__clang__)
            std::size_t c = __builtin_ffs( m ) - 1;
#else
            unsigned long index;
            _BitScanForward( &index, m );
            std::size_t c = index;
#endif

            p += c;
            return p;
        }

        p += 16;
    }

    while( p != end )
    {
        if( *p != ' ' && *p != '\t' && *p != '\r' && *p != '\n' )
        {
            return p;
        }

        ++p;
    }

    return p;
}

/*

// slightly faster on msvc-14.2, slightly slower on clang-win

inline std::size_t count_whitespace( char const * p, std::size_t n ) noexcept
{
    char const * p0 = p;

    while( n > 0 )
    {
        char ch = *p;

        if( ch == '\n' || ch == '\r' )
        {
            ++p;
            --n;
            continue;
        }

        if( ch != ' ' && ch != '\t' )
        {
            break;
        }

        ++p;
        --n;

        while( n >= 16 )
        {
            std::size_t n2 = count_leading( p, ch );

            p += n2;
            n -= n2;

            if( n2 < 16 )
            {
                break;
            }
        }
    }

    return p - p0;
}
*/

#else

inline const char* count_whitespace( char const* p, const char* end ) noexcept
{

    for(; p != end; ++p)
    {
        char const c = *p;
        if( c != ' ' && c != '\n' && c != '\r' && c != '\t' ) break;
    }

    return p;
}

#endif

} // detail
BOOST_JSON_NS_END

#endif

/* sse2.hpp
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
*/