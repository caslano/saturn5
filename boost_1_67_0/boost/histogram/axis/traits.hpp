// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_TRAITS_HPP
#define BOOST_HISTOGRAM_AXIS_TRAITS_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/args_type.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/detail/try_cast.hpp>
#include <boost/histogram/detail/type_name.hpp>
#include <boost/variant2/variant.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
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

static axis::null_type null_value;

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
using static_options [[deprecated("use get_options instead")]] = get_options<Axis>;

#else
struct get_options;
#endif

/** Meta-function to detect whether an axis is inclusive.

  Doxygen does not render this well. This is a meta-function (template alias), it accepts
  an axis type and represents compile-time boolean which is true or false, depending on
  whether the axis is inclusive or not.

  An axis with underflow and overflow bins is always inclusive, but an axis may be
  inclusive under other conditions. The meta-function checks for the method `constexpr
  static bool inclusive()`, and uses the result. If this method is not present, it uses
  get_options<Axis> and checks whether the underflow and overflow bits are present.

  An inclusive axis has a bin for every possible input value. A histogram which consists
  only of inclusive axes can be filled more efficiently, since input values always
  end up in a valid cell and there is no need to keep track of input tuples that need to
  be discarded.

  @tparam Axis axis type
*/
template <class Axis>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using is_inclusive = decltype(detail::traits_is_inclusive<Axis>(detail::priority<1>{}));

template <class Axis>
using static_is_inclusive [[deprecated("use is_inclusive instead")]] = is_inclusive<Axis>;

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
  boost::ignore_unused(axis);
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
  boost::ignore_unused(axis);
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
  boost::ignore_unused(axis);
  return is_ordered<Axis>::value;
}

// specialization for variant
template <class... Ts>
bool ordered(const variant<Ts...>& axis) noexcept {
  return axis.ordered();
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
  return detail::static_if<detail::has_method_metadata<std::decay_t<Axis>>>(
      [](auto&& a) -> decltype(auto) { return a.metadata(); },
      [](auto &&) -> mp11::mp_if<std::is_const<std::remove_reference_t<Axis>>,
                                 axis::null_type const&, axis::null_type&> {
        return detail::null_value;
      },
      std::forward<Axis>(axis));
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
      value(axis, index)); // avoid conversion warning
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
template <class Axis>
constexpr unsigned rank(const Axis& axis) {
  boost::ignore_unused(axis);
  using T = value_type<Axis>;
  // cannot use mp_eval_or since T could be a fixed-sized sequence
  return mp11::mp_eval_if_not<detail::is_tuple<T>, mp11::mp_size_t<1>, mp11::mp_size,
                              T>::value;
}

// specialization for variant
template <class... Ts>
unsigned rank(const axis::variant<Ts...>& axis) {
  return detail::variant_access::visit([](const auto& a) { return rank(a); }, axis);
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
        return {index(a, value), 0};
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