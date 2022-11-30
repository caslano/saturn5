//  Boost integer/integer_mask.hpp header file  ------------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

//  See https://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_INTEGER_MASK_HPP
#define BOOST_INTEGER_INTEGER_MASK_HPP

#include <boost/integer_fwd.hpp>  // self include

#include <boost/config.hpp>   // for BOOST_STATIC_CONSTANT
#include <boost/integer.hpp>  // for boost::uint_t

#include <climits>  // for UCHAR_MAX, etc.
#include <cstddef>  // for std::size_t

#include <boost/limits.hpp>  // for std::numeric_limits

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
// boost/integer/integer_mask.hpp:93:35: warning: use of C99 long long integer constant
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost
{


//  Specified single-bit mask class declaration  -----------------------------//
//  (Lowest bit starts counting at 0.)

template < std::size_t Bit >
struct high_bit_mask_t
{
    typedef typename uint_t<(Bit + 1)>::least  least;
    typedef typename uint_t<(Bit + 1)>::fast   fast;

    BOOST_STATIC_CONSTANT( least, high_bit = (least( 1u ) << Bit) );
    BOOST_STATIC_CONSTANT( fast, high_bit_fast = (fast( 1u ) << Bit) );

    BOOST_STATIC_CONSTANT( std::size_t, bit_position = Bit );

};  // boost::high_bit_mask_t


//  Specified bit-block mask class declaration  ------------------------------//
//  Makes masks for the lowest N bits
//  (Specializations are needed when N fills up a type.)

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4310)  // cast truncates constant value
#endif

template < std::size_t Bits >
struct low_bits_mask_t
{
    typedef typename uint_t<Bits>::least  least;
    typedef typename uint_t<Bits>::fast   fast;

    BOOST_STATIC_CONSTANT( least, sig_bits = least(~(least(~(least( 0u ))) << Bits )) );
    BOOST_STATIC_CONSTANT( fast, sig_bits_fast = fast(sig_bits) );

    BOOST_STATIC_CONSTANT( std::size_t, bit_count = Bits );

};  // boost::low_bits_mask_t

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#define BOOST_LOW_BITS_MASK_SPECIALIZE( Type )                                  \
  template <  >  struct low_bits_mask_t< std::numeric_limits<Type>::digits >  { \
      typedef std::numeric_limits<Type>           limits_type;                  \
      typedef uint_t<limits_type::digits>::least  least;                        \
      typedef uint_t<limits_type::digits>::fast   fast;                         \
      BOOST_STATIC_CONSTANT( least, sig_bits = (~( least(0u) )) );              \
      BOOST_STATIC_CONSTANT( fast, sig_bits_fast = fast(sig_bits) );            \
      BOOST_STATIC_CONSTANT( std::size_t, bit_count = limits_type::digits );    \
  }

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4245)  // 'initializing' : conversion from 'int' to 'const boost::low_bits_mask_t<8>::least', signed/unsigned mismatch
#endif

BOOST_LOW_BITS_MASK_SPECIALIZE( unsigned char );

#if USHRT_MAX > UCHAR_MAX
BOOST_LOW_BITS_MASK_SPECIALIZE( unsigned short );
#endif

#if UINT_MAX > USHRT_MAX
BOOST_LOW_BITS_MASK_SPECIALIZE( unsigned int );
#endif

#if ULONG_MAX > UINT_MAX
BOOST_LOW_BITS_MASK_SPECIALIZE( unsigned long );
#endif

#if defined(BOOST_HAS_LONG_LONG)
    #if ((defined(ULLONG_MAX) && (ULLONG_MAX > ULONG_MAX)) ||\
        (defined(ULONG_LONG_MAX) && (ULONG_LONG_MAX > ULONG_MAX)) ||\
        (defined(ULONGLONG_MAX) && (ULONGLONG_MAX > ULONG_MAX)) ||\
        (defined(_ULLONG_MAX) && (_ULLONG_MAX > ULONG_MAX)))
    BOOST_LOW_BITS_MASK_SPECIALIZE( boost::ulong_long_type );
    #endif
#elif defined(BOOST_HAS_MS_INT64)
    #if 18446744073709551615ui64 > ULONG_MAX
    BOOST_LOW_BITS_MASK_SPECIALIZE( unsigned __int64 );
    #endif
#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#undef BOOST_LOW_BITS_MASK_SPECIALIZE


}  // namespace boost


#endif  // BOOST_INTEGER_INTEGER_MASK_HPP

/* integer_mask.hpp
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
*/