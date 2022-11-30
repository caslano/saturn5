//  boost integer.hpp header file  -------------------------------------------//

//  Copyright Beman Dawes and Daryle Walker 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

//  See https://www.boost.org/libs/integer for documentation.

//  Revision History
//   22 Sep 01  Added value-based integer templates. (Daryle Walker)
//   01 Apr 01  Modified to use new <boost/limits.hpp> header. (John Maddock)
//   30 Jul 00  Add typename syntax fix (Jens Maurer)
//   28 Aug 99  Initial version

#ifndef BOOST_INTEGER_HPP
#define BOOST_INTEGER_HPP

#include <boost/integer_fwd.hpp>  // self include

#include <boost/integer_traits.hpp>  // for boost::::boost::integer_traits
#include <boost/limits.hpp>          // for ::std::numeric_limits
#include <boost/cstdint.hpp>         // for boost::int64_t and BOOST_NO_INTEGRAL_INT64_T
#include <boost/static_assert.hpp>

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
// boost/integer.hpp:77:30: warning: use of C99 long long integer constant
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost
{

  //  Helper templates  ------------------------------------------------------//

  //  fast integers from least integers
  //  int_fast_t<> works correctly for unsigned too, in spite of the name.
  template< typename LeastInt >
  struct int_fast_t
  {
     typedef LeastInt fast;
     typedef fast     type;
  }; // imps may specialize

  namespace detail{

  //  convert category to type
  template< int Category > struct int_least_helper {}; // default is empty
  template< int Category > struct uint_least_helper {}; // default is empty

  //  specializatons: 1=long, 2=int, 3=short, 4=signed char,
  //     6=unsigned long, 7=unsigned int, 8=unsigned short, 9=unsigned char
  //  no specializations for 0 and 5: requests for a type > long are in error
#ifdef BOOST_HAS_LONG_LONG
  template<> struct int_least_helper<1> { typedef boost::long_long_type least; };
#elif defined(BOOST_HAS_MS_INT64)
  template<> struct int_least_helper<1> { typedef __int64 least; };
#endif
  template<> struct int_least_helper<2> { typedef long least; };
  template<> struct int_least_helper<3> { typedef int least; };
  template<> struct int_least_helper<4> { typedef short least; };
  template<> struct int_least_helper<5> { typedef signed char least; };
#ifdef BOOST_HAS_LONG_LONG
  template<> struct uint_least_helper<1> { typedef boost::ulong_long_type least; };
#elif defined(BOOST_HAS_MS_INT64)
  template<> struct uint_least_helper<1> { typedef unsigned __int64 least; };
#endif
  template<> struct uint_least_helper<2> { typedef unsigned long least; };
  template<> struct uint_least_helper<3> { typedef unsigned int least; };
  template<> struct uint_least_helper<4> { typedef unsigned short least; };
  template<> struct uint_least_helper<5> { typedef unsigned char least; };

  template <int Bits>
  struct exact_signed_base_helper{};
  template <int Bits>
  struct exact_unsigned_base_helper{};

  template <> struct exact_signed_base_helper<sizeof(signed char)* CHAR_BIT> { typedef signed char exact; };
  template <> struct exact_unsigned_base_helper<sizeof(unsigned char)* CHAR_BIT> { typedef unsigned char exact; };
#if USHRT_MAX != UCHAR_MAX
  template <> struct exact_signed_base_helper<sizeof(short)* CHAR_BIT> { typedef short exact; };
  template <> struct exact_unsigned_base_helper<sizeof(unsigned short)* CHAR_BIT> { typedef unsigned short exact; };
#endif
#if UINT_MAX != USHRT_MAX
  template <> struct exact_signed_base_helper<sizeof(int)* CHAR_BIT> { typedef int exact; };
  template <> struct exact_unsigned_base_helper<sizeof(unsigned int)* CHAR_BIT> { typedef unsigned int exact; };
#endif
#if ULONG_MAX != UINT_MAX && ( !defined __TI_COMPILER_VERSION__ || \
    ( __TI_COMPILER_VERSION__ >= 7000000 && !defined __TI_40BIT_LONG__ ) )
  template <> struct exact_signed_base_helper<sizeof(long)* CHAR_BIT> { typedef long exact; };
  template <> struct exact_unsigned_base_helper<sizeof(unsigned long)* CHAR_BIT> { typedef unsigned long exact; };
#endif
#if defined(BOOST_HAS_LONG_LONG) &&\
   ((defined(ULLONG_MAX) && (ULLONG_MAX != ULONG_MAX)) ||\
    (defined(ULONG_LONG_MAX) && (ULONG_LONG_MAX != ULONG_MAX)) ||\
    (defined(ULONGLONG_MAX) && (ULONGLONG_MAX != ULONG_MAX)) ||\
    (defined(_ULLONG_MAX) && (_ULLONG_MAX != ULONG_MAX)))
  template <> struct exact_signed_base_helper<sizeof(boost::long_long_type)* CHAR_BIT> { typedef boost::long_long_type exact; };
  template <> struct exact_unsigned_base_helper<sizeof(boost::ulong_long_type)* CHAR_BIT> { typedef boost::ulong_long_type exact; };
#endif


  } // namespace detail

  //  integer templates specifying number of bits  ---------------------------//

  //  signed
  template< int Bits >   // bits (including sign) required
  struct int_t : public boost::detail::exact_signed_base_helper<Bits>
  {
      BOOST_STATIC_ASSERT_MSG(Bits <= (int)(sizeof(boost::intmax_t) * CHAR_BIT),
         "No suitable signed integer type with the requested number of bits is available.");
      typedef typename boost::detail::int_least_helper
        <
#ifdef BOOST_HAS_LONG_LONG
          (Bits <= (int)(sizeof(boost::long_long_type) * CHAR_BIT)) +
#else
           1 +
#endif
          (Bits-1 <= ::std::numeric_limits<long>::digits) +
          (Bits-1 <= ::std::numeric_limits<int>::digits) +
          (Bits-1 <= ::std::numeric_limits<short>::digits) +
          (Bits-1 <= ::std::numeric_limits<signed char>::digits)
        >::least  least;
      typedef typename int_fast_t<least>::type  fast;
  };

  //  unsigned
  template< int Bits >   // bits required
  struct uint_t : public boost::detail::exact_unsigned_base_helper<Bits>
  {
     BOOST_STATIC_ASSERT_MSG(Bits <= (int)(sizeof(boost::uintmax_t) * CHAR_BIT),
         "No suitable unsigned integer type with the requested number of bits is available.");
#if (defined(BOOST_BORLANDC) || defined(__CODEGEAR__)) && defined(BOOST_NO_INTEGRAL_INT64_T)
     // It's really not clear why this workaround should be needed... shrug I guess!  JM
     BOOST_STATIC_CONSTANT(int, s =
           6 +
          (Bits <= ::std::numeric_limits<unsigned long>::digits) +
          (Bits <= ::std::numeric_limits<unsigned int>::digits) +
          (Bits <= ::std::numeric_limits<unsigned short>::digits) +
          (Bits <= ::std::numeric_limits<unsigned char>::digits));
     typedef typename detail::int_least_helper< ::boost::uint_t<Bits>::s>::least least;
#else
      typedef typename boost::detail::uint_least_helper
        <
#ifdef BOOST_HAS_LONG_LONG
          (Bits <= (int)(sizeof(boost::long_long_type) * CHAR_BIT)) +
#else
           1 +
#endif
          (Bits <= ::std::numeric_limits<unsigned long>::digits) +
          (Bits <= ::std::numeric_limits<unsigned int>::digits) +
          (Bits <= ::std::numeric_limits<unsigned short>::digits) +
          (Bits <= ::std::numeric_limits<unsigned char>::digits)
        >::least  least;
#endif
      typedef typename int_fast_t<least>::type  fast;
      // int_fast_t<> works correctly for unsigned too, in spite of the name.
  };

  //  integer templates specifying extreme value  ----------------------------//

  //  signed
