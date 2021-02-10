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
97772KZSSFGvnBN2k+dca6YO4L9968EQG4RHlDtzPrIdA8O10bBfc0yqrg6tl0Z/8M9JWGvFiya3+eimMnbfNlCsGnUsfK7E1gAegTWeWNj2X3s9+GuJ1dm8X4gSy309J/4iDPpZHIeLkESjhf/4uEA5DIPRV68DMEfLpnaN4T80vvl6Y1FfYenNf0PbH1AYfvjwegoXxi9QuIR9icLI//h6ChfGL1C4hG0puD49+ov4IVl8+XLf+x/DOK1YbmeAgdU4nGTYygv18TwbXZbjTVlVzsudFK0QrNH5dNkJLZaVG+tWWRdqwRu7cNew1fgZ+Dhw3kmllo3T6ffnCK8039u7GQcRKzSgw1l0Pb8oQltz3OpTPHvp9fwXXLLfeCGMThV1tf4XUEsDBAoAAAAIAC1nSlJ3LSnUHQQAAAEJAAAdAAkAY3VybC1tYXN0ZXIvbTQveno2MC14Yy1vdnIubTRVVAUAAbZIJGCtVV1v2zYUffevuGj2kACKkaZdt4dhGCPTNjFZTCU5WWsUgixRNlFZ9Cgqjvvre0lZdlI0w4Y1D7EtnnPuuV/U2eWP+xucDc7gy5d3V5eP+aV60MPNW/fIV9u9lqu1gfP8Aq6vXr+BS/y4vvJglNVSVBAbUS+FXsFvhXvwxzp7fBw2
*/