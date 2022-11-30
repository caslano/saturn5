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
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
*/