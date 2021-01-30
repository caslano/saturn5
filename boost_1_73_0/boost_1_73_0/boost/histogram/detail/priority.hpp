// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP
#define BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP

#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

// priority is used to priorise ambiguous overloads

template <std::size_t N>
struct priority : priority<(N - 1)> {};

template <>
struct priority<0> {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* priority.hpp
ZcLgN6eCes/n9LaplcninWqpMRUpAzI8dwUHJ6cs756SFYAwBeOQhB5XRpSvp1hUk8TVEyLYz65QjqyW
*/