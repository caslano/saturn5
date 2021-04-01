// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_MAKE_PROFILE_HPP
#define BOOST_HISTOGRAM_MAKE_PROFILE_HPP

#include <boost/histogram/accumulators/mean.hpp>
#include <boost/histogram/accumulators/weighted_mean.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/make_histogram.hpp>

/**
  \file boost/histogram/make_profile.hpp
  Collection of factory functions to conveniently create profiles.

  Profiles are histograms which accept an additional sample and compute the mean of the
  sample in each cell.
*/

namespace boost {
namespace histogram {

/**
  Make profle from compile-time axis configuration.
  @param axis First axis instance.
  @param axes Other axis instances.
*/
template <class Axis, class... Axes, class = detail::requires_axis<Axis>>
auto make_profile(Axis&& axis, Axes&&... axes) {
  return make_histogram_with(profile_storage(), std::forward<Axis>(axis),
                             std::forward<Axes>(axes)...);
}

/**
  Make profle from compile-time axis configuration which accepts weights.
  @param axis First axis instance.
  @param axes Other axis instances.
*/
template <class Axis, class... Axes, class = detail::requires_axis<Axis>>
auto make_weighted_profile(Axis&& axis, Axes&&... axes) {
  return make_histogram_with(weighted_profile_storage(), std::forward<Axis>(axis),
                             std::forward<Axes>(axes)...);
}

/**
  Make profile from iterable range.
  @param iterable Iterable range of axis objects.
*/
template <class Iterable, class = detail::requires_sequence_of_any_axis<Iterable>>
auto make_profile(Iterable&& iterable) {
  return make_histogram_with(profile_storage(), std::forward<Iterable>(iterable));
}

/**
  Make profile from iterable range which accepts weights.
  @param iterable Iterable range of axis objects.
*/
template <class Iterable, class = detail::requires_sequence_of_any_axis<Iterable>>
auto make_weighted_profile(Iterable&& iterable) {
  return make_histogram_with(weighted_profile_storage(),
                             std::forward<Iterable>(iterable));
}

/**
  Make profile from iterator interval.
  @param begin Iterator to range of axis objects.
  @param end   Iterator to range of axis objects.
*/
template <class Iterator, class = detail::requires_iterator<Iterator>>
auto make_profile(Iterator begin, Iterator end) {
  return make_histogram_with(profile_storage(), begin, end);
}

/**
  Make profile from iterator interval which accepts weights.
  @param begin Iterator to range of axis objects.
  @param end   Iterator to range of axis objects.
*/
template <class Iterator, class = detail::requires_iterator<Iterator>>
auto make_weighted_profile(Iterator begin, Iterator end) {
  return make_histogram_with(weighted_profile_storage(), begin, end);
}

} // namespace histogram
} // namespace boost

#endif

/* make_profile.hpp
/45flyisXguKB7Q+zf6eQZ13QulKh1fZqaaEPyAr9cmph7GjYatu7w82xcEoseyvcAOHyw4ySSPBlfRLSBAYM4YOyRlSCTmgEcbvjBRsvbsPsvHOVZDt0pdG9IRrkNSGGdnmQ0XEOUwEySk061trOqoR18preKXxyF3NRk8qYto6wEiDjLcQPOfKxw+DjPIfkxXQVOmMr0mC4mfy5PpIpE03nBySxsHbTK9APWxEiOZP6Ltx+AawYjVxQ/X/yFgR5KdUDflyWVkgneECwEHkc+k0qKNtOyT9SzfcuHp57vZq9jbw0erEN6J6tBgD/JrXM4yduB4axo8SlsqTL/gyScunzoiBRYfUjUIjL4sIUxoG+nt5Gxs6U1AhP0eO6WxUGPlx/hMjt6BMBgGIXT4rgVPeUUTGYvFmcXEPTiHZUgux1wuB9zKq4k0m1jZXFXpRAC4hoZJv0HQezdpkq2zul9Ufoq2VGiMYnF+Roiq3IfMzyPO7ZyNI8b0REq+T6EFb/xYu2+pFmzYCymmJouE3qhKBy+vn93CzSxIY8prl/h87VzpFemvrs0e0pg==
*/