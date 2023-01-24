//
// detail/win_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_MUTEX_HPP
#define BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<win_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL win_mutex();

  // Destructor.
  ~win_mutex()
  {
    ::DeleteCriticalSection(&crit_section_);
  }

  // Lock the mutex.
  void lock()
  {
    ::EnterCriticalSection(&crit_section_);
  }

  // Unlock the mutex.
  void unlock()
  {
    ::LeaveCriticalSection(&crit_section_);
  }

private:
  // Initialisation must be performed in a separate function to the constructor
  // since the compiler does not support the use of structured exceptions and
  // C++ exceptions in the same function.
  BOOST_ASIO_DECL int do_init();

  ::CRITICAL_SECTION crit_section_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_MUTEX_HPP

/* win_mutex.hpp
pe7xKUX6pAqzy1W6B8NzbN+Ou+05iHR1vCvHagM59nAxWM8/zaX7Kmn9MFiZywm4HyfSo8C30Fo5u9GBcZPCzimQ3Ca7pm4QnQ2zDxjW3kg/cBvPlXE5D1htY1qeSW41CZSjZleCUbg8GhLpe1Au2BdAiJ7mxwqJ8EwyoIc6qgX8li++LhxW4PYJpoefjbvOOQ3MlgqJ1h1rRgK9gbqCPJPewkpwy1AciMYc8j1H1OxdatIXNL7GoKMFQf8tirYEfguNw4bL7IgmyQzjU4oME1vlFZdtiDSlK6alpNeDfu1kLd/T2KGgtBslOO5Jrtm1vstP6xQR1n5nE2INLvHUJ4//TMVEs2y6VkPx7KQqQbnxKHE2a3z8W7CTgs9sSi1ATdtStUkhx16HP9B+zcA+WwapK7+jt2baCgx1nml0Pozn0zuYh/hfHwj0+4eBcBCZNQ7Jjca92S0aJV8rb+VMOXLZ3+NSv55CsHcCe9LsMNZUsHCyCE3FMvKWbvBu0VRMpz/GoPnqt7VRnAMrX289pTGBw8MXV6lZYC6Z7zLsj5bEVXSl4r4AKd7KuZrIq/TH1EURwGnijr85iyFjY2auQwiHj2+J13OeOVfj8yVwPdal/fH6ePbGBMzVsfM5FPc9X7YnssQaySp2Shk4uT85p7BfETainWMdsn9C4rY0/GH2BtImucfJL7O6oco/Q8bzVif5NtVIqHpluNOz
*/