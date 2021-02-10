//
// detail/null_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<null_mutex> scoped_lock;

  // Constructor.
  null_mutex()
  {
  }

  // Destructor.
  ~null_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

/* null_mutex.hpp
owQTI7uBsApnJmgaKMVTNm0w2CeDfXI4QGQGKrBMOyvTkqEn6nuFgxFo+PUuWlcB1QcYcnlQ7KyFH5+cX16ffuXrXvyuXEBl69jMFToUgefsEf06oUrX5TUZOT76hKPXSrydB1gFup6y62mWFC4iCHyHq4dkal8Z1PRjWkRAV7GA9/RXrU6eoTjYwHJRqORFWa4VAnT/S9qwbULPYbqDw10y3e9EbEDSzRzB5/bBLKvedSFzU4rd7qzpyVsRVPLaNDjZxHIs3EzGUt+D2TgfDInzPLqHy5agH2Z6VAUeyWiUzYA4Il1Wd7WKlLLCmuS4oYNEJCkM0bOJe/1LDtnc2YTJ8nIeNFHvKiHFUBrjcbaI0xxKA8Qdr47q2hEwhvm5514Kar8QSSplc3rDEdKFaclnmMzqQm9FSpKVdvEW7G5SCtw+J5N59rCpaMd3WdiYr8vx+Lb52iezpgo/mJXUYh+2Gw1X+nWH7er847WqTO6Jeo6fG7zjJaEXdfhORSpImjDZ3ZeTFKOr3Ajw4citdG+gFm16XjE4Rhq1Gzsf1hBvVmxjQvAEZ3rxWaPEviyahCoG9lhELbDMiOY/2kkh3U7LeUHzcTByIBB2PJJPsgTMAgR8xRjnzBaJhWFo7B0pQRgbAcTLZTfIuuhm
*/