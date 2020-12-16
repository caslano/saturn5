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
yoPoAqYE7lvpAYrsjfI8+4BDwL7KUxygPMWBYCl4jvIiBoOzwDPBeep+pvIsFyjP8iJwhPIYR4LXgAfrfR+jwDuVR3mv3o/zIDhaeY1Hgk/pvS4v6r0um8FjwNfA48Adyrv8Ur+/C5wIZpLRU5TnOAksBCfr/SClYG9wOjgY/DF4kPIqD1Fe5QRwlt4TMhssBeeAZyj9mWAVuBCcC14MzgOvUN7mT5W3uR48R+unu6vrOl3HTtZ3iQq0flZpvV6n97XcqPX7U+VRrwH3AZ8He4A/Ux7SLcqzvgccpDztEvBecBj4S3CE8rJHgr8Cj1Ce9tHKyx4H3g0eB/5ceU6/AWeDv9X6fA48X79/AfiI8pAfBS9V98vAx8Cr1H618rrWgE+DGzWe36j/g8rjelLdn1V35eXr+oS81OflC2+4OXi+5vsifVt5ieb7YvAY8BJwMnip5udiTf/l4DJwObgKXKm87xXKC1tpeF46F+ockNaInn5tgnRbvoFu6W7w0P6X+GZ7ml/WMK8scT6ZcyInJJjhmDLMUsx6TC1mx4lNPLKmX9Ov6df0a/o1/Zp+Tb+m3/f/+8H4/+UzS/cU///agP7/RD0sLYoSi+LCAjCpPv9/er+y8Dm4eVt1sNA3i+ZwGjaFryzAPInZivkXZgivkd3F+6rbIin29+OTYmdtX7SJf4ciCzwmRd4+MOfavxX7ZPi2rWznccTX+NumxeKfGS2kFH/M7u4CzK8o1PfAFPjbB2J+GUnjXC3Z6cbRcYYfJyXk8Y8uxawl7L3OSM6h0qF/1PColTZ0dlh16mlglt7vn5Ms+ua8Bltu8rggucE3gYkv/FbDqaUzTq2slHNXfd9zntA8GemnZTRH7M9EupHOYZjLMGtpKY+C/8Kc4lY4nSMTnIWR/kbXty5dF7tRSuNx5wHb2wnhvPHjqvupMd7TIRJHhtrRJBY7upv67uWwuvDRIL8hX8P+Wfzu5HudOY8aw92zaaZ8Nkmd55s3GvYWezv9jp/2CBTQ89dV4n853K5xfCHqzKfOspT/Viu05+F3msgc7Iyrk1nu0266uH9m3F9Cv/tW51x3jNaB8rFnlM/kD6HdFRfH/hJHWCagk+ZlpORzV2QsaZqOqeY0bDuY6r7s5mj6nxKaVdTUSLgz/aw63v183pLQtox2oDdNx5yPeRbzLiYZuYoRmF+hV/8BJszfV3kIDhulTDi37ksfpqw0rQ9JnpZzDjrKyBS4qbjhkgGdll+gnO5wznLHafkFy6RSyzVQfqWzZlZRhkHe57lCf6+TRC8r1L63UvK3POKVaBe+uoxecZuzdyAvpdPIjeFbbRP6vRqVH/igrswalR94X9LSKlDnsH0C6W0D/ktoPuQ+7N+EZRzMePWK0KS55c7N6qbtlV5GX2s0DfdKvWTVl5/QuNeIf3u1a7zEeiC8iFb4X+fxd2MyD2K/AbMgYO+WT3/CBN1u7JL427BdUmP8X/p7Pf7v0Jhbse9WlFxfh//+pPpyET9Nqq8fe25S4rqwzCdx73ZkhPnHwTf5dJzOwS3bdwuMtflBXnOw/arO6KNJ8fISrZPj7b3VXqLyFbeG/NNTfXu87Npila/I9XkLmCOwZKbFz9MySVtk16x65mnWOdc2n0JrnU/tuuBp8bywn35HObfG6y+et7+huSO/fI28nZZTcbicvCnLK6wEy6p4N8qqeDfKqvg/UFb9fB6v8k3L3BhuHApPKy0mByHLvtL68g89/DWL0O7v9mXddAy5n8hsdSnmduy/w+x02tvvEgqUUVGSF28piY7NAROayVoIe3qgbE24QLkzLkv4ChG8aaicx9rrxNwlMF78J7vtSd1v4dS9hOHtfn0=
*/