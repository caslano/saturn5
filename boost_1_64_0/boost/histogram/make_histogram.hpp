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
rfWS9NXNCH7lZQy/yoUMvdIEB7hRtgADGxXCYAq3+51ct2z3BNnuXmMtgxkHQ56Jdnc2BEeXOH9CEx5ucSo506W1jtHyETL8roYW01dLzqEcjpArHHolLKQBj1x3Orf73VHtfs9Au6+Lbnd6WmfgsR3fWPVxrRvLiwwFJSm9+tqHVm3U25OUPoOUHExK1FhQUV4apinA1okiQTMobi8ZhUjWlzcj5OsNyKy/3iiBTZazP5tyjKfdZZgbdgS+/us7w2EsV5yM9axgE7d7GxYscrWDJQq/H+HFC8DvAjNkp3UEfvvs9tl+ItpZR2lqyGAc08mNmn58gNxOGMvbFJBIGaGfUd/85U9945yyMfDMu0at+wQte7gLTkn0tREKTiuRtcwZiT4QOq3FCeU81aTiz9K9dloMceP5lbLxq1wE0SthPthsU/aldRKxfaHw3h8pXZjhdaLJoB1QEGH1WsvvbudZ8RuiA+1QDmvdSI+lwIffPeE4z6GBA0zFlfPaRuRAQa7fujYYE+YRyj7RiQ/dVNTMD859D2OG60hUtjClgOIea3uil+ezXEfSQB1z7Ddu42nr0Doqk4pi8SHvgjoaXn1kB4M7tI72M1teY14aWserXS9ey2QztI5t8Tc1AyFDa1g7civ1b84FNbye9MHiwGM7Y+/5GFPv0Hqu6n35p9xDQ+s5+YNDZ/GhKFKT2CLr4vk7puGJSp+2Vei1NJZPCtD8HOV3UfnHtG0opKlgyumwXNIF28wom1Bx/FNrCRJeAujlcgve9aHvfNJYvNhl2RRty3nlHKLLZMnjlGNIva2hqejAs4/ymneg5J9u3DuNcTm05PnTnj7OUA8uefEf//Qs95Ys2YC59b5vZaDklKiST1/3yAGmhKElr3Ye+gtjfXDJV73TZ2Zae0Mvt6Ftyqa/7KSlJgkSiIcmc+DpVx7a/aqyjRkkm9ZiVixD92HwwNZSQ/PJld+fKHdUgs12ZZ/GnfXRmsefoz4BxBtP9FDZR6w8OBa963rq/QzqfXxoisPIwL349fCkQm46uhcf2hKU09aNVNSP077yM0brTtGBD82qss/aSbBPefjL1O9Oo44xRh3NH7jzowwqU1jciR6jji/92fYgI2FoHZ89eijMCB5aR8+cB1Yzkw6tY8Z9P7mHiCPwi0dGWSouaM3+VzPPMxsN1BT4zf33VZ6Q9SUVmn7AaB9cH5N3b+DLT2/ePgkWCFrGAPQ+axeGVWY8rqM1DnuJGDQbgu87fPMzRIaoows1IO15lN5NaBfYdQFM3cEmFdHbsfPQ8sUta/pMGtXBhgfLlS7hCAbHKCS4ynjd6eZ153x2nA1cyFVnubHqrFIg0vlrlejlVSmvPBfQyrPgBG6k4JDirVgX///v/7+LrXe/B5Xgi6x3ky9Y7+Y8f+F69+GzR4eud9/YedRY7wb2DKx3r+m6yHr3Q2ePXsF6d3062/8/GQUv69c5Cd7MwfA63aFpLw2GNxUV9p+huHSCN1uHd8m+CLxf3qbDC1W6j/8Z8ILTB4D9ncw7TGANfR84+SlJIXUH78nY+qy+q+gR11qUZV6Vv95iWJ83S+vz40qwILMgCFhuM7FiJN+0LLH5TXTAm2/GmS00JegcPN92WY1zOr9uQxpyN5li4oftDvzgfFI+kt6NX5srmR5cWvNFzl+TpT0c8gI582mGeAccBSltuUeWjpeOPUMfKI5aarItn2ZS3arEevDWYm5Sqe690+1xHFH6Qh+WWp99Zkom9npfPrnMCoMooakcb3McqRtdA/fpbuRzh84Ucen+m670MHn9w3w8enyAXh5g9wbk9uAn0s0BOzOn1XY96f3OCHzC5m1OCh5SyBPCenw=
*/