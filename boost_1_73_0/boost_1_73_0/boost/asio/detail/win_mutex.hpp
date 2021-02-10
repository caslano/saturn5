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
790Hx7XDwCmg73vQZJxBm9042ezJ5nR1lywmXqJ2eB8vbmBuKKp0KJC/sGaRwO4YAocOb+3htT24noyvkh97Kiyqa5rGfSrvcU99ZMroZVmoGtwoJY7PGG6bKYLcE4oJhuH0Mp4GRHpUu+ro/ju2GMtdZjXItP94SZYlwv8yy7wsW9rPJeE+x4gvdlvi5PNjNQ4VMSsoRrkrzscRWbaSpDDBJHW9g0sFsExJyVfUnuwCT7RFQ20AhbKS6vzNrfsBUEsDBAoAAAAIAC1nSlLQLq9jywAAAEMBAAAvAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZnRwLXNzbC1jb250cm9sLmRVVAUAAbZIJGB9jjFOBDEMRfucwh0NGaABaboV0mqLKVbMXiAkzhDJioPtgOb2zI60VIjS1n///YnrMkK25lXJR64mTO6E1EZ4w89eBGGep4fLNENmgePlDMRLqfcQCYPsT5NQNaO4s7BxZNLxGnSHlDCN8DI8PQ+P7jUYLizrrgMjdd5795fEPvB/0QBwIOJvBcXYBV3oG1OtxGCFN+S9G1SuHmuUtRkmSMHCL697G+ZcYtki69Z3DIX0ana3EJS8L1GUr+1KjFrvDLS3xmK3wYP7AVBLAwQKAAAACAAt
*/