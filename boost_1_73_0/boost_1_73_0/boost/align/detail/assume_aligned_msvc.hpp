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
GKcWkgVMg3YblozY+6mxgK1JDQmCGJCRLpn4vgdaB4Km3rtYXkYFPMglpkG38HB1mSYLgEV+aSV1gO8oWP1RRKor/d7aCuqzLS67AsEFk+drk9Rfv7TBb7Ybtxr0va5u+XocbB+OFVo+DTAhAn5qUb6aoxVVi6CpZI1shV7Gb6mIN4zI7CgN47VylUq1qoYSdYzr9koQoPINJVe+qiFYP6/U3/WVy2qXgK7A+nkNmTVW+ijDlT5aWBDgO4eSTL4=
*/