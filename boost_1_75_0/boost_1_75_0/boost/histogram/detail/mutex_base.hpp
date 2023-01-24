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
od+CubwNqrFGZwCS6nQ31VLzqk6SncttV9xGVxLMjhvmRbf8uLFGAuJIQnBS3XU/aEVyI9zzG3lVGF2eE3ZnSuywao9/opffxI2bXjYEY+RXak+SzptJuYxWbLWug5wOcCwzBZ7vgGvXmzt3BW/0FZcceYq/roQG+bZjRLXpbM2lJCn2P8nyM/o4WZ5MsQEAoxwiMWsnhdUTZgX5VkEBJtKIKb+NLqZbQEWxycgRzL1Cut/InlAzKxaNaXTC8NyQlfbFV+RWa35/o9+uvAorIWGCdronPdRo4YTPIoqiFRzir7OpiAzegAZEnKWMIdIocnCPBO+nj0hesejRUJegYv5vsFcLZd0Fk6aSD6RQLKiwViabqaSPrPHc5yOeIHH+/cxXUc5P+xkoAY/MiXffGZ4GXNZ0QndY6U/BJqGyIvnOwxD8mHadrVoDjNh+fHLBiot11dAd0tCdbBVvEEMoRKT0AmhBu3qgvef726W/pezDBHRuhZt/4ZrdIBEDK/GpRdxEAB4/mG10d3awpPGhVkIvb72gcsZxbsGapGH+lLvSQnPJz+MBw3kzuIHIxr9CfFVSr8EEo8ZChqNBiaVCuKzR5hlEJJ9Ssvaa8o4+6NaLsiWgHc9i9vwBzIc2PMY+Qnup471Csl9lHbfMXJq/Z49yeq212aCV//AVniOUKFD5Hn5y0PsIo3yu8vt5+7n7LcWM6bfdwUwXNkTX
*/