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
7qvMsMi5jAfhhvh7etQ9IwPI8BV7U88TGnYCCs/TurHwZDnQkEewDzYBcqoml5wTpDT1AqCpNaCpVbRwD6OpP7fx8cnC85EKyY/p+IT+MjU+Tmwdn4V2+RfCdtQNTHV8dlq9Epu+ZWmNiu4kcO/GlCBP64kutwkchMfSNoEPQeFpSEQvsBV+kSA+QVrDeOeRFzMRjIhVzm67PICFbpxI1zGD3OScuV0XoTDXzsbrEraO+0IsHccNjEebQbcdts+3yq9ughvSGXgjPutZvkbzO/dAYTWv+167te5PgRmqZh4OZuIPd5rhPAWFn3I4E9Pg3ISlX0CLCtM8kNU3yqfwOOWBbMJ8JEMyhPkpH9PsbIBDsE7i++xKFhaGmHcUITTLmigXTPPyDijUC2xeEhmXdBvx3eAU0mfWLrepGxJ4u+52Af8LhSf4+5unNedaUd4n3CPgUlQpRGaW4Z4xw3oXCr/lsD6aBmuJqP4/9t4HPKri3v+fPdlsNkuyWUIIIYa4IGJEwAUDBkTYQAKBAq4QIFKUJGQhwZBsk/CvpTZatOhFGylatEhXqxYt2i1Vi4p2tWjRi3aL2mKLdrVqqaXe1WKLvVJ/75nznt2zIfRW/d3vvd/n+e7zzL7mM2dmPnPmzJn/55zd9o8MDPXqEd8MFV8fY/myTEvey+egxsPBuRtBOHbta/xvDfPhDIz/ZZgnVZiRpwnTYw2z+kSu
*/