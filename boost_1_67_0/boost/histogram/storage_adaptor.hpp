// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_STORAGE_ADAPTOR_HPP
#define BOOST_HISTOGRAM_STORAGE_ADAPTOR_HPP

#include <algorithm>
#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/array_wrapper.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/iterator_adaptor.hpp>
#include <boost/histogram/detail/safe_comparison.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct vector_impl : T {
  using allocator_type = typename T::allocator_type;

  static constexpr bool has_threading_support =
      accumulators::is_thread_safe<typename T::value_type>::value;

  vector_impl(const allocator_type& a = {}) : T(a) {}
  vector_impl(const vector_impl&) = default;
  vector_impl& operator=(const vector_impl&) = default;
  vector_impl(vector_impl&&) = default;
  vector_impl& operator=(vector_impl&&) = default;

  explicit vector_impl(T&& t) : T(std::move(t)) {}
  explicit vector_impl(const T& t) : T(t) {}

  template <class U, class = requires_iterable<U>>
  explicit vector_impl(const U& u, const allocator_type& a = {})
      : T(std::begin(u), std::end(u), a) {}

  template <class U, class = requires_iterable<U>>
  vector_impl& operator=(const U& u) {
    T::resize(u.size());
    auto it = T::begin();
    for (auto&& x : u) *it++ = x;
    return *this;
  }

  void reset(std::size_t n) {
    using value_type = typename T::value_type;
    const auto old_size = T::size();
    T::resize(n, value_type());
    std::fill_n(T::begin(), (std::min)(n, old_size), value_type());
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("vector", static_cast<T&>(*this));
  }
};

template <class T>
struct array_impl : T {
  static constexpr bool has_threading_support =
      accumulators::is_thread_safe<typename T::value_type>::value;

  array_impl() = default;
  array_impl(const array_impl& t) : T(t), size_(t.size_) {}
  array_impl& operator=(const array_impl& t) {
    T::operator=(t);
    size_ = t.size_;
    return *this;
  }

  explicit array_impl(T&& t) : T(std::move(t)) {}
  explicit array_impl(const T& t) : T(t) {}

  template <class U, class = requires_iterable<U>>
  explicit array_impl(const U& u) : size_(u.size()) {
    using std::begin;
    using std::end;
    std::copy(begin(u), end(u), this->begin());
  }

  template <class U, class = requires_iterable<U>>
  array_impl& operator=(const U& u) {
    if (u.size() > T::max_size()) // for std::arra
      BOOST_THROW_EXCEPTION(std::length_error("argument size exceeds maximum capacity"));
    size_ = u.size();
    using std::begin;
    using std::end;
    std::copy(begin(u), end(u), T::begin());
    return *this;
  }

  void reset(std::size_t n) {
    using value_type = typename T::value_type;
    if (n > T::max_size()) // for std::array
      BOOST_THROW_EXCEPTION(std::length_error("argument size exceeds maximum capacity"));
    std::fill_n(T::begin(), n, value_type());
    size_ = n;
  }

  typename T::iterator end() noexcept { return T::begin() + size_; }
  typename T::const_iterator end() const noexcept { return T::begin() + size_; }

  std::size_t size() const noexcept { return size_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("size", size_);
    auto w = detail::make_array_wrapper(T::data(), size_);
    ar& make_nvp("array", w);
  }

  std::size_t size_ = 0;
};

template <class T>
struct map_impl : T {
  static_assert(std::is_same<typename T::key_type, std::size_t>::value,
                "requires std::size_t as key_type");

  using value_type = typename T::mapped_type;
  using const_reference = const value_type&;

  static constexpr bool has_threading_support = false;
  static_assert(
      !accumulators::is_thread_safe<value_type>::value,
      "std::map and std::unordered_map do not support thread-safe element access. "
      "If you have a map with thread-safe element access, please file an issue and"
      "support will be added.");

