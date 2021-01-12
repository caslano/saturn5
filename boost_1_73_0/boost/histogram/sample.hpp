// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_SAMPLE_HPP
#define BOOST_HISTOGRAM_SAMPLE_HPP

#include <tuple>
#include <utility>

namespace boost {
namespace histogram {

template <class T>
struct sample_type {
  T value;
};

/** Helper function to mark arguments as sample.

  @param ts arguments to be forwarded to the accumulator.
*/
template <class... Ts>
auto sample(Ts&&... ts) noexcept {
  return sample_type<std::tuple<Ts...>>{std::forward_as_tuple(std::forward<Ts>(ts)...)};
}

} // namespace histogram
} // namespace boost

#endif

/* sample.hpp
7cmoiMM9Xyy6oC0xcXNmLlPzK9jmIWVsM+JN57eXGex681fcDETIVigwZCqOaIFbp7JAHSj328Iy3xu162apUNFcAiDjxMX1f/pLlhJO7xE/7pZ0UP9/O0iyMH6jyG430CF0SoFW25/VtlnqtIE6Oj3nAS5fR9C7l7Ax6aXrhamKRrf3UwXM4lRL/1QEuvdPKTBgqdpAbfwoxWLZVMOaBTALA6YhIbXDYaG3TgqcTyTy0rQo
*/