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
KsUUONnQfyRLWoFlZCbrpGE96zSMQ/HLGZgj55dz+ESzW90KdTpSn+UP542kYT1pcUz6Ploy2Vz4m+orRvlK+p/wnmFLrfYpoW+/RtQISq4O9UPBjC/i5LnxJ8cdcj51NFwZ+rRMUYb1e7eRosrNMaHEpwz6dfKdEzLs26OhcDIXpe1gv5FFNAnx44vPRDsq+SakYqNR+bHyLdmXr/hm6nac8q/Ckz7GiWY2bR1vmLamr9dQ9maZGen6kn0fUMROfEF+IytyITcyQg9CXf1zKM/j3P3z6Y8abl3vAGs3PPfw22gi5Yp+j+xIY3d7I275/MwYe11seD9xEBsgcOMuMD7K2/4bvvwO+8UcEjyy38hfd5PMTz48wmP+iPSsiDg0/QtG+ocLBtV3mwHJNRKSq1GOPfKPVN3YWRoSTL0oYOgX0olxipEM0fN11zScYpBGGYW4wz2s4dTsBngyFwIzB5X2HOKvyFabcR87D8CRjngChrF3tdGgaTFQM06ixm64Manh1sC1XQSMuc2XK78+30DPeIme0azdYfyTBeouwLSL4cf4Wn+NkYlBCVlfIFjtpNDEV3Fy25YmOU4GbHGemaEPtnI7IAqQeyTVXwm8JjecYgjsxmUvide+pItVK3as3g29+ZrK0PWueL7XR/88EDu7+ca3aL68Su+b/sgsH4CKZ/T4TUQFHHzBCNo4uJ+DF6nIewvDzP45iBJ/4IJMjciFy6dfvYExAzHczr78OECRL0QibX4EZOR+Gcnl+znUPBz+rPGQT3LZ8UxChpM9D/d837UI29iNMffjxfqBDMjaPLSt+6NbWbTMG56GHmqxPBJCcazwaeP6orOxzt4VhHtnYKoUHfbg2soV5L9cuCZ62AidPnw0ogI5ippCCPjhLYyAi7Xf8D/8uUPR861supiLMd+NrWndCTGx5Sy2qEiW3lnuQeCQUJ0DzcTcPTDn0+oN25dUk+VgM8ow/JXPrK4Mbxa0j5xVHOM9RPbvs4oxxbFkFdOcRxzJKoY4tguU6G2xe6EkYSJRVt+mWxBOJjZWYVNsVFxfHdVwT1QNRSifZSXVYaU2xqEKDS2gMvzFMahNw3d/Ik4i/Fwtgnn+CrPAuowBQNjlr7CIaQSFH7DoQPgrbART/feojffSDaBylNrqCKLmdKZnfs1YH2u8Zq5XjFenaOZnUqA4lg1UBh0hHR80mdJBhnIHj8+5baq3GZ9YW43OkfsbkxLZQqstcXKiz3YDvfs4KkPpzt2oesnmdWOFidDTWKWYJpfH0bvdVx4XpgIErWf7fVUmGg8yKcvS+Y0VsXryWCSP5eS2uEGpY/Hm5NTvbaxQ9NQKUit64VyhrypOwdzQe9Ku3l9Al4es3g1KXxzu0/WZXOigZZleNNwObOJptwOf6BJ1tVk3vKf7gC7vP8q+l1HM0gkEgWNnIMn0pJ0w2N5oHh24w+QrCHt7cYeEJjj6taGx/Uf/9R6b396f9D+k4pAQJJpBbJVO99wWgaLYNGU6XyPynidWapWEbhdtjq2OFp7FJT1tJkrpF+aEwO1mLf+svyjxrLfPVH+QVjseD4iqjDQtxHbvQYyDRM6kxuVtI6q2m+p/R5UdpiL2iQ7HHkcXaTdpG/iuOc1QHXsQYX+aiJpfk59WjNcU5rfc1qV3izoQakpGo+2ayVafDd1HnArS6cztXupuLM8AQdpNvvJ4E3Usx74PsbGIjUUskVkKx45HrIJYBbFEU7R+A0Es+VbfpGiaAomMf5ooI2DLcWx37Giktpt8+WFq9+GBdqO5aPZ5qPuj7UR3bdx2Mk6cKM365qj22Hlz1FExd+J8P+lfQkZ8uicXiSUZ6EBc7MJVRjRmVaI=
*/