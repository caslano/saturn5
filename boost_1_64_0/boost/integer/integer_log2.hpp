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
Y4cTrcgv6fsfBTivekIVJ/WBmslNwOR/s1idr5qnmjoihpGWxkn8yJLX39X7awZsuRmHV+uazPNgdjeDM30z4o7STeDzKcxjxKbDvwy13s6Wqwgv2NjUjDxUVSt2nuVllbYaOjo4PVyBQM9wTKkSZsmRA/jKevJ+18IvnEykisvQck+b/p0R3eAA+OEf3hBfTEZ/Pthm9hgDH/CLw6qb3tw49lMc9KjdV0L2g7Yi56D/TZSpDt8PbLmJ4YaSKdVzyeZjLeMvL6PPIhxcfkYr/X2MKh6BDJV750yJ35DBmq9TnowL2b1QVSz61Euycx2/ho64MiZGZgQYUSKJxDTzBXCPlEUw4f53dm2bL6Tlo4Gn6klCBCSoXOb0DpTEjlKGhJbiu8HEC3kPMmf6Ega71tlRcr0rPZGY2X4rflHnKThlQ+jtyQ3CRd/kZVGzZjkHwxMAD1fp2JpUdYzb+QjHGwTIvdQA3kfymWzd5y5OVtx2URVoeD5TF6/s4yMcKfs/hnC/tEWcyf2bvGS1O5uMNA4BwQa3r+6A8+ZiwZf+OXRN6Ll75o6fNSQFBQ==
*/