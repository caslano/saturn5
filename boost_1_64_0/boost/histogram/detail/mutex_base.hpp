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
59efvBo0oYPLpk6mlSwHQuwzrq9Zim3yYe9QR+g2M6j1jwl5HzwxYMX89yJsn4TwwPs2lVg0BjxO63PeC1j2KN/ovUOPBjC5KvVLW6rYFLcmuNGTOCUmwWw5FiVVRUVEqGVMtUdqde2dSQDb9CLefKE1haWRwCLu5rmh4c/Yx4jUtbDarZTdjxkDSlXbfVOJmZpp79qXSz68+FlDOFdCS1TzR6dgnMrH2reDiCeIzYwzCGGqStGCN7Z4R55nn/keiq3Vk7y2AeTZXyshvRc4UXsReKixnsNqVanakToVkJ1ov9gLsU9LaTFqcWMlIdU5bNQLwQapOLZqck6FfaRkDNhLuuNqNouCTSsPb52jVdKRKWbgNzIh3jVVf6qZJnN8jlUA9e4WU81dmaOYC5DH0zgddYr75mnUaCxrlsCBKD2mDbivoP3Mxag4mlsuiW+YT1wXdjIB0HOHnJt2K4b4aG4MgF6ltna9kS/HfybqJ7+zanXyp1Np040BLbhp1TkZNdmEtkk8pt1G18vm8sIm5GMuIfAVSDCm45wLSX5rXn2kf1CVpT2zTJsG4A==
*/