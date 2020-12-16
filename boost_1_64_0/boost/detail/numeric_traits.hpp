// (C) Copyright David Abrahams 2001, Howard Hinnant 2001.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Template class numeric_traits<Number> --
//
//    Supplies:
//
//      typedef difference_type -- a type used to represent the difference
//      between any two values of Number.
//
//    Support:
//      1. Not all specializations are supplied
//
//      2. Use of specializations that are not supplied will cause a
//      compile-time error
//
//      3. Users are free to specialize numeric_traits for any type.
//
//      4. Right now, specializations are only supplied for integer types.
//
//      5. On implementations which do not supply compile-time constants in
//      std::numeric_limits<>, only specializations for built-in integer types
//      are supplied.
//
//      6. Handling of numbers whose range of representation is at least as
//      great as boost::intmax_t can cause some differences to be
//      unrepresentable in difference_type:
//
//        Number    difference_type
//        ------    ---------------
//        signed    Number
//        unsigned  intmax_t
//
// template <class Number> typename numeric_traits<Number>::difference_type
// numeric_distance(Number x, Number y)
//    computes (y - x), attempting to avoid overflows.
//

// See http://www.boost.org for most recent version including documentation.

// Revision History
// 11 Feb 2001 - Use BOOST_STATIC_CONSTANT (David Abrahams)
// 11 Feb 2001 - Rolled back ineffective Borland-specific code
//               (David Abrahams)
// 10 Feb 2001 - Rolled in supposed Borland fixes from John Maddock, but
//               not seeing any improvement yet (David Abrahams)
// 06 Feb 2001 - Factored if_true out into boost/detail/select_type.hpp
//               (David Abrahams)
// 23 Jan 2001 - Fixed logic of difference_type selection, which was
//               completely wack. In the process, added digit_traits<>
//               to compute the number of digits in intmax_t even when
//               not supplied by numeric_limits<>. (David Abrahams)
// 21 Jan 2001 - Created (David Abrahams)

#ifndef BOOST_NUMERIC_TRAITS_HPP_DWA20001901
#define BOOST_NUMERIC_TRAITS_HPP_DWA20001901

#include <cstddef>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/conditional.hpp>
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#endif

namespace boost { namespace detail {

#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
  // digit_traits - compute the number of digits in a built-in integer
  // type. Needed for implementations on which numeric_limits is not specialized
  // for some integer types, like __int128 in libstdc++ (gcc).
  template <class T, bool IsSpecialized = std::numeric_limits<T>::is_specialized>
  struct digit_traits
  {
      BOOST_STATIC_CONSTANT(int, digits = std::numeric_limits<T>::digits);
  };

  // numeric_limits is not specialized; compute digits from sizeof(T)
  template <class T>
  struct digit_traits<T, false>
  {
      BOOST_STATIC_CONSTANT(int, digits = (
          sizeof(T) * std::numeric_limits<unsigned char>::digits
          - (boost::is_signed<T>::value ? 1 : 0))
          );
  };
#endif

  // Template class integer_traits<Integer> -- traits of various integer types
  // This should probably be rolled into boost::integer_traits one day, but I
  // need it to work without <limits>
  template <class Integer>
  struct integer_traits
  {
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   private:
      typedef Integer integer_type;
      typedef std::numeric_limits<integer_type> x;
   public:
      typedef typename boost::conditional<
        (int(x::is_signed)
          && (!int(x::is_bounded)
             // digits is the number of no-sign bits
             || (int(x::digits) + 1 >= digit_traits<boost::intmax_t>::digits))),
        Integer,

        typename boost::conditional<
          (int(x::digits) + 1 < digit_traits<signed int>::digits),
          signed int,

          typename boost::conditional<
            (int(x::digits) + 1 < digit_traits<signed long>::digits),
            signed long,
            boost::intmax_t
          >::type
        >::type
      >::type difference_type;
#else
      BOOST_STATIC_ASSERT(boost::is_integral<Integer>::value);

      typedef typename boost::conditional<
        (sizeof(Integer) >= sizeof(intmax_t)),

        boost::conditional<
          (boost::is_signed<Integer>::value),
          Integer,
          boost::intmax_t
        >,

        boost::conditional<
          (sizeof(Integer) < sizeof(std::ptrdiff_t)),
          std::ptrdiff_t,
          boost::intmax_t
        >
      >::type::type difference_type;
#endif
  };

  // Right now, only supports integers, but should be expanded.
  template <class Number>
  struct numeric_traits
  {
      typedef typename integer_traits<Number>::difference_type difference_type;
  };

  template <class Number>
  inline BOOST_CONSTEXPR typename numeric_traits<Number>::difference_type numeric_distance(Number x, Number y)
  {
      typedef typename numeric_traits<Number>::difference_type difference_type;
      return difference_type(y) - difference_type(x);
  }
}}

