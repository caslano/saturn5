/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/integral_constant.hpp
 *
 * This header defines \c integral_constant wrapper
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/integral_constant.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
using boost::integral_constant;
using boost::true_type;
using boost::false_type;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

/* integral_constant.hpp
MvDddFJGfR//FUjPmtN9neemTdL7A5BFKHLPI0uURnWvgcVJNGPsy1Z6zmkLc25qA5yerjr9ws7DYD++fFC4juFNE/VVQiS/F0UMnZpNE8Rqc/yifk4/cYt7P0OZTq1sZtSUJONr5xJO1w2VxPcpRqHEPxziNg3/FB0O/kvQ7TYN5eJ/KFdGVQbzuC0plxXyzfMOdZUZTN6k8CvzMKcxD1f42nXBBklh5W55tI6hzPQuWEUZBBw85ivWV4zfWhqlxorQDBeJec0MM2aV7DI+XPAsAqqOi/b7NCddB4VwsxOVOT6IQtoaLLjHBLqnO5EfxJYYBFiG3jKypetd2pceveU+ho0OARhmsWyq4s494zkLtfaTw3d/kH/+66YH+GYq0qcJ5AWq6lPmrBbsi7nmGBiZpTBZ9YV31lTW9KGgabfDAUOJ92U/RK96MIk9IyctJ4KEEmYC9ruEcfLK6MqiDjTao/k3oYyh3Z/0XPmeSOEvWJa1rt3gBHCMZ0HdRlgJeb3u86uur6QHWtdl1+T6bpJxpDtj+hzdinVWcvdEcDW4YJDdqH7oVtlTbqOQCrlUF5P2U/8NtZQb9c2LCuFD4orFnT5RFl+NIUwYA6l8zdTFlCoNUYSXuKfCkN6QF/XOofBhQ2JL3tzFPMCz8+aL+rPZzfPGgMZ666CRrVizkAqNE6llJUsuZZnvdmpixXgRqKtz4wgad/C7yd2q
*/