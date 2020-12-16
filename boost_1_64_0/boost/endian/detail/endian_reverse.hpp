#ifndef BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/endian/detail/integral_by_size.hpp>
#include <boost/endian/detail/intrinsic.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/is_class.hpp>
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

} // namespace detail

// Requires:
//    T is non-bool integral

template<class T> inline BOOST_CONSTEXPR
    typename enable_if_< !is_class<T>::value, T >::type
    endian_reverse( T x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( is_integral<T>::value && !(is_same<T, bool>::value) );

    typedef typename detail::integral_by_size< sizeof(T) >::type uintN_t;

    return static_cast<T>( detail::endian_reverse_impl( static_cast<uintN_t>( x ) ) );
}

template <class EndianReversible>
inline void endian_reverse_inplace(EndianReversible& x) BOOST_NOEXCEPT
{
    x = endian_reverse( x );
}

} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_ENDIAN_REVERSE_HPP_INCLUDED

/* endian_reverse.hpp
EQR5HJa30cEokUS5PbUy9+XCPQZjlKxa42lmeO/3JHyG8SuxsEyfTDqxudxjZ0u4irjnx6jNLtRXy7AaH/HhRlXNu7YsGrtQVfq4zVzpfGx7PWZ32lX2KartPxA1CPg1BJdK7XLxxiCXpj9DvWaMUJNfXStj434lMckCYU8ocDn0gWpkOH08tvG+Yph94j8H6YNECklSWvnAWEC1LIVhoc8tlE+B2MXwtDUgKJWW5LGnQIopbb5T6tzdq4XO/cxHS+fO5Ufywuo8qn2ZlBcSP9vqYf9o/6UlK96xE9/Qar8jD3G175+sfbc8b5cHCsKxz8+AOtQaBgUkvmySL1582UAvtH5fp+iiuq2LLpogTeqYd3uRDFATetqOq779JGKOv31k0miw9lTi+lAo6YW0KdumRqxzYQO04Jgxd7O5P7iqy9yZiOhMNc5Eu7EzM94RnRlf1fEf0gIv+jH2Yg1VivXFCpuEbvCKLooTxaYT6tKYMBFeGoLm9WzJFpKTUC/hOx++/Sj4vuOVeRaQVntiQ1VHnl006JnbzA1asFCuaRLT1Yd5ybaJl2za4ULGQLXEqhpOJqdpbwMadDvVR/P8nNn0+5sltPP0F5A+ONpXNxiXbnkJXzWiFGwTW7+lTo3G1sD8KDZrSTi9BSsHAoz/bvZLJ8v2nEztsTq1JmimLVA2EZ4bZmK6JAw4IOHoUtZpjyg2Qq55Ak7NARjcnQAuKvMkngviBQ1BrAY48/s/VrbcC6eDcnh1Tn3I1J85iwm/V5xH+D320mzwW7nKgN/lpyn87rym//gVpuA/LlL4reRzo/TXz/j2CxT5xcxI+PY3zFI6f72G77DwEmV8hxW+w1IbKqLjv8Kj9DnhSdp4JG7CiiQfAvG0e748lJ9YLr4YBINxEHPhft9tNCxNsd/CSgBTKyHVy6kdkErrl4L4UqEeYZZ9jVD5jjmdsyqexEcUPwzAtyC9id7sm1cms6pXFMnGDDgGKDLhbxClJY5XsO2RIMbXH33nraox5dCYgzNe9+OXEv/ncqK3knOJ3rZekg29PXS1gd5OqVX0dubV/ac3r6D/y5NB6INtARzUe344UtpG3/kGACWkDCAPMGSvBkHL1eMM2alBkBj+yJC7NIgfIHGGXK9BJgFkH0OaNEgAIAUbFGSmBgkCZBRDghokBJCxDDlWg1TjfM8QlwYJA+QLDHmrJgmpAchXGPInDRIByHSG7NAgtQCZzZBNGiQKkPkM+a4GmQWQFoY01sQ/vLM/Keefm5KHQLoDdeRUJ12DIqQUXzRCvz0EV8jzPy7yA5p6O0WelVUR0Ed+hJKpRs4EpADIF6EJne6UJ0B8Euqval9IitqQDcoj5KcoianyGq68Rqb4entkiqg4DDtorgXHiseLAj4bKXOYAYSI+DuxqvzSYdSLewulIeXQmiDM8iCxgPCpbW7ggi2kFpJzh0ozbJb2ClHp2gXGkzpuFil2XvCOGpq9fRcrcrYFrCSnRhpu+irNLSDwb4XEdHpCWOkJYaUnhHneSuoDnzVoCb6q9lNo+At/oI7R3NEmuUYUS3Qn1lW1T6ZML3wfMqltzGVtaEmeQpAegNAgz2mLH6SJScdP+YN988+7jSn8k5EevQtHU1OngK1CrlkOWDDdm3gKgo+xItOVrPih2NGaRp3ecwtY/8uwCb+eaDx2dYQckDrmnzr4yE02k31bmp4DTpuCiLuqQi76Ig4H5lKaiqy0miutVkzJKb7ECczeksPVO3+UyoS5TPh94Mks+ZXkX4PcVPkUoXXRekBrPUIuO8U4kxfE/y7wP5YyTsOMYqUSxox8SIwRh4OBpX5oY9ekEXDb08IfF9PA0oZhRDxzSaA=
*/