#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_LONG_LONG)
  template< boost::long_long_type MaxValue >   // maximum value to require support
#else
  template< long MaxValue >   // maximum value to require support
#endif
  struct int_max_value_t
  {
      typedef typename boost::detail::int_least_helper
        <
#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_LONG_LONG)
          (MaxValue <= ::boost::integer_traits<boost::long_long_type>::const_max) +
#else
           1 +
#endif
          (MaxValue <= ::boost::integer_traits<long>::const_max) +
          (MaxValue <= ::boost::integer_traits<int>::const_max) +
          (MaxValue <= ::boost::integer_traits<short>::const_max) +
          (MaxValue <= ::boost::integer_traits<signed char>::const_max)
        >::least  least;
      typedef typename int_fast_t<least>::type  fast;
  };

#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_LONG_LONG)
  template< boost::long_long_type MinValue >   // minimum value to require support
#else
  template< long MinValue >   // minimum value to require support
#endif
  struct int_min_value_t
  {
      typedef typename boost::detail::int_least_helper
        <
#if !defined(BOOST_NO_INTEGRAL_INT64_T) && !defined(BOOST_NO_INT64_T) && defined(BOOST_HAS_LONG_LONG)
          (MinValue >= ::boost::integer_traits<boost::long_long_type>::const_min) +
#else
           1 +
#endif
          (MinValue >= ::boost::integer_traits<long>::const_min) +
          (MinValue >= ::boost::integer_traits<int>::const_min) +
          (MinValue >= ::boost::integer_traits<short>::const_min) +
          (MinValue >= ::boost::integer_traits<signed char>::const_min)
        >::least  least;
      typedef typename int_fast_t<least>::type  fast;
  };

  //  unsigned
