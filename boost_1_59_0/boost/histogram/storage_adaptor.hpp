// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_STORAGE_ADAPTOR_HPP
#define BOOST_HISTOGRAM_STORAGE_ADAPTOR_HPP

#include <algorithm>
#include <boost/core/nvp.hpp>
#include <boost/histogram/accumulators/is_thread_safe.hpp>
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
    template <class V, class R, class M,
              class = std::enable_if_t<std::is_convertible<M, MapPtr>::value>>
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