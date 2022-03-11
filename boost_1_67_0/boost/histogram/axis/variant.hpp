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
#include <boost/variant2/variant.hpp>
#include <boost/histogram/detail/variant_proxy.hpp>
#include <boost/mp11/algorithm.hpp> // mp_contains
#include <boost/mp11/list.hpp>      // mp_first
#include <boost/throw_exception.hpp>
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

  // maybe metadata_type or const metadata_type, if bounded type is const
  using metadata_type = std::remove_reference_t<decltype(
      traits::metadata(std::declval<std::remove_pointer_t<mp11::mp_first<variant>>>()))>;

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

  /// Return reference to const metadata or instance of null_type if axis has no
  /// metadata.
  const metadata_type& metadata() const {
    return visit(
        [](const auto& a) -> const metadata_type& {
          using M = decltype(traits::metadata(a));
          return detail::static_if<std::is_same<M, const metadata_type&>>(
              [](const auto& a) -> const metadata_type& { return traits::metadata(a); },
              [](const auto&) -> const metadata_type& {
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

  /** Compare two variants.

    Return true if the variants point to the same concrete axis type and the types compare
    equal. Otherwise return false.
  */
  template <class... Us>
  bool operator==(const variant<Us...>& u) const {
    return visit([&u](const auto& x) { return u == x; }, *this);
  }

  /** Compare variant with a concrete axis type.

    Return true if the variant point to the same concrete axis type and the types compare
    equal. Otherwise return false.
  */
  template <class T>
  bool operator==(const T& t) const {
    return detail::static_if_c<(mp11::mp_contains<impl_type, T>::value ||
                                mp11::mp_contains<impl_type, T*>::value ||
                                mp11::mp_contains<impl_type, const T*>::value)>(
        [&](const auto& t) {
          using U = std::decay_t<decltype(t)>;
          const U* tp = detail::variant_access::template get_if<U>(this);
          return tp && detail::relaxed_equal(*tp, t);
        },
        [&](const auto&) { return false; }, t);
  }

  /// The negation of operator==.
  template <class T>
  bool operator!=(const T& t) const {
    return !operator==(t);
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

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* variant.hpp
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
*/