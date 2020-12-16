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
aZB9mFwjOf0ZrRoENYYfy7+VUjPySCR59dfLut20NIYWfCUJW9uCzATtPHQSHjhuUw3Kdq84D12P85CKJ3HfHC7aQmIm2ydEN3sAVuT5x1sM0ZNDHss6j6N+mm3ionnnp/jbe2BawbH/lm/wEqCVLaFuF0nIa0DmSVBJz4C7wpzCVB4tsGnmrPQ4Km131/CAWDwtlcZm76YZNIXbXQ3OTUwBYmkkNiEfjlaWdpBS8DkaZ/fCEcuXs1LNyIGAXk3OSnNhqrIyp8Zl2c43j/K1y6JG0iBWpTb0JV2d6sr5wmtB6C4fL6xdCpqgdBZk0lVvktYlPX0KsCu21VS1059JU9sW3i2OXh/gF+kdu28DV6VdTrWvGFIkaT+Ppj/SuYepz7RUBT2r74EdA93rDKrCSvNnORiVWhw4BQjWaN04kxXmHHIhABvQ528YhzSi9d//SRzSLvD/ymX52oO25nyJ48IQHKls99AEmRNUdlt36U6nIO5JrJG4p509TIvuXChfnqt4EmPCQziJvYcS5pzsKR6eikoxgiOK31Z39OlscpmLU92Wv7PYVwCU8QUgyHj7d57SWv/R8cO01U34YXMTftBWoP9rgSjUPMrw2CRLGYytYfciE2bhpCd4q9Mqe5Wa/9PVP+78cSFksVuDP/686uj4IwWNPQY9bdDSV6+Ko6W9xSp0n1xC8SnY6J9B9+bnztZp6dpSSUs/VWrQ0tFQCcDnQkkdBYXEIrQXVqrJW5vI36ImJ3o6+UvSNzWyHT+gn7dGlnmUPNCW6NecCxyTrX4nCCJg30/PIfb9ki09GNbJ4UAWaMZViBFW96h/Mz/GKtUfXuX+E1mIRexxvG9bcCuW38DJqXMsocmpvmIu7vXqwd6dTdL22O2igt1C+0tY0soLTbbWC09mwTkgE18jIEhvqPcgGv2U3XOClZJVJ28AGtWDj4FM7IhMxkDcKsjEVJCJO7FAjUIO331QBM8Z3+x8rSEd5lbrl4hSsfzVPz8macUlKIJoplGimRqJZgZG0wfYgGZKUo3iH9WKn/tCXhQt1Gam/gbkRxVWg1RE0oq3Jal4OeLyovVj8Ddx0bagxZS+wGKqxzdYCnoR/6/i2xPf7YgztTG3kR8Qh21+mk9S3Hvy2v++Tyz9Fl0ZQ7+dgps2QF3qAFBPOYpBv52F85OkovbmkXLLRr5URTfsFiBgnw/aCvGb83j+2RZPYtUUWpkpr0KnSEh06fTW8VMouv3aQr3tW2PoqcuJL0kaXZDHtXORgL22avo2QUkxop+IGC16/wGbCgoyF0RkqFA27gcN3mr3n28fHb9tuTeOPvKe9U/RR1dorBxt0obJqoU93A/kduFPJW+mjeDtBeJEvDi2RK+52kq8PldNw/Qp7kRkaVvjTjQJdUJDnDNfXY47Q2zvScLiCbUs84Pb2zh2QwcO822HGFy4KIWbzqM1sLGX6SH/jTv7O+rqv6JcCga0Y3QQ7KRQIJHbEmpvatLxTfeR4TfWnvygKp3/D4aWHA99DHJjrJ2LwfF/KUZB7XQnttGmHq99TvS4M3ocn83oP+2iEd5F/9uK/ldz021RD8eDwe+rv96sjYeVyac9gnYyXSs36lZ+NPmHFUeHx99jt2ux/x8j/Q2PxKRv6R95daWONGCjlAUAElEGxzzel3HwQKr/0uCBa/0nqb/ZxLGIT6CTMur8heJUA2uNawBMQrpWnYAskszJf5gjHZ9ZPOZt+yeHU8cn31Ro3aJv6oywRwWyqD0TGO2su6RR82QNwdSYovgQbQBh8EiacSy8YZT/m4pj4aurUBMYSUw46f3jQkva/FccfT6HhuPw0fX9gY/i6c9v3oqhP/2DiVB+oRM=
*/