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
ocEUO96uR9y5EfUMxxuP5kqESOG+PXD44Qtl562BuVi4LG4U6HbyFDUcFNf0FS5L0PultD4gw7f+7GYLLntwCWxeyQaKzmcKq6r8TK9XP14vtj9eX5A5fgAyNFBfzWvnXkXunTF0lKxqp8l3DcDeyrr3HfoVxIItGkflirzpCZp30n0oJfs2cuJ3xqPquYe+7q20f12bK7qSNAtI/XaRcTEZ6eIq4QSbF0q7arVZl6rG42R4lcm8DE2XjciK6hfefz4ksJQ/+IT965ZT1clag71Gq9kkYwL3OfTO1jOrh/5b58vQjXVqV/LxyKZHDVvhKxF9zbLcoO5waLV7twGO9rjfbH3iM70qmwyozTSzhML2GiGmXgQWkyY/mnh7Vi291hBomutNvLkQNqvOAlokUs+a1STvDPhPLR4EJvTevHRSGTsn267ZGpRuHYXrlfJW5b8yQK3kudQtrY1YnV9WWQ0oqxrkBb5Yx7NMhY9eQ/4MlBqZtD+4aZM1CUCWnVsqT3Kcegwjt7yXGyUMiR4olgWCfnUB4EVmI6DIghrqSKneKgwO63aVA5vaj5AmAfEZYgeLq0hTVWgpuY2sCNNViGP1Ok+mOKZyGKkI29PbJ3GmqZbaU5sCtwL+ybSo7BitW3pVrBOzhYsy9nVk+pZ2qI3RK5ffvFLy6s+EQpmbEy8nLx/rZX01XE/gAsoyBq7INbzS5ume0+Q9vwcV
*/