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
ZFup7BZbsewpW+FC/TX6tS9sPdvsEbR7bdpe2SnOJa9NTgt96f0i+2MMNu3Z0YKUmro4F/vUNDhccXGWmviBCM8Owcrk4AiTHNw+mWz1iY2vZv08AB1VtaniNegIw8mi21Ji6MzC9fQ8yWk71w81eO3QJOK0o2w6cpdxo+z1Q+X8TTFDU+pHpX5eXNC21PMkyErHnj7/S7QGwWpRX6vvHIhZwHk1/kDIHiMG7XSO2cnGGavmZENOyNY3FIT1vQvt/RqusdYPjQR2W+vapAA4rmdk0Nq7svVPCvY6F9u72JY7Fzc6F99fhjVpvbvnkEFrZwsmkBWpoSO2/W8XHAlsTwVgn4biPs/T6m3DwVxIEgsZvgsWzGdH7TUWl18QaZgR8cAeuV7G0w6laHiGeNlLZSSXeueQ0XLDjMMwNGu45qhha2YnuB2fw7T6BPTS5y8sf+fxHiO7bM7GIPbLm67olps3rNJKhQS7ghCZABq3DhVfhTNUC34MMKrsVwyZy0ZevbneJIcpuStJyV12GlaQr1MUwZEsRgRn0FoVX+Sj/YnlIKYuFKjIy2bM5Faex5OoHziK5vRhdkVdNLGjdvVXppAotdDuuNjevd46pN7efTiFB3akUgPolrdBGK4kUEwJFgG3RI8IJQ+SjAxuKhJQ4/Gbx819+Mto7p1/PN3myrbmMUDKQkcZ1XMhmpve/eIWauxwtLYewdwM2egBsY3+UhnSKX6WFvL8/0KsfjefGgH9Hn5K8erCLzUmy1vtXJzVoFn1N8mkjg91j0O38GrGMN7kztikX4pH7o5NQbAxvEhuWA+xHi888SJBCvBunAMhwbgJnQNEp62vL8/rjzfhwsMF9JCFhwtZ2MTDRXjgqIvxwFEeOt8YBF+shyE1re+FtDN0oYJlBWtp+vPsMu7zGxEELDR+E+nMIztEFNOeYqVItiSELCrQIatAeZxkNSqobVQ+1WdheXHh8ItTiQzsAyupdlBOLViwi4zAaweQLF5vFFNhkQ2twPqLjHsnJVFota2+wm4uLSqS66tTaDxI4iEDYegJerHlTyHVsSR4qXHLQbIM/BcSl3H//XPSoRxNEjic35XPmem32/3svboZ6zp1jvibxOgONAzFyF6nj37I0WC/yLkYRtRLoKx5yGELBUcvcfBkUP4dx8UVlnrbyYJaMYRPFjYJ65TjwwKOwA1YcAHbycLawTFOFjYZXOVkYVOweDpZ2NTACqy6jKWpC9LW/TBypG5g3ve3VD5mgFfYYErTkSyV83fNnDEoyp+OwRzmeqRAOQvL58lewVwJCxbqy4knyuD7nMEz0LMBzqUy4L7iHB78B3tXAh9lccV3s0uyISG7yAIRgkQTNZiogQ0SSMAEQhIOYXHZXSxHsFVZt6gIuyAVAnShZfkI2lpr7WXtfdhbLbVqWSIJglxaEaQgrT0mRpGjEhDN9v/efPPt5lCO1v56bX6b/b55b+a9mXkz82bmzZsLTYFqkFOYfqEpUL1yChddaApU25zCbtMFpkAywClsuNAUSDKQQsh9QbH1ilwzAiJSF73bimlNb/iHJ0lRrx+xu/h/+8/GUGN/R2Pn/m7q4zwfs7letBf0WgkMTMoaZtiaWQVtrrDSD9yfuDbdj2X8TQ21sCdesAkz6PYYFu8jCIslBVRFHJFNttHktWTh7oZP2siUm/RUOd9ehmHrDod2g4D+O8YSI1V5N9a/XSfLMELQMrL1geh4Ec18gODaDW9+EMqbBspRiXKqI8pvsNPFp7gyf9MwxYz9KSCnuk5aNluay6A+Ad8+/hjbQKFvNzP+36LO32ivyPl23Ud0swBGFPIn03BvjrZoVpN1zMrqSHvp4kvZ7LM=
*/