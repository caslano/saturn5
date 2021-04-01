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
Yw+PIx44fExhforSttA2N5cAxOGFZZCyxInMFmNSHLGDDPyVf0CacpXdMYO49O7STi8nymfj+8z7xMr/XVD9VC0szzUdpJ1wrKKKsroHoKgeLRYUE1WnevFx78wJqT4DimXuQib1tXj68LlnQ3qwlSxa+084CxcllomM4qSudjZHrDlaozACb+kFt/u6lV9Y8l79n+54Jc4Csu7j9GAOvpbm8kn1mwy0ogkNfIqcVjK9coMw7Zsr7yXH5JUt48RUakwjBsFU/DIC/CQ+e7+niGyuH88yQyufuXDpjsjJl8OngzXtox54mlvh+C87SL1/BgwDMm1hHVN71Uhi/Y359VNI3CIWf3rGdoDcyIDNfTsGWPs7bEg0xT3VHmnM4B1JbKitO3Xbk6NmaSZKk9sQX6dS8EvIensS5s37m4kn9GP685agM2K11abU1NuL1yMwbIjYVqAB4FFxBDpXfp5G3Vcuhu6bI8amRTIixFl4hGwHx8ltPWUP06zyukbELjvIa6Hxr7euSbQAce4h+5Wp+OjUyoy/1Nzpygknl98fofaR28X367krXjGILA==
*/