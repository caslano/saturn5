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
auto accumulator_traits_impl(T&, priority<1>)
    -> decltype(accumulator_traits_impl_call_op(&T::operator()));

template <class T>
auto accumulator_traits_impl(T&, priority<1>)
    -> decltype(std::declval<T&>() += 0, accumulator_traits_holder<true>{});

template <class T>
auto accumulator_traits_impl(T&, priority<0>) -> accumulator_traits_holder<false>;

// for boost.accumulators compatibility
template <class S, class F, class W>
accumulator_traits_holder<false, S> accumulator_traits_impl(
    boost::accumulators::accumulator_set<S, F, W>&, priority<1>) {
  static_assert(std::is_same<W, void>::value,
                "accumulator_set with weights is not directly supported, please use "
                "a wrapper class that implements the Accumulator concept");
}

template <class T>
using accumulator_traits =
    decltype(accumulator_traits_impl(std::declval<T&>(), priority<1>{}));

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* accumulator_traits.hpp
AYxzq/Hc26VWTKtW220WmgGRp2UhdWpE6g30IU1p5aY4UTiTqNwayFmt/tx1E+fWQpy2cGNqFOaOVK4gFE8eR5xa1Fqc7SK7gAsEw8pXBeOD/ZABuJTPll9q5XqcYVORtPLz5LSutAPQLNNhNRnSooE8d8UdZfvPq05ib3ToDPCW45LEcAGyVePO1MLYTKl1YyvW7lSOCDZmZ8v0tA/0i73Vhro0uuyT9Pz022mW3Si1KSe2qMchUr3ftnERZuD6SwLVt69STFhtDKMrkTrtDVNhuYz9U+E87e+exStlsRzJnA/2Dvbe2tkfALc+qgIBHm+/YQxOn59n52fV2K0ZYGRV0YscZRj6Pw+uCf8oLiq+Whv7wV4R6sYEW2l6hjxrF+BKaFqZiYh3DMf/dbsG+VoKVuCz5ziCouEbEUHnA9LrPspzErKAXsDUl20XuNH+DlIMnzIq93HwgMJI1SnyfWwA0P3vhN3lW1QPHgVwQkBAQAF/NAhId0uH0p3S3d05gAhISqe0dHe30t3N0B1DDAw1M4tbL/bZffZPuPfdufd8P6f3uWSH6YN7MAruU24qnjTPgd5j/cai+KAnmbEQeFf+1DWQP+xHbQinTYDIOdH4NLtTDLcXQOI7Eh/eD/uVHsgAFV3stp9LabSgIgkFoOT62K6/RtqwXwl9IkSLN9FLB8Ll43RDRgtqzDarg0eR+xCsXlS1fYv1P+HY
*/