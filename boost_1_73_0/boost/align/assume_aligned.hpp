/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ASSUME_ALIGNED_HPP
#define BOOST_ALIGN_ASSUME_ALIGNED_HPP

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#include <boost/align/detail/assume_aligned_msvc.hpp>
#elif defined(BOOST_CLANG) && defined(__has_builtin)
#include <boost/align/detail/assume_aligned_clang.hpp>
#elif BOOST_GCC_VERSION >= 40700
#include <boost/align/detail/assume_aligned_gcc.hpp>
#elif defined(__INTEL_COMPILER)
#include <boost/align/detail/assume_aligned_intel.hpp>
#else
#include <boost/align/detail/assume_aligned.hpp>
#endif

#endif

/* assume_aligned.hpp
cWIa2W7GgcNj99NaQAL2S8Bocb0uLh6bDbhCT+uiwmVexCKsnK6KfCjTtu30/fXcO23DTlQRVHoQsONF39cpwSZ1+3juUwgyTNXJ35f5MqbjoN6HXpjon7Gr9HB0S16GaS4h0bUb1Ux8fS9+YQBgy6kSEIlEt5xBx8KKh0JZeF+ryvIRytI3zac19lX7NGOMKk5024uILLG37aHj1Oi2N3J4DCnUpINe50fHyRoLjPMWpOay
*/