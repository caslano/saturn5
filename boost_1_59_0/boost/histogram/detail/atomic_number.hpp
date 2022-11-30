// Copyright 2021 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ATOMIC_NUMBER_HPP
#define BOOST_HISTOGRAM_DETAIL_ATOMIC_NUMBER_HPP

#include <atomic>
#include <boost/histogram/detail/priority.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

// copyable arithmetic type with thread-safe operator++ and operator+=
template <class T>
struct atomic_number : std::atomic<T> {
  static_assert(std::is_arithmetic<T>(), "");

  using base_t = std::atomic<T>;
  using std::atomic<T>::atomic;

  atomic_number() noexcept = default;
  atomic_number(const atomic_number& o) noexcept : std::atomic<T>{o.load()} {}
  atomic_number& operator=(const atomic_number& o) noexcept {
    this->store(o.load());
    return *this;
  }

  // not defined for float
  atomic_number& operator++() noexcept {
    increment_impl(static_cast<base_t&>(*this), priority<1>{});
    return *this;
  }

  // operator is not defined for floating point before C++20
  atomic_number& operator+=(const T& x) noexcept {
    add_impl(static_cast<base_t&>(*this), x, priority<1>{});
    return *this;
  }

  // not thread-safe
  atomic_number& operator*=(const T& x) noexcept {
    this->store(this->load() * x);
    return *this;
  }

  // not thread-safe
  atomic_number& operator/=(const T& x) noexcept {
    this->store(this->load() / x);
    return *this;
  }

private:
  // for integral types
  template <class U = T>
  auto increment_impl(std::atomic<U>& a, priority<1>) noexcept -> decltype(++a) {
    return ++a;
  }

  // fallback implementation for floating point types
  template <class U = T>
  void increment_impl(std::atomic<U>&, priority<0>) noexcept {
    this->operator+=(static_cast<U>(1));
  }

  // always available for integral types, in C++20 also available for float
  template <class U = T>
  static auto add_impl(std::atomic<U>& a, const U& x, priority<1>) noexcept
      -> decltype(a += x) {
    return a += x;
  }

  // pre-C++20 fallback implementation for floating point
  template <class U = T>
  static void add_impl(std::atomic<U>& a, const U& x, priority<0>) noexcept {
    U expected = a.load();
    // if another tread changed `expected` in the meantime, compare_exchange returns
    // false and updates `expected`; we then loop and try to update again;
    // see https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange
    while (!a.compare_exchange_weak(expected, expected + x))
      ;
  }
};
} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* atomic_number.hpp
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
*/