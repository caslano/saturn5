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
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
*/