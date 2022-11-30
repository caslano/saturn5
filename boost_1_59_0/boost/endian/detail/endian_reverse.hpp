#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED

// Copyright 2019, 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/detail/intrinsic.hpp>
#include <boost/endian/detail/is_scoped_enum.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <cstddef>
#include <cstring>

#if defined(BOOST_ENDIAN_NO_INTRINSICS)
# if defined(BOOST_NO_CXX14_CONSTEXPR)
#  define BOOST_ENDIAN_CONSTEXPR
# else
#  define BOOST_ENDIAN_CONSTEXPR constexpr
# endif
#else
# if defined(BOOST_ENDIAN_CONSTEXPR_INTRINSICS)
#  define BOOST_ENDIAN_CONSTEXPR BOOST_CONSTEXPR
# else
#  define BOOST_ENDIAN_CONSTEXPR
# endif
#endif

namespace boost
{
namespace endian
{

namespace detail
{

//  -- portable approach suggested by tymofey, with avoidance of undefined behavior
//     as suggested by Giovanni Piero Deretta, with a further refinement suggested
//     by Pyry Jahkola.
//  -- intrinsic approach suggested by reviewers, and by David Stone, who provided
//     his Boost licensed macro implementation (detail/intrinsic.hpp)

inline uint8_t BOOST_CONSTEXPR endian_reverse_impl( uint8_t x ) BOOST_NOEXCEPT
{
    return x;
}

inline uint16_t BOOST_ENDIAN_CONSTEXPR endian_reverse_impl( uint16_t x ) BOOST_NOEXCEPT
{
#ifdef BOOST_ENDIAN_NO_INTRINSICS

    return (x << 8) | (x >> 8);

#else

    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_2(x);

#endif
}

inline uint32_t BOOST_ENDIAN_CONSTEXPR endian_reverse_impl( uint32_t x ) BOOST_NOEXCEPT
{
#ifdef BOOST_ENDIAN_NO_INTRINSICS

    uint32_t step16 = x << 16 | x >> 16;
    return ((step16 << 8) & 0xff00ff00) | ((step16 >> 8) & 0x00ff00ff);

#else

    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_4(x);

#endif
}

inline uint64_t BOOST_ENDIAN_CONSTEXPR endian_reverse_impl( uint64_t x ) BOOST_NOEXCEPT
{
#ifdef BOOST_ENDIAN_NO_INTRINSICS

    uint64_t step32 = x << 32 | x >> 32;
    uint64_t step16 = (step32 & 0x0000FFFF0000FFFFULL) << 16 | (step32 & 0xFFFF0000FFFF0000ULL) >> 16;
    return (step16 & 0x00FF00FF00FF00FFULL) << 8 | (step16 & 0xFF00FF00FF00FF00ULL) >> 8;

#else

    return BOOST_ENDIAN_INTRINSIC_BYTE_SWAP_8(x);

# endif
}

#if defined(BOOST_HAS_INT128)

inline uint128_type BOOST_ENDIAN_CONSTEXPR endian_reverse_impl( uint128_type x ) BOOST_NOEXCEPT
{
    return endian_reverse_impl( static_cast<uint64_t>( x >> 64 ) ) |
        static_cast<uint128_type>( endian_reverse_impl( static_cast<uint64_t>( x ) ) ) << 64;
}

#endif

// is_endian_reversible

template<class T> struct is_endian_reversible: boost::integral_constant<bool,
    (boost::is_integral<T>::value && !boost::is_same<T, bool>::value) || is_scoped_enum<T>::value>
{
};

// is_endian_reversible_inplace

template<class T> struct is_endian_reversible_inplace: boost::integral_constant<bool,
    boost::is_integral<T>::value || boost::is_enum<T>::value || boost::is_same<T, float>::value || boost::is_same<T, double>::value>
{
};

} // namespace detail

// Requires:
//   T is non-bool integral or scoped enumeration type

template<class T> inline BOOST_CONSTEXPR
    typename enable_if_< !is_class<T>::value, T >::type
    endian_reverse( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( detail::is_endian_reversible<T>::value );

    typedef typename detail::integral_by_size< sizeof(T) >::type uintN_t;

    return static_cast<T>( detail::endian_reverse_impl( static_cast<uintN_t>( x ) ) );
}

// Requires:
//   T is integral, enumeration, float or double

template<class T> inline
    typename enable_if_< !is_class<T>::value >::type
    endian_reverse_inplace( T & x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( detail::is_endian_reversible_inplace<T>::value );

    typename detail::integral_by_size< sizeof(T) >::type x2;

    std::memcpy( &x2, &x, sizeof(T) );

    x2 = detail::endian_reverse_impl( x2 );

    std::memcpy( &x, &x2, sizeof(T) );
}

// Default implementation for user-defined types

template<class T> inline
    typename enable_if_< is_class<T>::value >::type
    endian_reverse_inplace( T & x ) BOOST_NOEXCEPT
{
    x = endian_reverse( x );
}

// endian_reverse_inplace for arrays

template<class T, std::size_t N>
inline void endian_reverse_inplace( T (&x)[ N ] ) BOOST_NOEXCEPT
{
    for( std::size_t i = 0; i < N; ++i )
    {
        endian_reverse_inplace( x[i] );
    }
}

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED

/* endian_reverse.hpp
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
*/