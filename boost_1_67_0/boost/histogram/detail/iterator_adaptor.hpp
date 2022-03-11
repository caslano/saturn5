// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Uses code segments from boost/iterator/iterator_adaptor.hpp
// and boost/iterator/iterator_fascade.hpp

#ifndef BOOST_HISTOGRAM_DETAIL_ITERATOR_ADAPTOR_HPP
#define BOOST_HISTOGRAM_DETAIL_ITERATOR_ADAPTOR_HPP

#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

// operator->() needs special support for input iterators to strictly meet the
// standard's requirements. If *i is not a reference type, we must still
// produce an lvalue to which a pointer can be formed.  We do that by
// returning a proxy object containing an instance of the reference object.
template <class Reference>
struct operator_arrow_dispatch_t // proxy references
{
  struct proxy {
    explicit proxy(Reference const& x) noexcept : m_ref(x) {}
    Reference* operator->() noexcept { return std::addressof(m_ref); }
    Reference m_ref;
  };

  using result_type = proxy;
  static result_type apply(Reference const& x) noexcept { return proxy(x); }
};

template <class T>
struct operator_arrow_dispatch_t<T&> // "real" references
{
  using result_type = T*;
  static result_type apply(T& x) noexcept { return std::addressof(x); }
};

// only for random access Base
template <class Derived, class Base, class Reference = std::remove_pointer_t<Base>&,
          class Value = std::decay_t<Reference>>
class iterator_adaptor {
  using operator_arrow_dispatch = operator_arrow_dispatch_t<Reference>;

public:
  using base_type = Base;

  using reference = Reference;
  using value_type = std::remove_const_t<Value>;
  using pointer = typename operator_arrow_dispatch::result_type;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

  iterator_adaptor() = default;

  explicit iterator_adaptor(base_type const& iter) : iter_(iter) {}

  pointer operator->() const noexcept {
    return operator_arrow_dispatch::apply(this->derived().operator*());
  }
  reference operator[](difference_type n) const { return *(this->derived() + n); }

  Derived& operator++() {
    ++iter_;
    return this->derived();
  }

  Derived& operator--() {
    --iter_;
    return this->derived();
  }

  Derived operator++(int) {
    Derived tmp(this->derived());
    ++iter_;
    return tmp;
  }

  Derived operator--(int) {
    Derived tmp(this->derived());
    --iter_;
    return tmp;
  }

  Derived& operator+=(difference_type n) {
    iter_ += n;
    return this->derived();
  }

  Derived& operator-=(difference_type n) {
    iter_ -= n;
    return this->derived();
  }

  Derived operator+(difference_type n) const {
    Derived tmp(this->derived());
    tmp += n;
    return tmp;
  }

  Derived operator-(difference_type n) const { return operator+(-n); }

  template <class... Ts>
  difference_type operator-(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ - x.iter_;
  }

  template <class... Ts>
  bool operator==(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ == x.iter_;
  }
  template <class... Ts>
  bool operator!=(const iterator_adaptor<Ts...>& x) const noexcept {
    return !this->derived().operator==(x); // equal operator may be overridden in derived
  }
  template <class... Ts>
  bool operator<(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ < x.iter_;
  }
  template <class... Ts>
  bool operator>(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ > x.iter_;
  }
  template <class... Ts>
  bool operator<=(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ <= x.iter_;
  }
  template <class... Ts>
  bool operator>=(const iterator_adaptor<Ts...>& x) const noexcept {
    return iter_ >= x.iter_;
  }

  friend Derived operator+(difference_type n, const Derived& x) { return x + n; }

  Base const& base() const noexcept { return iter_; }

protected:
  // for convenience in derived classes
  using iterator_adaptor_ = iterator_adaptor;

private:
  Derived& derived() noexcept { return *static_cast<Derived*>(this); }
  const Derived& derived() const noexcept { return *static_cast<Derived const*>(this); }

  Base iter_;

  template <class, class, class, class>
  friend class iterator_adaptor;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* iterator_adaptor.hpp
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
*/