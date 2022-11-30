// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_SUB_ARRAY_HPP
#define BOOST_HISTOGRAM_DETAIL_SUB_ARRAY_HPP

#include <algorithm>
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace histogram {
namespace detail {

template <class T, std::size_t N>
class sub_array {
  constexpr bool swap_element_is_noexcept() noexcept {
    using std::swap;
    return noexcept(swap(std::declval<T&>(), std::declval<T&>()));
  }

public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = pointer;
  using const_iterator = const_pointer;

  sub_array() = default;

  explicit sub_array(std::size_t s) noexcept : size_(s) { assert(size_ <= N); }

  sub_array(std::size_t s, const T& value) noexcept(
      std::is_nothrow_assignable<T, const_reference>::value)
      : sub_array(s) {
    fill(value);
  }

  reference at(size_type pos) noexcept {
    if (pos >= size()) BOOST_THROW_EXCEPTION(std::out_of_range{"pos is out of range"});
    return data_[pos];
  }

  const_reference at(size_type pos) const noexcept {
    if (pos >= size()) BOOST_THROW_EXCEPTION(std::out_of_range{"pos is out of range"});
    return data_[pos];
  }

  reference operator[](size_type pos) noexcept { return data_[pos]; }
  const_reference operator[](size_type pos) const noexcept { return data_[pos]; }

  reference front() noexcept { return data_[0]; }
  const_reference front() const noexcept { return data_[0]; }

  reference back() noexcept { return data_[size_ - 1]; }
  const_reference back() const noexcept { return data_[size_ - 1]; }

  pointer data() noexcept { return static_cast<pointer>(data_); }
  const_pointer data() const noexcept { return static_cast<const_pointer>(data_); }

  iterator begin() noexcept { return data_; }
  const_iterator begin() const noexcept { return data_; }

  iterator end() noexcept { return begin() + size_; }
  const_iterator end() const noexcept { return begin() + size_; }

  const_iterator cbegin() noexcept { return data_; }
  const_iterator cbegin() const noexcept { return data_; }

  const_iterator cend() noexcept { return cbegin() + size_; }
  const_iterator cend() const noexcept { return cbegin() + size_; }

  constexpr size_type max_size() const noexcept { return N; }
  size_type size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  void fill(const_reference value) noexcept(
      std::is_nothrow_assignable<T, const_reference>::value) {
    std::fill(begin(), end(), value);
  }

  void swap(sub_array& other) noexcept(swap_element_is_noexcept()) {
    using std::swap;
    for (auto i = begin(), j = other.begin(); i != end(); ++i, ++j) swap(*i, *j);
  }

private:
  size_type size_ = 0;
  value_type data_[N];
};

template <class T, std::size_t N>
bool operator==(const sub_array<T, N>& a, const sub_array<T, N>& b) noexcept {
  return std::equal(a.begin(), a.end(), b.begin());
}

template <class T, std::size_t N>
bool operator!=(const sub_array<T, N>& a, const sub_array<T, N>& b) noexcept {
  return !(a == b);
}

} // namespace detail
} // namespace histogram
} // namespace boost

namespace std {
template <class T, std::size_t N>
void swap(::boost::histogram::detail::sub_array<T, N>& a,
          ::boost::histogram::detail::sub_array<T, N>& b) noexcept(noexcept(a.swap(b))) {
  a.swap(b);
}
} // namespace std

#endif

/* sub_array.hpp
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
*/