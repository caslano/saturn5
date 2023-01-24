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
ci/tUp7GNTbeOmcRW8bqH/UhL90aPnqiutVXoTJAuTaLaolhhm/pHZeUJ3JB/w0SS6QfHVhD4jr6tEy1s4VkjwnuZdsxkbdCB90y7bpwxdmmwM1XJH3Cz9G5aVw/55KcPrZ0MVQPFM1/rv8UzdyKw5ygLctY5Mlye1wBAsHvZKOX91e7jtKSN+O7l72Wb3jONmERO/+S/DhPkK4VgyiVdfX0gxUHebkS7fI7bosG8GTp+JM7uOJ88SrzTPcqy2yFiceAQSIz5nQSc094n3NoUKF9k1Q6exn1O7//Ss/RdIztELdByln4NI0XyqYo377MXY+W4XQfY1mqIzX9tnSDktYJkUyk8cp+fphyS7k9H+O2tA+LOTLiwCgXbZIyQ37a9RfboTQ96emRIG96Y/79zklu8YzMKRJrhQGuQtE4NYYZPRXLffbyd1qvGV671dess8tpFqwaL5TIfFSiL+zG+mgU3X3o2PIjm/fNUXcW/KiY1UaTOxu2UVyo24YDm+YQLmr3zZ3ti3ADxgw0rujMnZb4d6aoPqG+Mr5OPnJw+NZIVv0i5XUEfxMwMPwlYOBG+1PAsPCXgAF1xvz799ZBB/XzddzO4Btm4jr890jcbK5wCRqJ9Q7471emDZrtnliKNduFOCkumay/sAyYYn1VKY0pzUO1WAo/9TXcAGHPXeo9+RoNejvTl8tX8EHdzo0vPLZ1XkQzequUOM5I
*/