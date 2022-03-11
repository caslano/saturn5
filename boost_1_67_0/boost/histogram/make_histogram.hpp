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