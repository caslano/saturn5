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
n1q4Pl8Ag6LbLJU1y6rqgXhZPnXZCNcuUxywiv9wCrfoUJStW1AUyrnORyG4SqoHPM4LjcRCCtUCHIpEeqHxeNw5Qke0kOQoINlr6nm7EW+pedwfBZY2gHFQCq1ehpufuvrKhsqa8kqa9vclXjuFdOOUyUaFgxqUFsbfZGkrKUozgnNGi1nFjZEKkpcUKN1Xt7yhtBZ4+0rr6gDHxSXLpiLUiyQCq7toLfmWiy8dNDR0+fPYf1AmV7+H6AIkjMA=
*/