#endif // BOOST_NUMERIC_TRAITS_HPP_DWA20001901

/* numeric_traits.hpp
++YssKPCb/s9udf3X4NW+bCb2JXPFG01CkPP7S5NaaZAemFFEZZ6w3Cu6DNukNLNywEy7BcdPvdrVJ+L66vcpSyCwAQu0uR3TRC2DsEN7VadD+bPd/E54K2e/VwKb2PN29jJqzhqsxblMyop6m6OWodRfB3s24lV7pzWL9BkOm8aD76FRd7ERQ43IfopRc3jqH4Km31vJcQmtj/Tn22n4sn3pKbvxUbGNJFP5PIe6gETmTDesKzFcqXFObwfCQYBTeOTONWcHlIgsfkOSMVc6HyIz+L4cSK+2Lhfixe03vYgjlDOmbVie8p3Hxb7sYgMUwC76+Y9TbANfDhasUpYNd4lUpvv4VWs9FVcr0YZT6bSKjYZPiH0Ugxlc5rRzPt6srviMMxR+/CNsI5GxgmeSK/BkMhohnzYEkdZMM21S3oWJvUTgjg+NwkPaQGaMzdSOA/rY8jPaFkvvUJ+anIycBnHDdgbyhBNH/IQ9ze/fjxHfdYtGuUz6ihqAkftwyjapO+DYPT+5kgM9R/72V798petLW2ufgnqV7/AKWYcVlS7uq7U2Hi32ejNa6y8i0/nFRTMvoRJ/QTo9YGvm8d6d8wbeXiRa6EZv/LIZnxzla4WKeBKEW4M8h0U3BMCrqgQJ4VyYFvBseUHW003FCRFulLHRyZyfPXvmKLfx8yvPpAtuZfeWK6G1/7HhcWb5MpWepgrWwF4HOeRXNnwvpbDeaOK7X0pFUT/bxHLX6pv+wA26ke6Vt7ZkPx5q6ldc4R5JGsbDiwkXRldwYdvPDJ2fmVON0GlS4F0o7ER7xf3SnfBSTqL74VT9p8g+5DX+GD/dZG2aX45XZp3YHJRnBUNJlxu/YJ22iCNM+/teJ2SjoV38S3ibPhLxuRcwuRaMyY+wKQAiSMYzNMBQNjQ4U4+Dru6FkcL+4NLnQjxTAcIfOQYeHlvX5dWnT5YnS5kFwxyD8kILEbrNmSywaioOCyjwt7/b2NL1B+Hb1U8fzvvbWL69her4/jb2bRJyy97uYSMzf/V4T+rdeaf5zJOpGnlX7q2Hf55+nPyaOq9T7U49Se8/3kN3/0/itdeTzOoMffuOO21Qs/vy2UO6/98m/rf1576c3LNu9Grzuv/Gw3fwmWO/Ck/+htLebc5Ko8ORKWcVjLzWY9j/Sd9pO2pj6U36e+EJA++FmjohiCm7f6oQ6GfTv9yeVWjd24D0gR0yLOMGcArMf56J/x5Yzlu6rjZSV7odtjMtqeuAdh4ylHbU28UEFt0/8fPtdHHyg0K/8ePRfWxTgiy/+ONpI+1m7+qN7ZHH8uWv9vnOY0SBgBBBSLotpQM2t7JJyFbDnnEAVnYko+AtzlnRLm1rJIMHAZvHZFYqKkJRSajQqm3rpu3bkcuxPbM6AGygqVwun7UW5eS4Qh3u581UYGt/7dnFf86p0AZ8UAj/yOpH3C3q+CQ3ockR2+cM8jVkEyvG84Z5KRFgxPqi7GIPc8ICcsM0gB57nncUl8IVY8JAG27fCvStkFg4aSvycfBOQbIyflAafqhG//kRhJlrL81fSnFpf5gKxHEl1CiHsAJK4Q3JhRHF+BrWY/W9FHw0nyCGzG9+mzK0gNZosdA3iRTiNwc49JvaYB9FEuC8+LJZ9N5EfLZFxwETMsbyzgZXdFeCYrjADpXBG3E3XMMer0cA//xqiN+IUXrmqZQVaM3dEbT9d1DDZ+00g8uZX/nExgCxvMbRZvQsBrjU/gU1IyFXXGMT2GE7YIYSX/I59kUCFO+geA/O5ALutkTfNOqe54N7bfRRe3na03fD3lYpREQEwjlvmx8tR3nzFU5l3dolHX8R6OQxiPNPDoOTqjH27yMtQ1qyIQ=
*/