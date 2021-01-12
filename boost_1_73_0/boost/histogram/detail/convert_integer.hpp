// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP
#define BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using convert_integer =
    std::conditional_t<std::is_integral<std::decay_t<T>>::value, U, T>;

}
} // namespace histogram
} // namespace boost

#endif

/* convert_integer.hpp
TFBUT30fREW4MbMOzHo6JdsSjhSg+XYtt+XAKN1mznoaKKqjGnJ1n6DbR65WBr5ObluTn5jEnpBqGqh+saFYhOZJzyqxkMk7INSuKhBTjArEZBZfUJOc0HCsoIaaDKwq/VmVs2PiF/kPWnOK8zuJFdTtO6eAZSXhjO7bTl7zIvABxOrufoDLVaQEGjqqFj2Bj+j0lPTpM7Syl5D3XHSERLK6BW9myXa1eOEMK4S6UIRxFC7p
*/