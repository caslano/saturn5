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
LCe8m+MkrYVhxrV3NFlTZs9PxD5DDGQtYR7fBT5F63KYcV0eTpaL2Y18xa+iPsl6wTzW7KdZOT3X7GQNYR5r9tPey+k8Q+tymMea/ax3iyfD8TzX7Oe8Hy+GbCvMuC6PPk/nB5hx7Z1IhnbwWHs7L9DaG2Zce8eR9YYZ197Oi7S+hhnX17FkWWAe766STYAZ19fhl4z1su+HjRi3CWTPmD3avFvfw/SyTdsXALZ1xUnc0wn5ldWnx5o9gawds3e+mWxGfFdsagMvy+MD+n6OV5PnOljBkcMao66vYT1IZlwPBly3qbRm3Q7EryiKernJ+rXn2o2sMMxj7XaL1i8wj7WbYDFkpWDu9Qt+8/Z6PDo5eU/nJPN2vGgyb3nGCXkmCekcd7ynCyE7mFe3EdOux6I+M9rVwSy6nY4/Xkv/LcSurcthjorOhoiPtgJty9p998nI9ShnEbuqz2xojmmT9bWpXaVhNmh/maooS3G7ojtRsCsFdobqvzHYtfUELPDXrvWRZ1m7+ojlOf7HT3/AOPK3KxeL4UyL+11wPLIVzJYsOq4/t1berpYy612sf2scL8BuaIfCJevp75KSZYAZ3wFIIFuZUbfj5n56uzvtqi+zO9kGfYi6pimY/iJs5M09MbCWdnWPWcZZQXsReyu7+pJZmSVpTUj3gV3bEx2257spvRFfa7sKZpZuTvOBGEdt7aoCs2V1XRbE1476C7O95Q99gvg62BX9FARbHxOu95cudnWelbNo85q9MKZD7IZ51zRrXhT6J1kYsybjM/bHeOhmV22YjYucNQ7xkUUyu1W7ZFqk625XU1kM0yaPqo6yhFKezObkffcs2j3MrpaxPMOCHfp1f0+7CmI2Nff5kuiDZHtYnrmHPMyIsvQx9sHboYWTUGdkfzILnFlW/w2sn119w/IcdT92N9pvgF0VYONoysiXOP+pcBor6XRbNG1CA/17yXa1m+XZ/92RzVCWj+2qA8tz/NyxcxAffSDwJktXvNNX0SjLJ3aVwMdm0c1Y14WMs6vtzJqPflgO6cbbDecx69WH09AOZHaY8Xv6CWRh3MrW+BfynGBXrZllbfl+WuRJVotZqxvx+n6HE+30mynrg7mqoE84JtvVFJauzdhy+r5GZMVZus5TduJ+nXOqx/EKToxBXyLbyup627OGQfqeqXaVneXZYXwNfW/lGJrnWZ4FfvtiK+yfdu23LNiHG8NRn67P7Go9S1dsf6hD/83NrtKaeHwhG/R9Su1qErM/FxZthXlpjl3FmdlcMG9+fdTLPLv2mzDshwyZ9bluobEs64p/8UB/Rt6u7rI8F/a6twB5LrZrW0nA4l8Vvo5+/ZVd7eftfrXnx7DlNG5tbE0UWewcyrLGbljzLSt4Kx7zElnq2q2YxxparaW+C/O4B0/WAGZctyaQNYUZ160B6+xYYxbzWGO6yKrDjGuwWLLfmBVYsHUWjhdnV9NNujV894eXsG/tqhOzsa42GLcxG+3quVm3ZhFRB1GWLXZ1zH08bXFy1H4V9RlCj1sfNulmu/79ALTDdrvKzexarRqbMP7+ZVcVWZ6D6j55juORBXDr8IW+DvFIt+p+mVWIj6wCs7HWuzlxvJ2GdHS9kgPt4CLjx/uoVf0cOJ6HVTkzsguOR8Zj3zw8r77n7S67qmyD0fcml5ZCvfxExvJc3WSWDf1sn9F22NZ+hnJ62JCi9+eiT3jYhbjvmmOeJytj1q2H6joIZTlg135zg/1WNJ/+DDk99LuT2XdlPo/EODqM8UDm8QwWWX12vPn9Oul70x9NXvPBJp5Yhvkz/DjNg8yazsuPZ7r3nUg9PzhC6iv8k2yHBDsu2FnBEgW7LthdwR4=
*/