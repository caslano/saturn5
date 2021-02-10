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
1vwP+jiumbXar416QNkLvC8fvi+l9WBhogaLbC2tDbpIVsOeUJXPmLz7zyubBH+UOSYrtVGgLTeV4KYOu5aHzDm/lA4nDKan1baVLKSr9s8qZTYcn/bcuK0wdxoVGYocBh3qyHOdn+snVJjjyFz7dlkQGgfnIWpwtgPWYODJEBVNAGIZJYhTx3z4yNKbI4PXGqymwDDx5oKo4rNqwgbnufl2dH4+fDE4Z2BUL6cD3XGKN0hbt2sab0Lg8YPPrSj2sMtWxLGnkAMYiGHd9dxIqm7VjJdzTJeb/zA6GWqOUqpP2rPbEK7kwUS4zvxTjbSVigxiBQysfnGa3PRMOvDvmo95y2AuoWyI5a6wh9MzI9evN43fjVpj2/lU2DUPCJ8CwdvH+3Q4Bra1Uezysxle1ApDd8KPMH6cb2DdgQlM61WBUVkBbQRsgKfP7g5i3BUKAOJTQ0AaMV0uvfIucFSHJAWHbRN9HmwwV9hw/JMx/3I4OB3ehQudk7micXeYG7NZBhe/d1Idw7/rGpWrWwrLaIlHpDyE4wcd6flUo69HGM879XU6M5zBrT2qcgfXva3KolS6sF95UE3d07NfWfijdmTD4LdFqSrD3Bp0e9D5RIZjqmXV4jNosm8K8qn4+miCT2nKVxRtdNxrcY8r
*/