/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/conditional.hpp
 *
 * This header defines \c conditional type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/conditional.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::conditional;
#else
using boost::conditional;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

/* conditional.hpp
51QcUxlca2oJ+g2AkbpONAj3CxJU1Oq76Mj8YH2nqGw3SdzDebO/mbkGpDd7kyxw69yEp5q1nxvE/zPmkUINrvPYsme6ZD8W/wKH7M61sMW6d3+ByjgGN9+uUxtUxrlTqcYF07nflGv+vawBY3hZOCffsU6s8TPFFiXTPm50MacoPyKbidfJyLZb/MNENtcatNHhPyTO8VZP1WG2yae9w+amqDhyntbwGwnvIv4iEz/V7PdyK+f5PrnhdbNU1Sdyo786uUWvRs/IGLCngql7Us8oo6uOJTfz139enf6ljk2bXl42Z8aMqNcgz3UNUsw10MTmOhDXdR0WxHAdzve5DnkNXId5ruuQ53MdbtmL65Ba7zqonHt4LTbptwb6U8402A3a16L69frXYvrcWXq9A6+FpjnOShU/mn3D9j9rdaTlFVpD3O1E9Gauj0nf3Vyfr8XfJvRDlOuzU+I0D31rJer1ieRzqPv6SJqD4d8kvG3oX3pNi0yaLtZPuUYH6DVqiYZug/bfT6fI3+ba3RbD9bP76A/eMH10jO2qqHhPr2WW7s9PNvILa7sq+Yu5ltp3Ty/EQiDatdQ0zeSatajXrjS1uW714ybXs6uZU16m8bJd8dI0T3N9CortP831cMZFx6Jrq4G20iKgrSQb3WrZVZdpRr+UU+OmG/1qmVw6Xq97+Z+jfdfEyNjxllvHjI/R2wtpgsYPSW30S7z644f4R5l+y+jaOX5InMF1/ZbJp72v3s0Y8pZrDMHv7rueTWm47sdW10VOU9fd12JYwLUYoNeil+6Dn0w5u8Kv9VqscNX30oK584qmF8yaMz3q9dB0WQ32U7Xx+op/Av714v/Q3UeZe72XJfw18Web9L19x4+D4YsSPln8RSZ+D+2/uKvcWHv/eigrxC0lD/tXZMeXOn2QhN8s+dfIXrvT7OzN/ewgO5y0KeKvn18Ha2Traup4bhI5ch+elFCUFG6WlFDM/5E6cH9rcVyLUa1TNX4F8c+24ydWVCTFdzH2cSM1Xmf8zbT+HNa67l6kI3UpIwZbHrsvvW7jj9eXPqV1KxV3oLrOpK+qbed1bXzqjLkFBb7PHRo31ehiUQzfEXffyzrL1K2Vt0y/JCTvTXeZigvOM7bR9rNFw+d1nmfYQd7z9MdTUduuSo8sin0cqU2TWq9N9UuV+7Oy+aZN1Y93rMbrJW1JzK1N23HGy3LK2KZhGRuqM5SL41IuU2d6SZ2hDKqjQaqjGh8d/SaD/96u1dE5U08aPHjouHFThwwdN3jsqdk5p44eNbW4fLalst2WIbKd49AVaevXl/uj1pf005w2buRHOcnPVc71yd5y3k7c9GjlnDdtVnlBYDk1baqz/8qPXEsugwk3fcAeyiHXxbRROYex1du231ZPbfX2vU3eB2KTd0LN5nOfOvCWx564aVyXVcfOeDDYJu/5sH187eu5n90zq+O2f127Ysg7XR/eybsNcrzyw0k/uSnv3paXJK4PpX7zu8f/+2z4Gmur52/zF2zDd8Bx9vHwVwf/Y/bowjPeadnzqpJrFrYKtrn8xrK4+5OfjMnLQ8S10I/j752yHqfzTjpfVsgfreACTbuG7rMHfBIeBZ+Cx8GndZ3sOTgWvqDrsC/ByXAdPAO+DM+C6+Es+CdYBl+Fy+Cf4Q2wWtfxcnEVWp6RWp4WcISW535dx6vUdbwH4WHwIS3faniMriNnqX+QY115mKVzHLBA828GB2r+txCvk66794e3qby3w5Phr+EY8dfllxclv2s0v2s1v+s0vxs1v2WSH37Nb6mlz5X6fE1+sq/wYs2vhHhpasfWE5bCYWqncDo8D86HF8CL1Z7zVrXjXAUvhi/ARXA=
*/