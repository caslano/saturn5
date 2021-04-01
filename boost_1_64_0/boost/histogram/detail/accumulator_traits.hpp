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
/KCHaVHrgauL1a5Q1Nhrc5I/qqY2kphMsCwul1hoCfrihs2kPZFAuf4DFI7L9NB1qqbDCk52yxPObUklbIyk4K+n37iMry3P07gOnqWqDiaSu8LKwpGb/VtgXjYRQtB6df/QabP2Y1jA4ZvrAxVaEfIbtobKjOLfrNrRCX1S2uF0tIvqhsvBLA5pK1qNRVQZHRnjwGVuXdFFTdphLchKnlWgNqshLhrJNaujmPqwf6UceRBQCY8jqR0xoC/nD3a5AA+JYjmHUriDenLv9SnwhXdANtYXM3qMsQrrlv0O12lYEU/D2QOHYpB3Hcb8fyePebZbIq1x8pVDOWVCoKQx/Hr04LuR2cB4V46RAN552MzRoDxFMHq/nbhwSOT5DnzSQN3l7n7UA2LIQMBYCW6fg/Ma/Ybi+heaG7/oG2EJMWd7TwLh+NfDCUKhe+Im0y9jBG8FH1RtdHun5jgWvxenN5Oz3eV0cgPMz3WQ7HtXCoWAM8S+x9UiciXD0NX+isi0vC6IRClN53gQolrQDLS3r1TfSRpKURazle573JveE4Wiom+5Cku7TdoV8Q==
*/