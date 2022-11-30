// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_VARIANT_HPP
#define BOOST_HISTOGRAM_AXIS_VARIANT_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/polymorphic_bin.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/histogram/detail/variant_proxy.hpp>
#include <boost/mp11/algorithm.hpp> // mp_contains
#include <boost/mp11/list.hpp>      // mp_first
#include <boost/throw_exception.hpp>
#include <boost/variant2/variant.hpp>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace axis {

/// Polymorphic axis type
template <class... Ts>
class variant : public iterator_mixin<variant<Ts...>> {
  using impl_type = boost::variant2::variant<Ts...>;

  template <class T>
  using is_bounded_type = mp11::mp_contains<variant, std::decay_t<T>>;

  template <class T>
  using requires_bounded_type = std::enable_if_t<is_bounded_type<T>::value>;

  using metadata_type = std::remove_const_t<std::remove_reference_t<decltype(
      traits::metadata(std::declval<std::remove_pointer_t<mp11::mp_first<variant>>>()))>>;

public:
  // cannot import ctors with using directive, it breaks gcc and msvc
  variant() = default;
  variant(const variant&) = default;
  variant& operator=(const variant&) = default;
  variant(variant&&) = default;
  variant& operator=(variant&&) = default;

  template <class T, class = requires_bounded_type<T>>
  variant(T&& t) : impl(std::forward<T>(t)) {}

  template <class T, class = requires_bounded_type<T>>
  variant& operator=(T&& t) {
    impl = std::forward<T>(t);
    return *this;
  }

  template <class... Us>
  variant(const variant<Us...>& u) {
    this->operator=(u);
  }

  template <class... Us>
  variant& operator=(const variant<Us...>& u) {
    visit(
        [this](const auto& u) {
          using U = std::decay_t<decltype(u)>;
          detail::static_if<is_bounded_type<U>>(
              [this](const auto& u) { this->operator=(u); },
              [](const auto&) {
                BOOST_THROW_EXCEPTION(std::runtime_error(
                    detail::type_name<U>() + " is not convertible to a bounded type of " +
                    detail::type_name<variant>()));
              },
              u);
        },
        u);
    return *this;
  }

  /// Return size of axis.
  index_type size() const {
    return visit([](const auto& a) -> index_type { return a.size(); }, *this);
  }

  /// Return options of axis or option::none_t if axis has no options.
  unsigned options() const {
    return visit([](const auto& a) { return traits::options(a); }, *this);
  }

  /// Returns true if the axis is inclusive or false.
  bool inclusive() const {
    return visit([](const auto& a) { return traits::inclusive(a); }, *this);
  }

  /// Returns true if the axis is ordered or false.
  bool ordered() const {
    return visit([](const auto& a) { return traits::ordered(a); }, *this);
  }

  /// Returns true if the axis is continuous or false.
  bool continuous() const {
    return visit([](const auto& a) { return traits::continuous(a); }, *this);
  }

  /// Return reference to const metadata or instance of null_type if axis has no
  /// metadata.
  metadata_type& metadata() const {
    return visit(
        [](const auto& a) -> metadata_type& {
          using M = decltype(traits::metadata(a));
          return detail::static_if<std::is_same<M, metadata_type&>>(
              [](const auto& a) -> metadata_type& { return traits::metadata(a); },
              [](const auto&) -> metadata_type& {
                BOOST_THROW_EXCEPTION(std::runtime_error(
                    "cannot return metadata of type " + detail::type_name<M>() +
                    " through axis::variant interface which uses type " +
                    detail::type_name<metadata_type>() +
                    "; use boost::histogram::axis::get to obtain a reference "
                    "of this axis type"));
              },
              a);
        },
        *this);
  }

  /// Return reference to metadata or instance of null_type if axis has no
  /// metadata.
  metadata_type& metadata() {
    return visit(
        [](auto& a) -> metadata_type& {
          using M = decltype(traits::metadata(a));
          return detail::static_if<std::is_same<M, metadata_type&>>(
              [](auto& a) -> metadata_type& { return traits::metadata(a); },
              [](auto&) -> metadata_type& {
                BOOST_THROW_EXCEPTION(std::runtime_error(
                    "cannot return metadata of type " + detail::type_name<M>() +
                    " through axis::variant interface which uses type " +
                    detail::type_name<metadata_type>() +
                    "; use boost::histogram::axis::get to obtain a reference "
                    "of this axis type"));
              },
              a);
        },
        *this);
  }

  /** Return index for value argument.

    Throws std::invalid_argument if axis has incompatible call signature.
  */
  template <class U>
  index_type index(const U& u) const {
    return visit([&u](const auto& a) { return traits::index(a, u); }, *this);
  }

  /** Return value for index argument.

    Only works for axes with value method that returns something convertible
    to double and will throw a runtime_error otherwise, see
    axis::traits::value().
  */
  double value(real_index_type idx) const {
    return visit([idx](const auto& a) { return traits::value_as<double>(a, idx); },
                 *this);
  }