  struct reference {
    reference(map_impl* m, std::size_t i) noexcept : map(m), idx(i) {}

    reference(const reference&) noexcept = default;
    reference& operator=(const reference& o) {
      if (this != &o) operator=(static_cast<const_reference>(o));
      return *this;
    }

    operator const_reference() const noexcept {
      return static_cast<const map_impl*>(map)->operator[](idx);
    }

    reference& operator=(const_reference u) {
      auto it = map->find(idx);
      if (u == value_type{}) {
        if (it != static_cast<T*>(map)->end()) { map->erase(it); }
      } else {
        if (it != static_cast<T*>(map)->end()) {
          it->second = u;
        } else {
          map->emplace(idx, u);
        }
      }
      return *this;
    }

    template <class U, class V = value_type,
              class = std::enable_if_t<has_operator_radd<V, U>::value>>
    reference& operator+=(const U& u) {
      auto it = map->find(idx);
      if (it != static_cast<T*>(map)->end()) {
        it->second += u;
      } else {
        map->emplace(idx, u);
      }
      return *this;
    }

    template <class U, class V = value_type,
              class = std::enable_if_t<has_operator_rsub<V, U>::value>>
    reference& operator-=(const U& u) {
      auto it = map->find(idx);
      if (it != static_cast<T*>(map)->end()) {
        it->second -= u;
      } else {
        map->emplace(idx, -u);
      }
      return *this;
    }

    template <class U, class V = value_type,
              class = std::enable_if_t<has_operator_rmul<V, U>::value>>
    reference& operator*=(const U& u) {
      auto it = map->find(idx);
      if (it != static_cast<T*>(map)->end()) it->second *= u;
      return *this;
    }

    template <class U, class V = value_type,
              class = std::enable_if_t<has_operator_rdiv<V, U>::value>>
    reference& operator/=(const U& u) {
      auto it = map->find(idx);
      if (it != static_cast<T*>(map)->end()) {
        it->second /= u;
      } else if (!(value_type{} / u == value_type{})) {
        map->emplace(idx, value_type{} / u);
      }
      return *this;
    }

    template <class V = value_type,
              class = std::enable_if_t<has_operator_preincrement<V>::value>>
    reference operator++() {
      auto it = map->find(idx);
      if (it != static_cast<T*>(map)->end()) {
        ++it->second;
      } else {
        value_type tmp{};
        ++tmp;
        map->emplace(idx, tmp);
      }
      return *this;
    }

    template <class V = value_type,
              class = std::enable_if_t<has_operator_preincrement<V>::value>>
    value_type operator++(int) {
      const value_type tmp = *this;
      operator++();
      return tmp;
    }

    template <class U, class = std::enable_if_t<has_operator_equal<value_type, U>::value>>
    bool operator==(const U& rhs) const {
      return operator const_reference() == rhs;
    }

    template <class U, class = std::enable_if_t<has_operator_equal<value_type, U>::value>>
    bool operator!=(const U& rhs) const {
      return !operator==(rhs);
    }

    template <class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& os, reference x) {
      os << static_cast<const_reference>(x);
      return os;
    }

    template <class... Ts>
    auto operator()(const Ts&... args) -> decltype(std::declval<value_type>()(args...)) {
      return (*map)[idx](args...);
    }

