// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_NOOP_MUTEX_HPP
#define BOOST_HISTOGRAM_DETAIL_NOOP_MUTEX_HPP

#include <boost/core/empty_value.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/mp11/utility.hpp> // mp_if
#include <mutex>

namespace boost {
namespace histogram {
namespace detail {

struct null_mutex {
  bool try_lock() noexcept { return true; }
  void lock() noexcept {}
  void unlock() noexcept {}
};

template <class Axes, class Storage,
          class DetailMutex = mp11::mp_if_c<(Storage::has_threading_support &&
                                             detail::has_growing_axis<Axes>::value),
                                            std::mutex, detail::null_mutex>>
struct mutex_base : empty_value<DetailMutex> {
  mutex_base() = default;
  // do not copy or move mutex
  mutex_base(const mutex_base&) : empty_value<DetailMutex>() {}
  // do not copy or move mutex
  mutex_base& operator=(const mutex_base&) { return *this; }
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* mutex_base.hpp
1HyvKojLiVJYa9Fh1xuwAprgdZwqMsYgYHSeD94o54MF4pOVaj4o60BfaDOUK07hwGhF4znubFqXyNkk9nQOL+H4ZU321VV0ffYQowy+nlQGG+Zz7lrXvPDv95HjY7iPMN8kXT5EzeSQO3I4BbO+lHCO2u/6g1w6kLfAyQX5xrNrK6z/WAO3NPeHR+97Oq/GcvshWGMn/E2E7+0ef1NH/MDqrfpS/JBQt/gE74wv/rCu+9VHwH/frKe3f1G36RG8sRO++NwHp3eLTM/4ir+wzKg0Aps6w5sUXPHbCf7djvDfd47/mY5wpq+O5D62rvORXKZvwNd3giv6Cj6/E1zRV/DJXeByxiQe83dXmEb/uQt1J9d1n+VF6RU5JrhhsNATrZg28ZMDT0/zkxNPv+CnbDx938JXvD83lZYQxDP44Xt7HpcPDvEj+eAU35QP2WJLJVAFuQ52Woxl2XT5SFTaU/iRyJyQj0RHpEjfTlg2o/VdcdWdypX+gOA1gcefx7r7rYFvcJN3ndR3TJyE+PX5xmUKwWFdEBdIROrGgyZe+hXfbeAqpH51ULCUY/CgmohU1jlSrrg7OdIYGWlVh0ipMpIX2KDiEbdO4Ri0eRPZGW/J43w5cBsOh9s4Y7WS3xWJVDbN41REHWZ1bk7ntVVqwrBRTJChudy9NhmAR7zEqof3SI7coFZVo0ZovshTzNhX34WulCA59NV3nsumGGqKWwdT2WIR3SMmX2/ASgDziPuTCvx2mYF7ExmI38bokRX5qNRrzCRGBXjK56ciPA3Ak1g5V2XPtMpQ3F5uB2kPiNJGPlYBvnODQfkpgLAMz3n5JIJVAd4j6S9L0F8h6YtLJIVcj/j6SoPCok4UxiUozGAKBUwh3aAwKEBDqySyPEFkwG2qrnOYRPVtRvE6OJ0i3IY0WSVSGLhfJeI6GaxvzQwW8AvEIlipJ6rr6E6PGIU9A+ZiqHzIFgXyIVcMlg8Foh8evOLF8fJKmKbZuA+GOobgQE6Xt6dUunfdalwzfwEO5//LP3I/zCFqPt79CMPz4/jiyWL0CPRp1aWkjh1ua66ebMKnF3Ua0erSOY0d8bXqybSI4ha2D4lEHbpPLB8qJ2Ycoy9wL19B3ji32oChb/jSzPxD+ed1DtxnoVXkd7ff58C+QZR+Kh3xwx8KzzwL3HYWuLUz3PD/gq4cnil4vZMCTD7c6GgXXyuTSyXh1DmzYU3yjsfvEwOX0drGVaMAocP5+6gBHQgPCtYHxPO8X7xWSvXDH5eKb0+a1dU5gVPmkx0vGrfYglDdNTyU/DWIwtED6/GkUvDrKWwlDneikaAcJ2g12TRBdIu3VqrRZ7hc49TuYE/27E6eSBxzMQIuHnXT6zMSH4uUw+kB27NYntEvk+vJyx8to1CzQSttaYo4yMWXlGs12EjP9pFTYw86o7/O59ZdgWilogT0ULoQngIkMSjwbZWJoEXl4MGbpeKb7hYPSOsvn1gykh/K3gml+8QvKuVLnTOU7hF/lN02VVndzDmzL2S56B/+qPb2Cum7m9LAzsORP6bhAthTlu7YUfM/cO5xHfCOhBE8VBMEkYkbKQu0V4nQXPtq2rDkHR2feGUpydBfRuA/qyq/159yxIsjuHKi0iTsY+Jd2gjlwU4s/ZQaTMeJ1xFM4sq2NF4xxwAV+BgZsFyvWFOtBtrePjnSiuvncpC2zyeOjJClDee3PPeh3aF/vP+lVWuRspxVsZ9Mxo8QhdW8k3MgdAv2Iedir2CW66S8SnjnS4fXQB8LZSFO1kw1GI2GS6DcZQdpPKGvRzTejdL1y6we5TGL1jz6+cXPgwAIy5ykvZRGv/gKQr2i+EaC/XU2l8yFb2g=
*/