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
1TFmSd3nZDYRH21jWYxpW4I6557w0pu9tENYOwGeMxD7tUJvfif6jKDG7bGt7ptkjYJTIpw7dfgx0YZumNFqq+9ITIYWzJ+SBfkA9nKuk7wZaTrKIw6YqFW3tx3uYv70zhKjh3wecI9Sr6Ne6rUWEQoqHZG+30i10fJ39TY5pBs20S8I4c6s7nXLQqEWkrxTATwHVXfP+rhjXLfkXn/k0Xw7X23agH9wnhx7Ozxb9cR6xPp+DGSQGPf48kuWenIO6MUNze4M9M3JiikNBSNiEgnZMQPQFiHTPYT/YKyP9mdjUfl82OIAoZRnq9jI1g2uuDHfVkXIG+XC/UbZHE8R9c7oAPxDwvoT5aCBpBOvX1f3Q9A629jm2ioEwYLEHZOBnEloWkhhBwC51+0RX4wuEYOLrArmLCJhundSz2tb3FyFqNo+3Mjz+83iZ2lOnBHiSLyW9ruBR9dhwl+x977Xo4MAGOun+E5f46LzlvxE1YmMV+4BTq8I0AaOucY8nVkI2IyqQyYrOoVMCXAoLieXxMKXDTECcKC5gs+NZATx3yd0l/Y3MvzOvl9upzLG2tylFsSkBu4jp/3SvBDoSIIwuMvUCchJ5+QWJYJQTPE7TamXymMWqu5lel3lLJSdNSv1AAZXNJs9D80EOBkMBhtVnx/Jti42CvWSU58QA57V4q1Uqo7FoXMyiYaiS72BgUGG+L6Zs9+DBb7/mQQd
*/