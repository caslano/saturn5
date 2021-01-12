/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP

#include <cstddef>

#define BOOST_ALIGN_ASSUME_ALIGNED(ptr, alignment) \
__assume((reinterpret_cast<std::size_t>(ptr) & ((alignment) - 1)) == 0)

#endif

/* assume_aligned_msvc.hpp
qMwxtFh4ggJ+zOmgh0/SG8xKATQ0wgolHIXNip9sYXueYJXzAU97xVNwD1O6z7jlhhQPZ8dqGfSVCDCuvUF1OHWq5iFOV52mH6lrB7Oe4ueguaAvbSWHjshfIRyhEWPQWz4Bu63gAiuTlZFPqgbfg0JJsmfFbJEL3FoINvCZZPHljsTSZJ/7lCnFEYfrPUoZIMS0S3QW6YNmfkceT+WHYOaXgWu3iFfSu1EOx0lK67n0CG+J
*/