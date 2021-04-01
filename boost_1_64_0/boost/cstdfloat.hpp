///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// <boost/cstdfloat.hpp> implements floating-point typedefs having
// specified widths, as described in N3626 (proposed for C++14).
// See: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3626.pdf

#ifndef BOOST_MATH_CSTDFLOAT_2014_01_09_HPP_
  #define BOOST_MATH_CSTDFLOAT_2014_01_09_HPP_

  // Include the floating-point type definitions.
  #include <boost/math/cstdfloat/cstdfloat_types.hpp>

  // Support a specialization of std::numeric_limits<> for the wrapped quadmath library (if available).
  #if !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_LIMITS)
    #include <boost/math/cstdfloat/cstdfloat_limits.hpp>
  #endif

  // Support <cmath> functions for the wrapped quadmath library (if available).
  #if !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH)
    #include <boost/math/cstdfloat/cstdfloat_cmath.hpp>
  #endif

  // Support I/O stream operations for the wrapped quadmath library (if available).
  #if !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_IOSTREAM)
    #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH)
    #error You can not use <boost/math/cstdfloat/cstdfloat_iostream.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH defined.
    #endif
    #include <boost/math/cstdfloat/cstdfloat_iostream.hpp>
  #endif

  // Support a specialization of std::complex<> for the wrapped quadmath library (if available).
  #if !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_COMPLEX)
    #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_LIMITS)
    #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_LIMITS defined.
    #endif
    #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH)
    #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH defined.
    #endif
    #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_IOSTREAM)
    #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_IOSTREAM defined.
    #endif
    #include <boost/math/cstdfloat/cstdfloat_complex.hpp>
  #endif


  // Undefine BOOST_NO_FLOAT128_T because this constant is not meant for public use.
  #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T)
  #undef BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T
  #endif

#endif // BOOST_MATH_CSTDFLOAT_2014_01_09_HPP_

/* cstdfloat.hpp
zLyJVzTQBSozHmAfuaykkDQrwBeSb8e77X/0v+1XhBcd0ZlvXuAT0zYCa5ztJSScoMvvQn/7wmGDX+q4GPpev4iy3sWtxxbP7HnyqQRVzDMiFJt0TwowAzxNlrldddg6cBR7QuzbHnCFdNc7VPYopCAHZ7JnEHvSvwH+uF+QcFn3xbsus9hKOOnhobtVNrhjvKhjWEYLCH+Sf6oH4aIcBY8lgKde4M5iOTFDm0TCl03XVB1VWXRQxfP4M61HcLnr9676okDoaW6gIZMwvUyWhwkqcvDCKkSv9IKbHONo+ESabqQ9ScypwJAl1g7smfi2kjUDAhjCRzdPdwzIkR2l97RmfbbqcvQxQKNjNac4idBEBmxKnBRP0/mrbSu8GFsVvDfuXAkVrOlxMitiMdehTRMEnhiD+MyPgY8tKzcaGjxYKRj/d3ZbUssoUqk3ItbJTjVb8rJmW2TBMN4KmQynCP3Edi9MSkky0qcq5gSzVYvG/0JLo2iuyJw4iHXCo5Q1eTPudZYSs3kPXGFkAssT2MTYwM9JtUFyoFVJVgUt5nngNEZDzxqf2Bxxhg==
*/