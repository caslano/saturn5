//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP
#define BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP

#include <array>
#include <boost/gil/extension/numeric/kernel.hpp>

namespace boost { namespace gil { namespace detail {

static constexpr double pi = 3.14159265358979323846;

static constexpr std::array<float, 9> dx_sobel = {{-1, 0, 1, -2, 0, 2, -1, 0, 1}};
static constexpr std::array<float, 9> dx_scharr = {{-1, 0, 1, -1, 0, 1, -1, 0, 1}};
static constexpr std::array<float, 9> dy_sobel = {{1, 2, 1, 0, 0, 0, -1, -2, -1}};
static constexpr std::array<float, 9> dy_scharr = {{1, 1, 1, 0, 0, 0, -1, -1, -1}};

template <typename T, typename Allocator>
inline detail::kernel_2d<T, Allocator> get_identity_kernel()
{
    detail::kernel_2d<T, Allocator> kernel(1, 0, 0);
    kernel[0] = 1;
    return kernel;
}

}}} // namespace boost::gil::detail

#endif

/* math.hpp
9N0hqaYzw+BRqYTj6erEkvS31X7Ush1DDU4yzWNQn7SXaR4XgFTdwTSPZlRUpzPNo2+XmbFcAEyqHTdGNBOUysg8cpTkNp8CBFwJNT91tRhAqCkp5vwwE5Q2P8WcNwwIBf2BZ8uanz37Ft20xZayVTXSzlRhSTSxYd9UDkx7NRL15n1smwvI9yENSCzfz8TvOI5lPSN6Kl3l5UHyk/5AFJWmqDNYmmpzwjWmqD8+1rimdHdI
*/