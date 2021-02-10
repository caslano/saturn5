// -----------------------------------------------------------
// integer_log2.hpp
//
//   Gives the integer part of the logarithm, in base 2, of a
// given number. Behavior is undefined if the argument is <= 0.
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_INTEGER_INTEGER_LOG2_HPP
#define BOOST_INTEGER_INTEGER_LOG2_HPP

#include <assert.h>
#ifdef __BORLANDC__
#include <climits>
#endif
#include <boost/limits.hpp>
#include <boost/config.hpp>


namespace boost {
 namespace detail {

  template <typename T>
  int integer_log2_impl(T x, int n) {

      int result = 0;

      while (x != 1) {

          const T t = static_cast<T>(x >> n);
          if (t) {
              result += n;
              x = t;
          }
          n /= 2;

      }

      return result;
  }



  // helper to find the maximum power of two
  // less than p (more involved than necessary,
  // to avoid PTS)
  //
  template <int p, int n>
  struct max_pow2_less {

      enum { c = 2*n < p };

      BOOST_STATIC_CONSTANT(int, value =
          c ? (max_pow2_less< c*p, 2*c*n>::value) : n);

  };

  template <>
  struct max_pow2_less<0, 0> {

      BOOST_STATIC_CONSTANT(int, value = 0);
  };

  // this template is here just for Borland :(
  // we could simply rely on numeric_limits but sometimes
  // Borland tries to use numeric_limits<const T>, because
  // of its usual const-related problems in argument deduction
  // - gps
  template <typename T>
  struct width {

#ifdef __BORLANDC__
      BOOST_STATIC_CONSTANT(int, value = sizeof(T) * CHAR_BIT);
#else
      BOOST_STATIC_CONSTANT(int, value = (std::numeric_limits<T>::digits));
#endif

  };

 } // detail


 // ---------
 // integer_log2
 // ---------------
 //
 template <typename T>
 int integer_log2(T x) {

     assert(x > 0);

     const int n = detail::max_pow2_less<
                     detail::width<T> :: value, 4
                   > :: value;

     return detail::integer_log2_impl(x, n);

 }



}



#endif // include guard

/* integer_log2.hpp
RjF/Byue8IzlfP7MXud5xhKx5Fk/SDdHvd/hP+g5YU//JALI04oEWBICrtzK+2sOH61PUELAMw/yNBOwzNINZJyFUbKCKKGFBGbF2zU7d3KWRMUGVsnzPI4WQZHFc7HbLNJY9NNtDkuE7mv203UkYJulAQ+LjMOW5cGai4rxmAVZ+t0VMCH4ZhGjBCjqgkPABAfBExHl0bNkTWIjVVLKrjBKrcKKHYe0yLdFDukSV7SYR+IdraFPU/RXst2GZXP+yoL8zRXp4qe3n20ruo3SSIGRGn3+yrV0g3S7y6LVOoeri8vv4Ay/ri5M+JCuE7REvFnwbKWXPvBsEwkRpQlZpBDcRMW3OxM2aRgt8RvtcZ5mEEYiz6JFkXOlrUiX+QtDZZf4kCU7wtoW2TZFe75E+RrwNn2jkWDJySaw5hlf7GCFPoCGNMlgz1HIydwsl1Zmi1RtQlApkKR5FHC9K2TlWt7y0XbLWUbOw+KYKCMuKq+4t8F3b6ePlmeD48OD5350hvYQDMvHawOsyVAusmbTe9eDoeMPRpYz9sEajQCpPGsydWyfsB6d6T149p3lIYmLVIhXY08Go9nQmdxJQmf8MHKQSw0A7i1hjG1vcI93rBtn5Ew/S/a3znRi+34fMWDigv3RnkzBvyechmQ3
*/