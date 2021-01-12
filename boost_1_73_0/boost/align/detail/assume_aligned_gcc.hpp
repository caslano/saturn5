/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))

#endif

/* assume_aligned_gcc.hpp
uo6Kbb3SxWvS8lVj4UkLPYjx2TqLV6ND8Ed9ZHnbVbxxuNsh8c+UyRe4txoFlgvHDTVwDI68d6b1PQuO1cIL2SaCislfbuDvHg7itvv4IntYEHApe2fG6yC3c2lweOXzm79xKmPfyrTu4WdkWpSgub8QDOqeDGtO5EJ06HcokFK0UgcduYq67gxf1Cy1H1/vsrlOzxazC59YeDxpcpqa6x9oTZvmCq1J2rW3L1Mjv9kG9gDC
*/