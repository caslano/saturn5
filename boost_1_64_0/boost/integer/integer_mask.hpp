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
oqiMJuiEoZiOldiDM3iIL4jeivIgK0qjDpqhC0ZgLjbiOB7Bak1cID7SIT/KoAaaoCsmYzF24SJewm5DvkBy5ENVtEYvTMIK7MVFPIXVljhGGuRHTfTGdKzDQVzDvzDtqAMKojIaoQfGYQX24CjO4wYe4x289pQJqZEHZVAXrdEHIzAdK7ENx3EP7+B3IK6QDgVRFe0wFDOwAltxBLfwFkFHyokMKIyKqI+OGIXZWIfDOI+XEJ1oB6REQVRFG/TAGMzEMuzECVzHa4jOzGWRGnlQGvXQAX0wCjOwCrtwCvfxCboLxyI5cqAE6qEzRmE21mA/LuE5fiJWV/IOCqEKGqErhmImlmMbjuE6XsHuRgwiEbKhFOqiI/pjLGZhJTbjEK7hJb4j6E77ICmyoQzqozcmYAG24gxu4TlUD/IfMqIsWqAbBmMmlmMnruE5PkL35PksEiELiqEKmqEPJmIhtuIE7uBfyF60C5IhM/KiJGqiDQZjJhZjI/bjFG7hJezetA+SIBuKohzqoi0GYCzmYw124CRu4RVEH74fiZENxVAZTdENwzAdi7Eee3Acd/AJYV/mhUiN3CiOWmiDwZiMldiFs3iAz4jRj/hBLpRGTbREf0zCKuzHeTzCe8j+9CmkRn5UQyt0wwQsxg6cx2P8RDCAeQ0yIC9Koz7aox8mYTF24Azu4g3UQNoFCZEOeVAeDdARwzALy7EDJ3ATL6EGkTeQDvlREU3RE+OwANtwAY/xBe5gYg4pkRdlUAdt0Q8TsQgbcQjX8RpyCOMlkiAj8qEcaqIl+mIC5mMNtuIoruMtnKHkHKRDYVRBKwzCBCzBBpzGM8hh3PcgC8qjOQZjHlZjO87gNt4h+nDaEKmRCyVQHa3QB6MwBxtwBFfxCnIE9UIKZEcp1EFLdEZ/jMdCbMcZXMczfIYzkn6PxMiKoqiJNuiNIZiMRdiCf3AJD/AWahTHIwmyoRRqoA36YCRmYzV24RSu4wk+QIwmfpACOVACFVAXHTEa87AOh3AJz/ANUcYQs0iKjCiCqmiN/piAhbBYoRSWtJTlWNoylmt5lm8FVmhFrChWVCuaFd2KYf3CGmZMK5b1q/WbFdsiyqy41u9WPDaf+cNKYCW0ErG+mcRKav1pJWMjhhRWSiuVlZrX4aW10lnprQxseJ3Jysz6Z1Ze5ZXdymHltHLxQtM8Vl4rn5WfVzUXtApZha0ibJRVzCpulWCVtJRV2ipjlbXK8ZK9ClZFq5JVmW2GqlrVrOqsn9a0alm1rTpWXbatqW81sBpajXgJQhOrqdXMam61sFparazWrLG2tdpZ7a0OVkerk9XZ6mJ1tbpZ3a0eVk+rF6uvfay+Vj+rvzXAGmgNsgZbQ6yh1jBruDXCGsm67GhrjDXWGmeNtyZYE61J1mRrijXVmmZNt2ZYM61Z1mxrjjWXtdv51l/WAmuhtchabC2xllrLrOXWCmultcpaba1hXXed9be13tpgbbQ2WZutLdZWa5u13dph7bR2seK7x9pr7bP2Wwesf6yD1iHrsHXEOmods45bJ6yT1inrtHXGOmuds85bF6yLrA5ftq5YV61r1nXrhnXTumXdtu5Yd6171n3rgfXQesTa8RPrqfXMem69sF5ar6zX1hvrrfXO+td6b32wPrKu/Nn6Yn21vlnfrR/WTy6/bQtb2sp2bG0b27U927cDO7QjdhQ7qh3Njm7HsH+x/2PHtGPZv9q/2bHtOPZ/7bj273Y8O779h53ATmgnshPbSeyk9p92Mju5ncJOaaeyU9tp7LR2Oju9ncHOaGeyM9tZ7Kx2Nju7ncPOaeeyc9t57Lx2Pju/XcAuaBeyC9tF7KJ2Mbu4XcIuaZc=
*/