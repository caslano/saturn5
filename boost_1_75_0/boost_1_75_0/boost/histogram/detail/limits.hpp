// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LIMITS_HPP
#define BOOST_HISTOGRAM_DETAIL_LIMITS_HPP

#include <limits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr T lowest() {
  return std::numeric_limits<T>::lowest();
}

template <>
constexpr double lowest() {
  return -std::numeric_limits<double>::infinity();
}

template <>
constexpr float lowest() {
  return -std::numeric_limits<float>::infinity();
}

template <class T>
constexpr T highest() {
  return (std::numeric_limits<T>::max)();
}

template <>
constexpr double highest() {
  return std::numeric_limits<double>::infinity();
}

template <>
constexpr float highest() {
  return std::numeric_limits<float>::infinity();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* limits.hpp
mSuAjYCnzEVpusNjj5fS6Y179V97KWU+m8c9FgulkMgEgGE3qj7bvlp6sV+oXPvbDuWGvC3ArxyR3fsXmmUHjqqDYW50eDuqD7/pjtfCuSdUY4FCKGQqc5qfhKfC1d0nbqqLHvGXc8PwO42m8MCU4hvgw0D5Q+lIbanRJIvdajb17HQ+ShHR+nfq8aVjGhZlnWC7ZBZWvlrs0SQ5pkpQcjHblgJJIXsn+mThByMgevcdu5KTpJGj2A+Kg3XoBzOgLNq0unz/NetK1JKl975jm3SyHxOUlCyvufSpece9A9lj1QUJGHIrKkY3Xf8EeQEAszzwQvn80fyfzIZ8gzFK4DQcRYaD1rZFS9r2GoJ4JOWT/XUr6RKsKVHfUQaPX6fuChKMqYqkYe77+DpXsO+LYE7aHpiZ7exx3hv/tefKKZp2k//+iq3JYvWKkzYQuryUJjpqZ32wt1RiialDtvpynFf1bbmp/DICljc15Va8pgSvZh1N9GP2xiuNmn57xPI9PPKuojFAU/i4Gc8p4ja4ior4DRgzl3dh4vYrI/tf3sK91qDO3RlqSXBJ7jV5Z04LlOMu7KrLjeNpYOAlr5pI7LTvNDW/Y6AVkv8nlXTCxpJPqUIPyOIUkMNEcijHYSvVgzqjVWLiwMgSRlOCg3mGNjVmnaUn2mr/bc2qON87KKoQQb2i+oIRP8r6mFbtvD3WdX2jPZnepKNJc51v
*/