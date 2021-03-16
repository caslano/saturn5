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
7En+UFxtgJHJID8MCq/LM5uHTVLG50bUwpA0h5u7z8FoJ7KXkHpFEs0wA4PPKQUXzkA6mmKaAfLKSve0/mJN0UsQEFIrWRrilITw9IMGe86ktEA43JSIFPRLg0EWBfkEIi6kG0gzN3UwZtEPDV8LlRi/4lfceErBqhCqGLBHSOFvTWB5IQHJen1NsxZrLU6JT2HuZO5J8Nt8O/Om31gXaPEarhLOmTCkpyenaoSqaGWyCRaUr3lZ5LifHlD4Cag=
*/