// Copyright 2015-2017 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_LITERALS_HPP
#define BOOST_HISTOGRAM_LITERALS_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
constexpr unsigned parse_number(unsigned n) { return n; }

template <class... Rest>
constexpr unsigned parse_number(unsigned n, char f, Rest... rest) {
  return parse_number(10u * n + static_cast<unsigned>(f - '0'), rest...);
}
} // namespace detail

namespace literals {
/// Suffix operator to generate literal compile-time numbers, 0_c, 12_c, etc.
template <char... digits>
auto operator"" _c() {
  return std::integral_constant<unsigned, detail::parse_number(0, digits...)>();
}
} // namespace literals
} // namespace histogram
} // namespace boost

#endif

/* literals.hpp
rBvnBsqK/FXcdPEyC0/20E0znWBNTWO8+0bLP/FHDETL+z1YytTqMi+6Id9Jn073jJhLhWBxxncNzVyrggmcMz6TqEoE58kvArC90I7nBgpVZXBBKxSN0Du8nq6t9hLKD2hCm406/wB/4T51TZfwOhBx6KSBSo0wrPHrRVmhOQs+KbXR1mfXXy7XJZKGuW4MNlGKVPq5XPmpYQ01S91kgPbAa78EhIj+mycozUqHMHMt62AFxgg+y+rgcUlhlAjTJoB75Z/fVZuf4S+WJF4Kt9H7eUiBD5OQLc4HMAY4wl4SDTLMez8qbnP5x9bJu/f+NOWGI1bOdZkrbuXu7bWGX6VTDxR/E+u2KNXv4A8z+/cFx4eeEcuYFFjDU4t1ULFNo5qgAZy5HXQm++Dm6NQ9bmHfEYCoWUvfdVVUM4XluzA6cfLJQMJbHpkzQtCx5UJBJaxq/d5ymDBqFrUIpdyYIgi7UOCLhSAPl/CoM4cW50Q3g9msTPJiDA3RUHq+5e4fAa/9iISEDCkfEPo0/gh/jiYqKGxq+ujjlvtgUGBg3zi/ki6JrazrGksHHA==
*/