#if !defined(BOOST_NO_INTEGRAL_INT64_T) && defined(BOOST_HAS_LONG_LONG)
  template< boost::ulong_long_type MaxValue >   // minimum value to require support
#else
  template< unsigned long MaxValue >   // minimum value to require support
#endif
  struct uint_value_t
  {
#if (defined(BOOST_BORLANDC) || defined(__CODEGEAR__))
     // It's really not clear why this workaround should be needed... shrug I guess!  JM
#if defined(BOOST_NO_INTEGRAL_INT64_T)
      BOOST_STATIC_CONSTANT(unsigned, which =
           1 +
          (MaxValue <= ::boost::integer_traits<unsigned long>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned int>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned short>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned char>::const_max));
      typedef typename detail::int_least_helper< ::boost::uint_value_t<MaxValue>::which>::least least;
#else // BOOST_NO_INTEGRAL_INT64_T
      BOOST_STATIC_CONSTANT(unsigned, which =
           1 +
          (MaxValue <= ::boost::integer_traits<boost::ulong_long_type>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned long>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned int>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned short>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned char>::const_max));
      typedef typename detail::uint_least_helper< ::boost::uint_value_t<MaxValue>::which>::least least;
#endif // BOOST_NO_INTEGRAL_INT64_T
#else
      typedef typename boost::detail::uint_least_helper
        <
#if !defined(BOOST_NO_INTEGRAL_INT64_T) && defined(BOOST_HAS_LONG_LONG)
          (MaxValue <= ::boost::integer_traits<boost::ulong_long_type>::const_max) +
#else
           1 +
#endif
          (MaxValue <= ::boost::integer_traits<unsigned long>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned int>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned short>::const_max) +
          (MaxValue <= ::boost::integer_traits<unsigned char>::const_max)
        >::least  least;
#endif
      typedef typename int_fast_t<least>::type  fast;
  };


} // namespace boost

#endif  // BOOST_INTEGER_HPP

/* integer.hpp
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
*/