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
g20vZ7j73pZJmyIZRe4jpD+MycPvELMDiSzO/2+qL+5HWCd1U6S8rUVrS4vtZaD99iKMRLH/n+MYyhsPhE1LhuT6az99lkj4/BHmg0yKN0yZG72/yXAJMvKEkCis/Q2eAAxDa2ME1kbdXHioJU2u8xtJKi2/QBV5C3OWi0ooXmue0hSL1DKVfglVty3stuBbu9rbl7AxrrIEOi45efykkL4uYYJsS0euPZ0XL98hZ3SbHMRI1q1p6UjBHPSxrfQ=
*/