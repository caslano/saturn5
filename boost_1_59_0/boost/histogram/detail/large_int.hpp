// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LARGE_INT_HPP
#define BOOST_HISTOGRAM_DETAIL_LARGE_INT_HPP

#include <boost/histogram/detail/operators.hpp>
#include <boost/histogram/detail/safe_comparison.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
using is_unsigned_integral = mp11::mp_and<std::is_integral<T>, std::is_unsigned<T>>;

template <class T>
bool safe_increment(T& t) {
  if (t < (std::numeric_limits<T>::max)()) {
    ++t;
    return true;
  }
  return false;
}

template <class T, class U>
bool safe_radd(T& t, const U& u) {
  static_assert(is_unsigned_integral<T>::value, "T must be unsigned integral type");
  static_assert(is_unsigned_integral<U>::value, "T must be unsigned integral type");
  if (static_cast<T>((std::numeric_limits<T>::max)() - t) >= u) {
    t += static_cast<T>(u); // static_cast to suppress conversion warning
    return true;
  }
  return false;
}

// An integer type which can grow arbitrarily large (until memory is exhausted).
// Use boost.multiprecision.cpp_int in your own code, it is much more sophisticated.
// We use it only to reduce coupling between boost libs.
template <class Allocator>
struct large_int : totally_ordered<large_int<Allocator>, large_int<Allocator>>,
                   partially_ordered<large_int<Allocator>, void> {
  explicit large_int(const Allocator& a = {}) : data(1, 0, a) {}
  explicit large_int(std::uint64_t v, const Allocator& a = {}) : data(1, v, a) {}

  large_int(const large_int&) = default;
  large_int& operator=(const large_int&) = default;
  large_int(large_int&&) = default;
  large_int& operator=(large_int&&) = default;

  large_int& operator=(std::uint64_t o) {
    data = decltype(data)(1, o);
    return *this;
  }

  large_int& operator++() {
    assert(data.size() > 0u);
    std::size_t i = 0;
    while (!safe_increment(data[i])) {
      data[i] = 0;
      ++i;
      if (i == data.size()) {
        data.push_back(1);
        break;
      }
    }
    return *this;
  }

  large_int& operator+=(const large_int& o) {
    if (this == &o) {
      auto tmp{o};
      return operator+=(tmp);
    }
    bool carry = false;
    std::size_t i = 0;
    for (std::uint64_t oi : o.data) {
      auto& di = maybe_extend(i);
      if (carry) {
        if (safe_increment(oi))
          carry = false;
        else {
          ++i;
          continue;
        }
      }
      if (!safe_radd(di, oi)) {
        add_remainder(di, oi);
        carry = true;
      }
      ++i;
    }
    while (carry) {
      auto& di = maybe_extend(i);
      if (safe_increment(di)) break;
      di = 0;
      ++i;
    }
    return *this;
  }

  large_int& operator+=(std::uint64_t o) {
    assert(data.size() > 0u);
    if (safe_radd(data[0], o)) return *this;
    add_remainder(data[0], o);
    // carry the one, data may grow several times
    std::size_t i = 1;
    while (true) {
      auto& di = maybe_extend(i);
      if (safe_increment(di)) break;
      di = 0;
      ++i;
    }
    return *this;
  }

  explicit operator double() const noexcept {
    assert(data.size() > 0u);
    double result = static_cast<double>(data[0]);
    std::size_t i = 0;
    while (++i < data.size())
      result += static_cast<double>(data[i]) * std::pow(2.0, i * 64);
    return result;
  }

  bool operator<(const large_int& o) const noexcept {
    assert(data.size() > 0u);
    assert(o.data.size() > 0u);
    // no leading zeros allowed
    assert(data.size() == 1 || data.back() > 0u);
    assert(o.data.size() == 1 || o.data.back() > 0u);
    if (data.size() < o.data.size()) return true;
    if (data.size() > o.data.size()) return false;
    auto s = data.size();
    while (s > 0u) {
      --s;
      if (data[s] < o.data[s]) return true;
      if (data[s] > o.data[s]) return false;
    }
    return false; // args are equal
  }

  bool operator==(const large_int& o) const noexcept {
    assert(data.size() > 0u);
    assert(o.data.size() > 0u);
    // no leading zeros allowed
    assert(data.size() == 1 || data.back() > 0u);
    assert(o.data.size() == 1 || o.data.back() > 0u);
    if (data.size() != o.data.size()) return false;
    return std::equal(data.begin(), data.end(), o.data.begin());
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator<(
      const U& o) const noexcept {
    assert(data.size() > 0u);
    return data.size() == 1 && safe_less()(data[0], o);
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator>(
      const U& o) const noexcept {
    assert(data.size() > 0u);
    assert(data.size() == 1 || data.back() > 0u); // no leading zeros allowed
    return data.size() > 1 || safe_less()(o, data[0]);
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator==(
      const U& o) const noexcept {
    assert(data.size() > 0u);
    return data.size() == 1 && safe_equal()(data[0], o);
  }

  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator<(
      const U& o) const noexcept {
    return operator double() < o;
  }

  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator>(
      const U& o) const noexcept {
    return operator double() > o;
  }

  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator==(
      const U& o) const noexcept {
    return operator double() == o;
  }

  template <class U>
  std::enable_if_t<
      (!std::is_arithmetic<U>::value && std::is_convertible<U, double>::value), bool>
  operator<(const U& o) const noexcept {
    return operator double() < o;
  }

  template <class U>
  std::enable_if_t<
      (!std::is_arithmetic<U>::value && std::is_convertible<U, double>::value), bool>
  operator>(const U& o) const noexcept {
    return operator double() > o;
  }

  template <class U>
  std::enable_if_t<
      (!std::is_arithmetic<U>::value && std::is_convertible<U, double>::value), bool>
  operator==(const U& o) const noexcept {
    return operator double() == o;
  }

  std::uint64_t& maybe_extend(std::size_t i) {
    while (i >= data.size()) data.push_back(0);
    return data[i];
  }

  static void add_remainder(std::uint64_t& d, const std::uint64_t o) noexcept {
    assert(d > 0u);
    // in decimal system it would look like this:
    // 8 + 8 = 6 = 8 - (9 - 8) - 1
    // 9 + 1 = 0 = 9 - (9 - 1) - 1
    auto tmp = (std::numeric_limits<std::uint64_t>::max)();
    tmp -= o;
    --d -= tmp;
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("data", data);
  }

  std::vector<std::uint64_t, Allocator> data;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* large_int.hpp
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
*/