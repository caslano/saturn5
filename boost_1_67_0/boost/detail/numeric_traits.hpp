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