//  Boost integer/integer_mask.hpp header file  ------------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

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