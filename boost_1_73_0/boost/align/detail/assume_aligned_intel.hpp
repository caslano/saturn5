/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_INTEL_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_INTEL_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(ptr, alignment) \
__assume_aligned((ptr), (alignment))

#endif

/* assume_aligned_intel.hpp
7kqFpfT1rBahSDJ/ersxqIfclwuHEe/DAsaGIHI3b/UDLZqEGOu/wgKQt97Sb6K3WWcqsIDge+DlRpeD8gy2vJA6npGhZmpot9A/NWPUCnyZFlIz589LTB93dW/yIg7Xm25VJOl7ZAqo09n4yFh9lZ0PFBhb9jCU/H4ob7VM2oM3qhHoMkeg2OKiEprHNEtD+hwU2Bv3gcUp+mhRNkkBelu73OxUR7vVgf6T0W51oC8yQfS2
*/