  /** Return bin for index argument.

    Only works for axes with value method that returns something convertible
    to double and will throw a runtime_error otherwise, see
    axis::traits::value().
  */
  auto bin(index_type idx) const {
    return visit(
        [idx](const auto& a) {
          return detail::value_method_switch(
              [idx](const auto& a) { // axis is discrete
                const double x = traits::value_as<double>(a, idx);
                return polymorphic_bin<double>(x, x);
              },
              [idx](const auto& a) { // axis is continuous
                const double x1 = traits::value_as<double>(a, idx);
                const double x2 = traits::value_as<double>(a, idx + 1);
                return polymorphic_bin<double>(x1, x2);
              },
              a, detail::priority<1>{});
        },
        *this);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    detail::variant_proxy<variant> p{*this};
    ar& make_nvp("variant", p);
  }

private:
  impl_type impl;

  friend struct detail::variant_access;
  friend struct boost::histogram::unsafe_access;
};

// specialization for empty argument list, useful for meta-programming
template <>
class variant<> {};

/// Apply visitor to variant (reference).
template <class Visitor, class... Us>
decltype(auto) visit(Visitor&& vis, variant<Us...>& var) {
  return detail::variant_access::visit(vis, var);
}

/// Apply visitor to variant (movable reference).
template <class Visitor, class... Us>
decltype(auto) visit(Visitor&& vis, variant<Us...>&& var) {
  return detail::variant_access::visit(vis, std::move(var));
}

/// Apply visitor to variant (const reference).
template <class Visitor, class... Us>
decltype(auto) visit(Visitor&& vis, const variant<Us...>& var) {
  return detail::variant_access::visit(vis, var);
}

/// Returns pointer to T in variant or null pointer if type does not match.
template <class T, class... Us>
auto get_if(variant<Us...>* v) {
  return detail::variant_access::template get_if<T>(v);
}

/// Returns pointer to const T in variant or null pointer if type does not match.
template <class T, class... Us>
auto get_if(const variant<Us...>* v) {
  return detail::variant_access::template get_if<T>(v);
}

/// Return reference to T, throws std::runtime_error if type does not match.
template <class T, class... Us>
decltype(auto) get(variant<Us...>& v) {
  auto tp = get_if<T>(&v);
  if (!tp) BOOST_THROW_EXCEPTION(std::runtime_error("T is not the held type"));
  return *tp;
}

/// Return movable reference to T, throws unspecified exception if type does not match.
template <class T, class... Us>
decltype(auto) get(variant<Us...>&& v) {
  auto tp = get_if<T>(&v);
  if (!tp) BOOST_THROW_EXCEPTION(std::runtime_error("T is not the held type"));
  return std::move(*tp);
}

/// Return const reference to T, throws unspecified exception if type does not match.
template <class T, class... Us>
decltype(auto) get(const variant<Us...>& v) {
  auto tp = get_if<T>(&v);
  if (!tp) BOOST_THROW_EXCEPTION(std::runtime_error("T is not the held type"));
  return *tp;
}

// pass-through version of visit for generic programming
template <class Visitor, class T>
decltype(auto) visit(Visitor&& vis, T&& var) {
  return std::forward<Visitor>(vis)(std::forward<T>(var));
}

// pass-through version of get for generic programming
template <class T, class U>
decltype(auto) get(U&& u) {
  return std::forward<U>(u);
}

// pass-through version of get_if for generic programming
template <class T, class U>
auto get_if(U* u) {
  return reinterpret_cast<T*>(std::is_same<T, std::decay_t<U>>::value ? u : nullptr);
}

// pass-through version of get_if for generic programming
template <class T, class U>
auto get_if(const U* u) {
  return reinterpret_cast<const T*>(std::is_same<T, std::decay_t<U>>::value ? u
                                                                            : nullptr);
}

/** Compare two variants.

  Return true if the variants point to the same concrete axis type and the types compare
  equal. Otherwise return false.
*/
template <class... Us, class... Vs>
bool operator==(const variant<Us...>& u, const variant<Vs...>& v) noexcept {
  return visit([&](const auto& vi) { return u == vi; }, v);
}

/** Compare variant with a concrete axis type.

  Return true if the variant point to the same concrete axis type and the types compare
  equal. Otherwise return false.
*/
template <class... Us, class T>
bool operator==(const variant<Us...>& u, const T& t) noexcept {
  using V = variant<Us...>;
  return detail::static_if_c<(mp11::mp_contains<V, T>::value ||
                              mp11::mp_contains<V, T*>::value ||
                              mp11::mp_contains<V, const T*>::value)>(
      [&](const auto& t) {
        using U = std::decay_t<decltype(t)>;
        const U* tp = detail::variant_access::template get_if<U>(&u);
        return tp && detail::relaxed_equal{}(*tp, t);
      },
      [&](const auto&) { return false; }, t);
}

template <class T, class... Us>
bool operator==(const T& t, const variant<Us...>& u) noexcept {
  return u == t;
}

/// The negation of operator==.
template <class... Us, class... Ts>
bool operator!=(const variant<Us...>& u, const variant<Ts...>& t) noexcept {
  return !(u == t);
}

/// The negation of operator==.
template <class... Us, class T>
bool operator!=(const variant<Us...>& u, const T& t) noexcept {
  return !(u == t);
}

/// The negation of operator==.
template <class T, class... Us>
bool operator!=(const T& t, const variant<Us...>& u) noexcept {
  return u != t;
}

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* variant.hpp
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
*/