// Copyright 2020 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_MULTI_INDEX_HPP
#define BOOST_HISTOGRAM_MULTI_INDEX_HPP

#include <algorithm>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <boost/throw_exception.hpp>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <tuple>

namespace boost {
namespace histogram {

/** Holder for multiple axis indices.

  Adapts external iterable, tuple, or explicit list of indices to the same representation.
 */
template <std::size_t Size>
struct multi_index {
  using value_type = axis::index_type;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  static multi_index create(std::size_t s) {
    if (s != size())
      BOOST_THROW_EXCEPTION(std::invalid_argument("size does not match static size"));
    return multi_index(priv_tag{});
  }

  template <class... Is>
  multi_index(axis::index_type i, Is... is)
      : multi_index(std::initializer_list<axis::index_type>{
            i, static_cast<axis::index_type>(is)...}) {}

  template <class... Is>
  multi_index(const std::tuple<axis::index_type, Is...>& is)
      : multi_index(is, mp11::make_index_sequence<(1 + sizeof...(Is))>{}) {}

  template <class Iterable, class = detail::requires_iterable<Iterable>>
  multi_index(const Iterable& is) {
    if (detail::size(is) != size())
      BOOST_THROW_EXCEPTION(std::invalid_argument("no. of axes != no. of indices"));
    using std::begin;
    using std::end;
    std::copy(begin(is), end(is), data_);
  }

  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + size(); }
  const_iterator begin() const noexcept { return data_; }
  const_iterator end() const noexcept { return data_ + size(); }
  static constexpr std::size_t size() noexcept { return Size; }

private:
  struct priv_tag {};

  multi_index(priv_tag) {}

  template <class T, std::size_t... Is>
  multi_index(const T& is, mp11::index_sequence<Is...>)
      : multi_index(static_cast<axis::index_type>(std::get<Is>(is))...) {}

  axis::index_type data_[size()];
};

template <>
struct multi_index<static_cast<std::size_t>(-1)> {
  using value_type = axis::index_type;
  using iterator = value_type*;
  using const_iterator = const value_type*;

  static multi_index create(std::size_t s) { return multi_index(priv_tag{}, s); }

  template <class... Is>
  multi_index(axis::index_type i, Is... is)
      : multi_index(std::initializer_list<axis::index_type>{
            i, static_cast<axis::index_type>(is)...}) {}

  template <class... Is>
  multi_index(const std::tuple<axis::index_type, Is...>& is)
      : multi_index(is, mp11::make_index_sequence<(1 + sizeof...(Is))>{}) {}

  template <class Iterable, class = detail::requires_iterable<Iterable>>
  multi_index(const Iterable& is) : size_(detail::size(is)) {
    using std::begin;
    using std::end;
    std::copy(begin(is), end(is), data_);
  }

  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + size_; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator end() const noexcept { return data_ + size_; }
  std::size_t size() const noexcept { return size_; }

private:
  struct priv_tag {};

  multi_index(priv_tag, std::size_t s) : size_(s) {}

  template <class T, std::size_t... Ns>
  multi_index(const T& is, mp11::index_sequence<Ns...>)
      : multi_index(static_cast<axis::index_type>(std::get<Ns>(is))...) {}

  std::size_t size_ = 0;
  static constexpr std::size_t max_size_ = BOOST_HISTOGRAM_DETAIL_AXES_LIMIT;
  axis::index_type data_[max_size_];
};

} // namespace histogram
} // namespace boost

#endif

/* multi_index.hpp
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
*/