    map_impl* map;
    std::size_t idx;
  };

  template <class Value, class Reference, class MapPtr>
  struct iterator_t
      : iterator_adaptor<iterator_t<Value, Reference, MapPtr>, std::size_t, Reference> {
    iterator_t() = default;
    template <class V, class R, class M, class = requires_convertible<M, MapPtr>>
    iterator_t(const iterator_t<V, R, M>& it) noexcept : iterator_t(it.map_, it.base()) {}
    iterator_t(MapPtr m, std::size_t i) noexcept
        : iterator_t::iterator_adaptor_(i), map_(m) {}
    template <class V, class R, class M>
    bool equal(const iterator_t<V, R, M>& rhs) const noexcept {
      return map_ == rhs.map_ && iterator_t::base() == rhs.base();
    }
    Reference operator*() const { return (*map_)[iterator_t::base()]; }
    MapPtr map_ = nullptr;
  };

  using iterator = iterator_t<value_type, reference, map_impl*>;
  using const_iterator = iterator_t<const value_type, const_reference, const map_impl*>;

  using allocator_type = typename T::allocator_type;

  map_impl(const allocator_type& a = {}) : T(a) {}

  map_impl(const map_impl&) = default;
  map_impl& operator=(const map_impl&) = default;
  map_impl(map_impl&&) = default;
  map_impl& operator=(map_impl&&) = default;

  map_impl(const T& t) : T(t), size_(t.size()) {}
  map_impl(T&& t) : T(std::move(t)), size_(t.size()) {}

  template <class U, class = requires_iterable<U>>
  explicit map_impl(const U& u, const allocator_type& a = {}) : T(a), size_(u.size()) {
    using std::begin;
    using std::end;
    std::copy(begin(u), end(u), this->begin());
  }

  template <class U, class = requires_iterable<U>>
  map_impl& operator=(const U& u) {
    if (u.size() < size_)
      reset(u.size());
    else
      size_ = u.size();
    using std::begin;
    using std::end;
    std::copy(begin(u), end(u), this->begin());
    return *this;
  }

  void reset(std::size_t n) {
    T::clear();
    size_ = n;
  }

  reference operator[](std::size_t i) noexcept { return {this, i}; }
  const_reference operator[](std::size_t i) const noexcept {
    auto it = T::find(i);
    static const value_type null = value_type{};
    if (it == T::end()) return null;
    return it->second;
  }

  iterator begin() noexcept { return {this, 0}; }
  iterator end() noexcept { return {this, size_}; }

  const_iterator begin() const noexcept { return {this, 0}; }
  const_iterator end() const noexcept { return {this, size_}; }

  std::size_t size() const noexcept { return size_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("size", size_);
    ar& make_nvp("map", static_cast<T&>(*this));
  }

  std::size_t size_ = 0;
};

template <class T>
struct ERROR_type_passed_to_storage_adaptor_not_recognized;

// clang-format off
template <class T>
using storage_adaptor_impl =
  mp11::mp_cond<
    is_vector_like<T>, vector_impl<T>,
    is_array_like<T>, array_impl<T>,
    is_map_like<T>, map_impl<T>,
    std::true_type, ERROR_type_passed_to_storage_adaptor_not_recognized<T>
  >;
// clang-format on
} // namespace detail

/// Turns any vector-like, array-like, and map-like container into a storage type.
template <class T>
class storage_adaptor : public detail::storage_adaptor_impl<T> {
  using impl_type = detail::storage_adaptor_impl<T>;

public:
  // standard copy, move, assign
  storage_adaptor(storage_adaptor&&) = default;
  storage_adaptor(const storage_adaptor&) = default;
  storage_adaptor& operator=(storage_adaptor&&) = default;
  storage_adaptor& operator=(const storage_adaptor&) = default;

  // forwarding constructor
  template <class... Ts>
  storage_adaptor(Ts&&... ts) : impl_type(std::forward<Ts>(ts)...) {}

  // forwarding assign
  template <class U>
  storage_adaptor& operator=(U&& u) {
    impl_type::operator=(std::forward<U>(u));
    return *this;
  }

  template <class U, class = detail::requires_iterable<U>>
  bool operator==(const U& u) const {
    using std::begin;
    using std::end;
    return std::equal(this->begin(), this->end(), begin(u), end(u), detail::safe_equal{});
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("impl", static_cast<impl_type&>(*this));
  }

private:
  friend struct unsafe_access;
};

} // namespace histogram
} // namespace boost

#endif

/* storage_adaptor.hpp
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
*/