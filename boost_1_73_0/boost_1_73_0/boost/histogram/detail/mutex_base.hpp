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
bwCPxa2AYx4SqpqPR74JPY3SItt3gb7q34BeAriVfdAS+p/OPvLVdPciftcCmg/Aq29+gg9sRe94vfxjNKP7eXgNvUQCw6EA2Kkl7eZ/UFM6ASpq0OzUnFcVaeSjPUac8qr6Mgj6eIk0erfyS+UZaKeXRQr8LsLiY8hjUufKRR6ct4Guq6H3/eDUuxxM55cTigVRewLSMbiNSbl6/VUMvEz8ijSCXlHJzlO5GtrZOMYBXs16RyOSO9HrCdXaeH3GUe7KeZZjA8Y0hD6W7MWdyW5+i8C/hvaEHvX9TVuEjQXCNkgsQavzTgOzH5xMUjSYpM4jdyDCfwNQSwMECgAAAAgALWdKUr2S1OhlBAAAAhUAACYACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy9PUzQwMC9jY3NpZGN1cmwuaFVUBQABtkgkYNVXwW7jNhC9+ysGySUxVHu7p267KBo4m67RrhPECbYBAhC0RFlsKVIgKScu8vGdoeVYduzYcpxDlViiKM6bN2+GFHUsU52IFHq313/2Bz3W6w3753TDvraO8YHUYu2zbvtwRwvasPVg4cfwwGuwuLLmbxH79aMZe4LZH1rd43Wbky4sTJ7YKWw3eYKTYMIqL5+pzdg2R/fEjU5dsrxn1MQeNCPLnimm
*/