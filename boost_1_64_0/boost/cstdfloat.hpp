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
EvbM5uT1Yjh/S5FXea7U56w9BZXvF9OfBU582jFvtj0Th3mSF37Kju2CvCv/656L2zpLA7v5xvqxDQsnIzbMoky4NsgoDo/OwNm1x5yW1tfIUdw8Xo5iTjj7YEMS5ueYPkMlZyBZeP2bi85PsnGIeSznm+8siZI1vXo35u58Bd8Z8IidUDc8OTeF3EWj/XKM/lUATeTElIS30u8aJot9hJphORCoSk1duoO7gG1exTaptDY7PScbTb2WIcs8jzLAbwZWj3RpZam2XBsGwN7LGOscXcQVEvYumxgG8JI16ZGseXmYWFo8AG2PxBCUSl5vINR784JWLX8RVc6ahG68dbUKXCQqG6D60x5tLM8NJ1Ph6252+ZVCecC1UlA6VeB7kgPDe+Re1Mi/Dz0lAn5ZYXB+UvSrh8pSL6OUEZx7R8Foi68HYQB+GcBlPBn99x4Je3cYiRbpLCdSP9gPY30QvVElBqCE/tEtEvYywAJQoa9eTljoiTgvbRyFtpbmZd2k4Ly8EpyXV64KnZcY1Z86q5iXNo3n5Tcr5Lx8MU5CbbGa8zKI9MyYj5tWBOcjUp+cLKEftbYwH+NXmPNxv6oZuyt0Pk7OwxiLLMH5QAn97Zsl7Hhro/nYAtja2dzVudO1WXmwaZpkDmD7HLmBfqSacajJopmn3Zm6K88GMkxCFsTGxZdKUJoBSFRkxwqWHRL0PedaCEooyysQFXtse/VU1S2qtDE1yzbnDjTxBRNiA3SmhNZThkhQjow7qTJ12ealrO4aBXDoJgLkzi9YFrD4OpvDaKeGMXesyPaSlAuab6sHElgMDsFReM3X8khwFF6Gb9Xu/ZxkPJTsz3lkO3cxKlSZ/sIFp5hrkbnQgeGHPDN2AzJS7/ojKe4toKEvzywehprBmBiMCk6u/SYDI92lP7Y8lq+Rz9FfdYuuvuSftb/22Y3///v/3w/xB/+JM4TdlH7BFEPhHv+k6fOOaAoxIt4m54Li1JXHk6/hV5pE1iA80xYZXVtvB7WG8JrEawjiQh7Gh1MJZN7y+P+U8KG4wkAJAqV4cU6CFDqMhHEqZLGTUGNtv7QVgdv56xL+6ppWV52Ww5+T+bNtwYkeuV3xayp+gTsWHvNKWb3+6cV834itdmisINfSFOavd0rrxciBTJTNYzdFCoIgX9WtxOikMtYyRyhjOQ2zv5NX8G+Uz542vv8blxihRTI03Suk3fpGmBGLV5tyMEac/9/kSkHq9XyS8HaIPPreUUJVN0lFDHx8nnJ1zjniVQv256hOvCqv15+GelT5VGMMWNg3R+nDYT2EX3oxGmQN2+f8kOH9Q+TVnIo4Yyr+lBUSkNFLOwT6919GRNtNO8c0WiIieR7GRbMK3olUbHi8uQwYJapQAmlw8OBAAXbdUOJwBFnfYQRpU5Trg5RwYnmWsUdOPmbukXjkuIW43YsFnBMvF/AlF20cPhTMw9NWYRzMh8QLAMww+yfnEkx3r6i73eMsIY8sjHppVnvfbMWgo9QqnDUig7j8B2B6E9irBWze7po4q7z4DhacqbOuyprjwIRELJfbwJLUrGhFIu+44mKCFeAWXYJs53JE0bWH8GvZlcl12G3hPSHxGzB3lWO1dWQbX+TrYht1gPqjtRv/Cx/Za2n4yHa+1oE3PYH1hXvydlEiTjxlbmJhILe3IQ8sUYrmPUtlz7aPphrrkNX3SXKArIQx2NeQzoBIsWaJP6gSj45uNpa689VYfuwV72bFWAAs58NA+bcEwnsgYGA1vwbF4krsF6YccmVMl5tcU1KGTy8XlIGLL800Lq900/T16gD+qmt8/xKfpmfE12mGr445QpyTaTx+ydQ+9CrBiNcM5mjz+kc=
*/