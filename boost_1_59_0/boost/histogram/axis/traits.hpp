// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_TRAITS_HPP
#define BOOST_HISTOGRAM_AXIS_TRAITS_HPP

#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/args_type.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/detail/try_cast.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant2/variant.hpp>
#include <stdexcept>
#include <string>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

template <class Axis>
struct value_type_deducer {
  using type =
      std::remove_cv_t<std::remove_reference_t<detail::arg_type<decltype(&Axis::index)>>>;
};

template <class Axis>
auto traits_options(priority<2>) -> axis::option::bitset<Axis::options()>;

template <class Axis>
auto traits_options(priority<1>) -> decltype(&Axis::update, axis::option::growth_t{});

template <class Axis>
auto traits_options(priority<0>) -> axis::option::none_t;

template <class Axis>
auto traits_is_inclusive(priority<1>) -> std::integral_constant<bool, Axis::inclusive()>;

template <class Axis>
auto traits_is_inclusive(priority<0>)
    -> decltype(traits_options<Axis>(priority<2>{})
                    .test(axis::option::underflow | axis::option::overflow));

template <class Axis>
auto traits_is_ordered(priority<1>) -> std::integral_constant<bool, Axis::ordered()>;

template <class Axis, class ValueType = typename value_type_deducer<Axis>::type>
auto traits_is_ordered(priority<0>) -> typename std::is_arithmetic<ValueType>::type;

template <class I, class D, class A,
          class J = std::decay_t<arg_type<decltype(&A::value)>>>
decltype(auto) value_method_switch(I&& i, D&& d, const A& a, priority<1>) {
  return static_if<std::is_same<J, axis::index_type>>(std::forward<I>(i),
                                                      std::forward<D>(d), a);
}

template <class I, class D, class A>
double value_method_switch(I&&, D&&, const A&, priority<0>) {
  // comma trick to make all compilers happy; some would complain about
  // unreachable code after the throw, others about a missing return
  return BOOST_THROW_EXCEPTION(
             std::runtime_error(type_name<A>() + " has no value method")),
         double{};
}

struct variant_access {
  template <class T, class Variant>
  static auto get_if(Variant* v) noexcept {
    using T0 = mp11::mp_first<std::decay_t<Variant>>;
    return static_if<std::is_pointer<T0>>(
        [](auto* vptr) {
          using TP = mp11::mp_if<std::is_const<std::remove_pointer_t<T0>>, const T*, T*>;
          auto ptp = variant2::get_if<TP>(vptr);
          return ptp ? *ptp : nullptr;
        },
        [](auto* vptr) { return variant2::get_if<T>(vptr); }, &(v->impl));
  }

  template <class T0, class Visitor, class Variant>
  static decltype(auto) visit_impl(mp11::mp_identity<T0>, Visitor&& vis, Variant&& v) {
    return variant2::visit(std::forward<Visitor>(vis), v.impl);
  }

  template <class T0, class Visitor, class Variant>
  static decltype(auto) visit_impl(mp11::mp_identity<T0*>, Visitor&& vis, Variant&& v) {
    return variant2::visit(
        [&vis](auto&& x) -> decltype(auto) { return std::forward<Visitor>(vis)(*x); },
        v.impl);
  }

  template <class Visitor, class Variant>
  static decltype(auto) visit(Visitor&& vis, Variant&& v) {
    using T0 = mp11::mp_first<std::decay_t<Variant>>;
    return visit_impl(mp11::mp_identity<T0>{}, std::forward<Visitor>(vis),
                      std::forward<Variant>(v));
  }
};

template <class A>
decltype(auto) metadata_impl(A&& a, decltype(a.metadata(), 0)) {
  return std::forward<A>(a).metadata();
}

template <class A>
axis::null_type& metadata_impl(A&&, float) {
  static axis::null_type null_value;
  return null_value;
}

} // namespace detail

