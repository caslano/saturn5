/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_CLANG_HPP

#if __has_builtin(__builtin_assume_aligned)
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))
#else
#define BOOST_ALIGN_ASSUME_ALIGNED(p, n)
#endif

#endif

/* assume_aligned_clang.hpp
LqW3heohhCF/sn53uSaCcrifkRcvZYzrv3GcZh1Jxk2366isOorUdadMtdgm8p6+CumwxHSckhoT8FxVSA2zFc85ORXURLumXK7dGss7i2QRuLx81aXZeM/Qb5X5XHzrRgdN0eJ33CpZB1y3yrgas2o9bXpiHYNEGNgwF3YJFvbVsDqBlwkdhEL88jvsfnt9+v0lR2mTvqnwPvKM/7pQchKSWNn1x5Pybp1pKXDk2la+Kj/D
*/