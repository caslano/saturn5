///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement quadruple-precision (and extended) support for <complex>.

#ifndef BOOST_MATH_CSTDFLOAT_COMPLEX_2014_02_15_HPP_
  #define BOOST_MATH_CSTDFLOAT_COMPLEX_2014_02_15_HPP_

  #include <boost/math/cstdfloat/cstdfloat_types.hpp>
  #include <boost/math/cstdfloat/cstdfloat_limits.hpp>
  #include <boost/math/cstdfloat/cstdfloat_cmath.hpp>
  #include <boost/math/cstdfloat/cstdfloat_iostream.hpp>

  #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_LIMITS)
  #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_LIMITS defined.
  #endif
  #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH)
  #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_CMATH defined.
  #endif
  #if defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_IOSTREAM)
  #error You can not use <boost/math/cstdfloat/cstdfloat_complex.hpp> with BOOST_CSTDFLOAT_NO_LIBQUADMATH_IOSTREAM defined.
  #endif

  #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

  #define BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE boost::math::cstdfloat::detail::float_internal128_t
  #include <boost/math/cstdfloat/cstdfloat_complex_std.hpp>
  #undef BOOST_CSTDFLOAT_EXTENDED_COMPLEX_FLOAT_TYPE

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_COMPLEX_2014_02_15_HPP_

/* cstdfloat_complex.hpp
28RVTeMZtCFsRaViDLcN6E0YvKz2GOjiQ5nQ9kPtQplOqZuxfWMulYkLqjIFzWeGKVonS3sToAzVthBtOhMJcAVHeqq3dR42HUd4k8WUfsy9Af3DWuNpI+r9p9tsDiUx/tRM6dX00bCXk8NNnlzrpq7v/K2hRjZlsdxfMw/zaaEbRmuezCFGG4XiBc1B4kVehwxGoXhgOadpon9EsJ/RuXr93GuGJsJNUDoVqqdpggh883TpIPnhMlWlHVAd2F/uFxbJa9LNqsd591pI7lEliHQjshKsbLWyUnRvmWDmPh/rPBQnNjODYyFv69FUoRxVKgGI/entJ/FOdTZPx+d60M5z3R21h9PQg081tkfxQ5Kal/cFlgfJ42+1h6BsbA/Glqw5o5zsuQDTiDnRHOVj9thkmi4zsMIx9aUQE+witk3VP2Yuc+e54JxoTPT4vBLRmXhHA7+uHskEqp24MmdRNgzOhIEdOWFVP08ejWv4syb738nOTeIOstH9iGaocAELfZkDocm6my5RRjIBwU5zA/7rUzSK6WEdfEyuTGLgehFKmm/6NicdDn+pnCsprOJyFz0R/0JMwWPk20Fqj1NN39gsmmND+4ykYnqOb+rq2F+aaKZshyWZ82+6nnpuunYU2N9djdAweCLGNt9AxnKyaKAbOoc8SJKrnBSEbNSsv5zPuIK4uKMVe0qY6K5xODIASy95/DbaaPCmKfWp
*/