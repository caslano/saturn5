// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ACCUMULATOR_TRAITS_HPP
#define BOOST_HISTOGRAM_DETAIL_ACCUMULATOR_TRAITS_HPP

#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/fwd.hpp>
#include <tuple>
#include <type_traits>

namespace boost {

// forward declare accumulator_set so that it can be matched below
namespace accumulators {
template <class, class, class>
struct accumulator_set;
}

namespace histogram {
namespace detail {

template <bool WeightSupport, class... Ts>
struct accumulator_traits_holder {
  static constexpr bool weight_support = WeightSupport;
  using args = std::tuple<Ts...>;
};

// member function pointer with weight_type as first argument is better match
template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>&, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(boost::histogram::weight_type<U>&&, Ts...));

template <class R, class T, class U, class... Ts>
accumulator_traits_holder<true, Ts...> accumulator_traits_impl_call_op(
    R (T::*)(const boost::histogram::weight_type<U>&, Ts...));

// member function pointer only considered if all specializations above fail
template <class R, class T, class... Ts>
accumulator_traits_holder<false, Ts...> accumulator_traits_impl_call_op(R (T::*)(Ts...));

template <class T>
auto accumulator_traits_impl(T&, priority<2>)
    -> decltype(accumulator_traits_impl_call_op(&T::operator()));

template <class T>
auto accumulator_traits_impl(T&, priority<2>)
    -> decltype(std::declval<T&>() += std::declval<boost::histogram::weight_type<int>>(),
                accumulator_traits_holder<true>{});

// fallback for simple arithmetic types that do not implement adding a weight_type
template <class T>
auto accumulator_traits_impl(T&, priority<1>)
    -> decltype(std::declval<T&>() += 0, accumulator_traits_holder<true>{});

template <class T>
auto accumulator_traits_impl(T&, priority<0>) -> accumulator_traits_holder<false>;

// for boost.accumulators compatibility
template <class S, class F, class W>
accumulator_traits_holder<false, S> accumulator_traits_impl(
    boost::accumulators::accumulator_set<S, F, W>&, priority<2>) {
  static_assert(std::is_same<W, void>::value,
                "accumulator_set with weights is not directly supported, please use "
                "a wrapper class that implements the Accumulator concept");
}

template <class T>
using accumulator_traits =
    decltype(accumulator_traits_impl(std::declval<T&>(), priority<2>{}));

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* accumulator_traits.hpp
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
*/