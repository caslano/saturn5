//  boost integer.hpp header file  -------------------------------------------//

//  Copyright Beman Dawes and Daryle Walker 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

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
#if (defined(__BORLANDC__) || defined(__CODEGEAR__)) && defined(BOOST_NO_INTEGRAL_INT64_T)
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
#if (defined(__BORLANDC__) || defined(__CODEGEAR__))
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