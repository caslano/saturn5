// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP
#define BOOST_HISTOGRAM_DETAIL_OPTIONAL_INDEX_HPP

#include <boost/assert.hpp>
#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

constexpr auto invalid_index = ~static_cast<std::size_t>(0);

// integer with a persistent invalid state, similar to NaN
struct optional_index {
  std::size_t value;

  optional_index& operator=(std::size_t x) noexcept {
    value = x;
    return *this;
  }

  optional_index& operator+=(std::intptr_t x) noexcept {
    BOOST_ASSERT(x >= 0 || static_cast<std::size_t>(-x) <= value);
    if (value != invalid_index) { value += x; }
    return *this;
  }

  optional_index& operator+=(const optional_index& x) noexcept {
    if (value != invalid_index) return operator+=(x.value);
    value = invalid_index;
    return *this;
  }

  operator std::size_t() const noexcept { return value; }

  friend bool operator<=(std::size_t x, optional_index idx) noexcept {
    return x <= idx.value;
  }
};

constexpr inline bool is_valid(const std::size_t) noexcept { return true; }

inline bool is_valid(const optional_index x) noexcept { return x.value != invalid_index; }

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* optional_index.hpp
ByorS8c2SL1LVKLDA3Cbn3+glePmStvfzv5gezj9Jvg6YBTqRX4iyO5c4pSrrFyA+mB8N9tlINiJ/KU+TK1WZiZ6He0IfNer/atmunn54NrT/tank8zBwQBqObC0ujBfPqg+YOhkROvSHP+h63MXWUWbeQoJzri/ITfEJ/YWovSWYkMwWbRX5+4DJoUC7hQe+u8QE2mw6o17EunGyZNrncYedf7enH3YD5ESn2QbITTc4v40Y4C5HatiKUXabm7ASDgEy3S7/557a36NFkZd5OLEnC4r6zdp+ZlfQpqz1ESWqftR6qY2hPRwmRh0yY0G7m0vTiLdjK4FqPvd8vCQsakHbNdw0D6yqLc2l6JzZTDhKl0c2Fdk3LtfnbqBf2FqsEljVSR8+vCm81uyIreBSLv+q7SDOJeSyd/pvi9miQrTXEhHK/bjOGzf/5QyddYPWNXrVd3JftVUfxgUl0Xtcm77wYsns9oxns4FNZXqrK5Ua17wyLaPQaRbo/JuOYJh80oDiWDriKr5pwWSVeK4cGW3ZP2UVrlAs++iYaH8d2u9wpGyTRsN8e7+O09Ekqky3aWKsjlgOqPq71U23Db2O5ZXIpjBIM52A4IfKUr1/sk1ybzIN2OlcssPjXJYNQuAXe0y69S4E54/u4DzrD2w+kLiaKXGH4EApfkxM1aWQQX9bzo6eQs4OSdR80+Ob31Ste08TCd4w5dnke7P
*/