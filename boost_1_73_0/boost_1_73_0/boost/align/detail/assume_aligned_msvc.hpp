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
qZOmN2OGnc8LYjDnvAX1MnyakwTvPmiaTZ83f+ew1pZf8NyWs6CCwvu5qY4M8C6vH5YKxXxibuKz1jPy
*/