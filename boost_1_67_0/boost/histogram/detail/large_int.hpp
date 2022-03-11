// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_LARGE_INT_HPP
#define BOOST_HISTOGRAM_DETAIL_LARGE_INT_HPP

#include <boost/assert.hpp>
#include <boost/histogram/detail/operators.hpp>
#include <boost/histogram/detail/safe_comparison.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
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
    BOOST_ASSERT(data.size() > 0u);
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
    BOOST_ASSERT(data.size() > 0u);
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
    BOOST_ASSERT(data.size() > 0u);
    double result = static_cast<double>(data[0]);
    std::size_t i = 0;
    while (++i < data.size())
      result += static_cast<double>(data[i]) * std::pow(2.0, i * 64);
    return result;
  }

  bool operator<(const large_int& o) const noexcept {
    BOOST_ASSERT(data.size() > 0u);
    BOOST_ASSERT(o.data.size() > 0u);
    // no leading zeros allowed
    BOOST_ASSERT(data.size() == 1 || data.back() > 0u);
    BOOST_ASSERT(o.data.size() == 1 || o.data.back() > 0u);
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
    BOOST_ASSERT(data.size() > 0u);
    BOOST_ASSERT(o.data.size() > 0u);
    // no leading zeros allowed
    BOOST_ASSERT(data.size() == 1 || data.back() > 0u);
    BOOST_ASSERT(o.data.size() == 1 || o.data.back() > 0u);
    if (data.size() != o.data.size()) return false;
    return std::equal(data.begin(), data.end(), o.data.begin());
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator<(const U& o) const
      noexcept {
    BOOST_ASSERT(data.size() > 0u);
    return data.size() == 1 && safe_less()(data[0], o);
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator>(const U& o) const
      noexcept {
    BOOST_ASSERT(data.size() > 0u);
    BOOST_ASSERT(data.size() == 1 || data.back() > 0u); // no leading zeros allowed
    return data.size() > 1 || safe_less()(o, data[0]);
  }

  template <class U>
  std::enable_if_t<std::is_integral<U>::value, bool> operator==(const U& o) const
      noexcept {
    BOOST_ASSERT(data.size() > 0u);
    return data.size() == 1 && safe_equal()(data[0], o);
  }

  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator<(const U& o) const
      noexcept {
    return operator double() < o;
  }
  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator>(const U& o) const
      noexcept {
    return operator double() > o;
  }
  template <class U>
  std::enable_if_t<std::is_floating_point<U>::value, bool> operator==(const U& o) const
      noexcept {
    return operator double() == o;
  }

  std::uint64_t& maybe_extend(std::size_t i) {
    while (i >= data.size()) data.push_back(0);
    return data[i];
  }

  static void add_remainder(std::uint64_t& d, const std::uint64_t o) noexcept {
    BOOST_ASSERT(d > 0u);
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