namespace axis {
namespace traits {

/** Value type for axis type.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and returns the value type.

  The value type is deduced from the argument of the `Axis::index` method. Const
  references are decayed to the their value types, for example, the type deduced for
  `Axis::index(const int&)` is `int`.

  The deduction always succeeds if the axis type models the Axis concept correctly. Errors
  come from violations of the concept, in particular, an index method that is templated or
  overloaded is not allowed.

  @tparam Axis axis type.
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using value_type = typename detail::value_type_deducer<Axis>::type;
#else
struct value_type;
#endif

/** Whether axis is continuous or discrete.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and returns a compile-time boolean.

  If the boolean is true, the axis is continuous (covers a continuous range of values).
  Otherwise it is discrete (covers discrete values).
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using is_continuous = typename std::is_floating_point<traits::value_type<Axis>>::type;
#else
struct is_continuous;
#endif

/** Meta-function to detect whether an axis is reducible.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and represents compile-time boolean which is true or false, depending on
  whether the axis can be reduced with boost::histogram::algorithm::reduce().

  An axis can be made reducible by adding a special constructor, see Axis concept for
  details.

  @tparam Axis axis type.
 */
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using is_reducible = std::is_constructible<Axis, const Axis&, axis::index_type,
                                           axis::index_type, unsigned>;
#else
struct is_reducible;
#endif

/** Get axis options for axis type.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and returns the boost::histogram::axis::option::bitset.

  If Axis::options() is valid and constexpr, get_options is the corresponding
  option type. Otherwise, it is boost::histogram::axis::option::growth_t, if the
  axis has a method `update`, else boost::histogram::axis::option::none_t.

  @tparam Axis axis type
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using get_options = decltype(detail::traits_options<Axis>(detail::priority<2>{}));

template <class Axis>
using static_options [[deprecated("use get_options instead; "
                                  "static_options will be removed in boost-1.80")]] =
    get_options<Axis>;

#else
struct get_options;
#endif

/** Meta-function to detect whether an axis is inclusive.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and represents compile-time boolean which is true or false, depending on
  whether the axis is inclusive or not.

  An inclusive axis has a bin for every possible input value. In other words, all
  possible input values always end up in a valid cell and there is no need to keep track
  of input tuples that need to be discarded. A histogram which consists entirely of
  inclusive axes can be filled more efficiently, which can be a factor 2 faster.

  An axis with underflow and overflow bins is always inclusive, but an axis may be
  inclusive under other conditions. The meta-function checks for the method `constexpr
  static bool inclusive()`, and uses the result. If this method is not present, it uses
  get_options<Axis> and checks whether the underflow and overflow bits are present.

  @tparam Axis axis type
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using is_inclusive = decltype(detail::traits_is_inclusive<Axis>(detail::priority<1>{}));

template <class Axis>
using static_is_inclusive
    [[deprecated("use is_inclusive instead; "
                 "static_is_inclusive will be removed in boost-1.80")]] =
        is_inclusive<Axis>;

#else
struct is_inclusive;
#endif

/** Meta-function to detect whether an axis is ordered.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and returns a compile-time boolean. If the boolean is true, the axis is
  ordered.

  The meta-function checks for the method `constexpr static bool ordered()`, and uses the
  result. If this method is not present, it returns true if the value type of the Axis is
  arithmetic and false otherwise.

  An ordered axis has a value type that is ordered, which means that indices i <
  j < k implies either value(i) < value(j) < value(k) or value(i) > value(j) > value(k)
  for all i,j,k. For example, the integer axis is ordered, but the category axis is not.
  Axis which are not ordered must not have underflow bins, because they only have an
  "other" category, which is identified with the overflow bin if it is available.

  @tparam Axis axis type
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using is_ordered = decltype(detail::traits_is_ordered<Axis>(detail::priority<1>{}));
#else
struct is_ordered;
#endif

/** Returns axis options as unsigned integer.

  See get_options for details.

  @param axis any axis instance
*/
template <class Axis>
constexpr unsigned options(const Axis& axis) noexcept {
  (void)axis;
  return get_options<Axis>::value;
}

// specialization for variant
template <class... Ts>
unsigned options(const variant<Ts...>& axis) noexcept {
  return axis.options();
}

/** Returns true if axis is inclusive or false.

  See is_inclusive for details.

  @param axis any axis instance
*/
template <class Axis>
constexpr bool inclusive(const Axis& axis) noexcept {
  (void)axis;
  return is_inclusive<Axis>::value;
}

// specialization for variant
template <class... Ts>
bool inclusive(const variant<Ts...>& axis) noexcept {
  return axis.inclusive();
}

/** Returns true if axis is ordered or false.

  See is_ordered for details.

  @param axis any axis instance
*/
template <class Axis>
constexpr bool ordered(const Axis& axis) noexcept {
  (void)axis;
  return is_ordered<Axis>::value;
}

// specialization for variant
template <class... Ts>
bool ordered(const variant<Ts...>& axis) noexcept {
  return axis.ordered();
}

/** Returns true if axis is continuous or false.

  See is_continuous for details.

  @param axis any axis instance
*/
template <class Axis>
constexpr bool continuous(const Axis& axis) noexcept {
  (void)axis;
  return is_continuous<Axis>::value;
}

// specialization for variant
template <class... Ts>
bool continuous(const variant<Ts...>& axis) noexcept {
  return axis.continuous();
}

/** Returns axis size plus any extra bins for under- and overflow.

  @param axis any axis instance
*/
template <class Axis>
index_type extent(const Axis& axis) noexcept {
  const auto opt = options(axis);
  return axis.size() + (opt & option::underflow ? 1 : 0) +
         (opt & option::overflow ? 1 : 0);
}

/** Returns reference to metadata of an axis.

  If the expression x.metadata() for an axis instance `x` (maybe const) is valid, return
  the result. Otherwise, return a reference to a static instance of
  boost::histogram::axis::null_type.

  @param axis any axis instance
*/
template <class Axis>
decltype(auto) metadata(Axis&& axis) noexcept {
  return detail::metadata_impl(std::forward<Axis>(axis), 0);
}

/** Returns axis value for index.

  If the axis has no `value` method, throw std::runtime_error. If the method exists and
  accepts a floating point index, pass the index and return the result. If the method
  exists but accepts only integer indices, cast the floating point index to int, pass this
  index and return the result.

  @param axis any axis instance
  @param index floating point axis index
*/
template <class Axis>
decltype(auto) value(const Axis& axis, real_index_type index) {
  return detail::value_method_switch(
      [index](const auto& a) { return a.value(static_cast<index_type>(index)); },
      [index](const auto& a) { return a.value(index); }, axis, detail::priority<1>{});
}

/** Returns axis value for index if it is convertible to target type or throws.

  Like boost::histogram::axis::traits::value, but converts the result into the requested
  return type. If the conversion is not possible, throws std::runtime_error.

  @tparam Result requested return type
  @tparam Axis axis type
  @param axis any axis instance
  @param index floating point axis index
*/
template <class Result, class Axis>
Result value_as(const Axis& axis, real_index_type index) {
  return detail::try_cast<Result, std::runtime_error>(
      axis::traits::value(axis, index)); // avoid conversion warning
}

/** Returns axis index for value.

  Throws std::invalid_argument if the value argument is not implicitly convertible.

  @param axis any axis instance
  @param value argument to be passed to `index` method
*/
template <class Axis, class U>
axis::index_type index(const Axis& axis, const U& value) noexcept(
    std::is_convertible<U, value_type<Axis>>::value) {
  return axis.index(detail::try_cast<value_type<Axis>, std::invalid_argument>(value));
}

// specialization for variant
template <class... Ts, class U>
axis::index_type index(const variant<Ts...>& axis, const U& value) {
  return axis.index(value);
}

/** Return axis rank (how many arguments it processes).

  @param axis any axis instance
*/
// gcc workaround: must use unsigned int not unsigned as return type
template <class Axis>
constexpr unsigned int rank(const Axis& axis) {
  (void)axis;
  using T = value_type<Axis>;
  // cannot use mp_eval_or since T could be a fixed-sized sequence
  return mp11::mp_eval_if_not<detail::is_tuple<T>, mp11::mp_size_t<1>, mp11::mp_size,
                              T>::value;
}

// specialization for variant
// gcc workaround: must use unsigned int not unsigned as return type
template <class... Ts>
unsigned int rank(const axis::variant<Ts...>& axis) {
  return detail::variant_access::visit(
      [](const auto& a) { return axis::traits::rank(a); }, axis);
}

/** Returns pair of axis index and shift for the value argument.

  Throws `std::invalid_argument` if the value argument is not implicitly convertible to
  the argument expected by the `index` method. If the result of
  boost::histogram::axis::traits::get_options<decltype(axis)> has the growth flag set,
  call `update` method with the argument and return the result. Otherwise, call `index`
  and return the pair of the result and a zero shift.

  @param axis any axis instance
  @param value argument to be passed to `update` or `index` method
*/
template <class Axis, class U>
std::pair<index_type, index_type> update(Axis& axis, const U& value) noexcept(
    std::is_convertible<U, value_type<Axis>>::value) {
  return detail::static_if_c<get_options<Axis>::test(option::growth)>(
      [&value](auto& a) {
        return a.update(detail::try_cast<value_type<Axis>, std::invalid_argument>(value));
      },
      [&value](auto& a) -> std::pair<index_type, index_type> {
        return {axis::traits::index(a, value), 0};
      },
      axis);
}

// specialization for variant
template <class... Ts, class U>
std::pair<index_type, index_type> update(variant<Ts...>& axis, const U& value) {
  return visit([&value](auto& a) { return a.update(value); }, axis);
}

/** Returns bin width at axis index.

  If the axis has no `value` method, throw std::runtime_error. If the method exists and
  accepts a floating point index, return the result of `axis.value(index + 1) -
  axis.value(index)`. If the method exists but accepts only integer indices, return 0.

  @param axis any axis instance
  @param index bin index
 */
template <class Axis>
decltype(auto) width(const Axis& axis, index_type index) {
  return detail::value_method_switch(
      [](const auto&) { return 0; },
      [index](const auto& a) { return a.value(index + 1) - a.value(index); }, axis,
      detail::priority<1>{});
}

/** Returns bin width at axis index.

  Like boost::histogram::axis::traits::width, but converts the result into the requested
  return type. If the conversion is not possible, throw std::runtime_error.

  @param axis any axis instance
  @param index bin index
 */
template <class Result, class Axis>
Result width_as(const Axis& axis, index_type index) {
  return detail::value_method_switch(
      [](const auto&) { return Result{}; },
      [index](const auto& a) {
        return detail::try_cast<Result, std::runtime_error>(a.value(index + 1) -
                                                            a.value(index));
      },
      axis, detail::priority<1>{});
}

} // namespace traits
} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* traits.hpp
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
*/