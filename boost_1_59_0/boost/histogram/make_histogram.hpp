// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_MAKE_HISTOGRAM_HPP
#define BOOST_HISTOGRAM_MAKE_HISTOGRAM_HPP

/**
  \file boost/histogram/make_histogram.hpp
  Collection of factory functions to conveniently create histograms.
*/

#include <boost/histogram/accumulators/weighted_sum.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/histogram.hpp>
#include <boost/histogram/storage_adaptor.hpp>
#include <boost/histogram/unlimited_storage.hpp> // = default_storage
#include <boost/mp11/utility.hpp>
#include <tuple>
#include <vector>

namespace boost {
namespace histogram {

/**
  Make histogram from compile-time axis configuration and custom storage.
  @param storage Storage or container with standard interface (any vector, array, or map).
  @param axis First axis instance.
  @param axes Other axis instances.
*/
template <class Storage, class Axis, class... Axes,
          class = detail::requires_storage_or_adaptible<Storage>,
          class = detail::requires_axis<Axis>>
auto make_histogram_with(Storage&& storage, Axis&& axis, Axes&&... axes) {
  auto a = std::make_tuple(std::forward<Axis>(axis), std::forward<Axes>(axes)...);
  using U = std::decay_t<Storage>;
  using S = mp11::mp_if<detail::is_storage<U>, U, storage_adaptor<U>>;
  return histogram<decltype(a), S>(std::move(a), S(std::forward<Storage>(storage)));
}

/**
  Make histogram from compile-time axis configuration and default storage.
  @param axis First axis instance.
  @param axes Other axis instances.
*/
template <class Axis, class... Axes, class = detail::requires_axis<Axis>>
auto make_histogram(Axis&& axis, Axes&&... axes) {
  return make_histogram_with(default_storage(), std::forward<Axis>(axis),
                             std::forward<Axes>(axes)...);
}

/**
  Make histogram from compile-time axis configuration and weight-counting storage.
  @param axis First axis instance.
  @param axes Other axis instances.
*/
template <class Axis, class... Axes, class = detail::requires_axis<Axis>>
auto make_weighted_histogram(Axis&& axis, Axes&&... axes) {
  return make_histogram_with(weight_storage(), std::forward<Axis>(axis),
                             std::forward<Axes>(axes)...);
}

/**
  Make histogram from iterable range and custom storage.
  @param storage Storage or container with standard interface (any vector, array, or map).
  @param iterable Iterable range of axis objects.
*/
template <class Storage, class Iterable,
          class = detail::requires_storage_or_adaptible<Storage>,
          class = detail::requires_sequence_of_any_axis<Iterable>>
auto make_histogram_with(Storage&& storage, Iterable&& iterable) {
  using U = std::decay_t<Storage>;
  using S = mp11::mp_if<detail::is_storage<U>, U, storage_adaptor<U>>;
  using It = std::decay_t<Iterable>;
  using A = mp11::mp_if<detail::is_indexable_container<It>, It,
                        std::vector<mp11::mp_first<It>>>;
  return histogram<A, S>(std::forward<Iterable>(iterable),
                         S(std::forward<Storage>(storage)));
}

/**
  Make histogram from iterable range and default storage.
  @param iterable Iterable range of axis objects.
*/
template <class Iterable, class = detail::requires_sequence_of_any_axis<Iterable>>
auto make_histogram(Iterable&& iterable) {
  return make_histogram_with(default_storage(), std::forward<Iterable>(iterable));
}

/**
  Make histogram from iterable range and weight-counting storage.
  @param iterable Iterable range of axis objects.
*/
template <class Iterable, class = detail::requires_sequence_of_any_axis<Iterable>>
auto make_weighted_histogram(Iterable&& iterable) {
  return make_histogram_with(weight_storage(), std::forward<Iterable>(iterable));
}

/**
  Make histogram from iterator interval and custom storage.
  @param storage Storage or container with standard interface (any vector, array, or map).
  @param begin Iterator to range of axis objects.
  @param end   Iterator to range of axis objects.
*/
template <class Storage, class Iterator,
          class = detail::requires_storage_or_adaptible<Storage>,
          class = detail::requires_iterator<Iterator>>
auto make_histogram_with(Storage&& storage, Iterator begin, Iterator end) {
  using T = std::decay_t<decltype(*begin)>;
  return make_histogram_with(std::forward<Storage>(storage), std::vector<T>(begin, end));
}

/**
  Make histogram from iterator interval and default storage.
  @param begin Iterator to range of axis objects.
  @param end   Iterator to range of axis objects.
*/
template <class Iterator, class = detail::requires_iterator<Iterator>>
auto make_histogram(Iterator begin, Iterator end) {
  return make_histogram_with(default_storage(), begin, end);
}

/**
  Make histogram from iterator interval and weight-counting storage.
  @param begin Iterator to range of axis objects.
  @param end   Iterator to range of axis objects.
*/
template <class Iterator, class = detail::requires_iterator<Iterator>>
auto make_weighted_histogram(Iterator begin, Iterator end) {
  return make_histogram_with(weight_storage(), begin, end);
}

} // namespace histogram
} // namespace boost

#endif

/* make_histogram.hpp
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
*/