//  (C) Copyright Eric Jourdanneau, Joel Falcou 2010
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  NVIDIA CUDA C++ compiler setup

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "NVIDIA CUDA C++ Compiler"
#endif

#if defined(__CUDACC_VER_MAJOR__) && defined(__CUDACC_VER_MINOR__) && defined(__CUDACC_VER_BUILD__)
#  define BOOST_CUDA_VERSION (__CUDACC_VER_MAJOR__ * 1000000 + __CUDACC_VER_MINOR__ * 10000 + __CUDACC_VER_BUILD__)
#else
// We don't really know what the CUDA version is, but it's definitely before 7.5:
#  define BOOST_CUDA_VERSION 7000000
#endif

// NVIDIA Specific support
// BOOST_GPU_ENABLED : Flag a function or a method as being enabled on the host and device
#define BOOST_GPU_ENABLED __host__ __device__

// A bug in version 7.0 of CUDA prevents use of variadic templates in some occasions
// https://svn.boost.org/trac/boost/ticket/11897
// This is fixed in 7.5. As the following version macro was introduced in 7.5 an existance
// check is enough to detect versions < 7.5
#if BOOST_CUDA_VERSION < 7050000
#   define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif
// The same bug is back again in 8.0:
#if (BOOST_CUDA_VERSION > 8000000) && (BOOST_CUDA_VERSION < 8010000)
#   define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif
// CUDA (8.0) has no constexpr support in msvc mode:
#if defined(_MSC_VER) && (BOOST_CUDA_VERSION < 9000000)
#  define BOOST_NO_CXX11_CONSTEXPR
#endif

#ifdef __CUDACC__
//
// When compiing .cu files, there's a bunch of stuff that doesn't work with msvc:
//
#if defined(_MSC_VER)
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#endif
//
// And this one effects the NVCC front end,
// See https://svn.boost.org/trac/boost/ticket/13049
//
#if (BOOST_CUDA_VERSION >= 8000000) && (BOOST_CUDA_VERSION < 8010000)
#  define BOOST_NO_CXX11_NOEXCEPT
#endif

#endif


/* nvcc.hpp
gOthEhc2UU4Rx5jx+vfmt3mdsjw3NqmCWlTPBvP2kkRnYrgeY3WC8mWF1UUtEyomgjKTkuVTxiVs2hXI7Nl2JyTLJ8nTUsZxI+O1He5reT5VaXObxqaWucjrg+2dUJmZOJSqUGEu1rc2r7L9HH5HJdfZsojKJM4C4T299dcofV4fnegUvKILdnLk2Rpdl1zPi6oIlDKxGHE5yXXiBpODE9vKprnSYqz7V97uP5Pe/iUqiyxPOtFuYfJJ1EHJv/OVzNOsNKUY51LR+84/yWSlAGsi1wlS+G4zvbaZUFxOZUVZapMJz2WsL3dceWsvk6swjFLhmfG3/YfvrhR/zxjqVIP5S2fd732PvfKlNoltGIXCf57urX0v83yiLCkzVWQC5t3TpzqVbPmrnF9WsoirJBDNPI18nAMV143UysiWthC1HbG6mMPSccq1w0NbH+stc924obhuJEmmg6iqRdFX9lDkY2j76LWDToI0MyoT10Co9olemz010xqOs8f89otKp/kqRDlcN3K5Jzy5MCnLWGYZl8Ny4lz4FK9blKeVlkFe1w29z3lrmgnNZGSqparSWLgWhME8jScfdG+qvXMFnReBNMnQ4850PR04S7Dt7XakkPdM92v/PXYmddLsWernuOMTwLlOM5ucwmppy0I4Z4ZMYIB7U+3ZMLtyVlGVicWFZazd9KobMuj6G9+M9ZlsJsKysDDUxOJGv1lP1SZen9jegr8yR8l4V0XTOFsVuXFKptzKzPHXFvmb4RvaO+c1UoehVaKJMTY+N96+T3tpFIHJokzW1pP1CJ/e3HL/A6N2zUVoHLTjA+eWkOuD0kVqs1zA2ofkj2+VW7kZKmeFlaXVsQrEcq8PlnC9a0u93nJvGeWiRs5SOaVEnpioKGPRHKu6x9rLdTSLNl5jXXrw27C1vdMj+7SHQ74uKkJZur4OxFAppt3GY6fusB18I4dxCh9jsoWIqrgsosS2soNWdmmtvwqmfPUrmsFI2z8Zct3O4yzVUaWF26f1loZJQC824d5aedwbT0beOVgVyDQNJZdHrWW6c4LJpiJWRZQWUQCybqGxttNqDLzOH2ws7Cyh7gh8Z8vSKOuJO4qDkqThPvJNH9RWP9u7Sztdp+LeKmI6pHIVRDIPGkcukP9gZO94zat7rpMgSK1xQtugB+4uCOKcQKCThe2r+ExyWbZztFd/a+JAhrEWa27tfnVhvQ4v2Q7ala1t1wIj52aPR/57Zm2iLE27NJqB2Nhh4jlM5NnFhkmpUk3klladxrim2m6V5gLuhyI2bgpdJIm0GYr6ZUW/6jG//zBhEAdV0cmt9tqDQYH785jrZ+JGd1CYoBNa26Ad7e9ZROytO2SkqyAyKM81G+2tLzO5RGRFlWQ6JPluuv+r73im6zu9Zs+IuuHJw+1cZWImPwA9nGZrUIHf/Ji/kwlVFusg78ThNrOJkYC2rzHvU2USm+sq4UKsvAF+92N+B1HEMkh0hKJsABN/IU94/ZOmqrJZUBDB2tM//G1h85Mj4/fp2POpoMoq0YXy5QfuLzAN7fRgTDXHSWQ9eyLx7kNkHFc2IuXoD5cHzTkMnu0lvM2ywhRFKUmbQf/0lknpce6znmwkTRDKLCayaxuoH1y/VhPeblqmQVjEZSf7qd62mzma9+xtu23I9tuReHdVVVrayKaiUedmxnNBatbWvAG5E7X6wtLIXZvZuCwTi2nQyQvScH8n31H0r/F4wufgIrBRpW0k2ojK04swPNuZDCY1mNlX2gKh/xGvTjrOgqrKApIOLmJwLeHPMYafe1upSyVNl4T7SK95a8MTxjvXSCKljE07IXhn2nzNvblwxnhnSjLPSptLIuveFqw=
*/