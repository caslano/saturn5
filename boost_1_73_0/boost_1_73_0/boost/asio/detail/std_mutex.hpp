//
// detail/std_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <mutex>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event;

class std_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_mutex> scoped_lock;

  // Constructor.
  std_mutex()
  {
  }

  // Destructor.
  ~std_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
    mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    mutex_.unlock();
  }

private:
  friend class std_event;
  std::mutex mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_MUTEX_HPP

/* std_mutex.hpp
idNQhG94hn0+bhnYclo6C55egb0ENeWnSJEEHluYMaC4bBoMaYjMEyUw4o+vEks8bSe9hDuTvoNbaNbEyYfLOP1aiQNdgR01lPiIYpe9vbqO+QJys0BuY8TCPHJjQmQiClBo/ryAUnTKz+FQIamKZNrsz49k2p7gaNKO0NPAPUfT6XtA02k7JSw1x4N3BM/H0B6OR8EJnZ94PZo2+QlfNuERX1g36xoRIRTUjLtPnjl4Pj8CjQZEvMJzmkIXNJwa+jkVq9NN96qe6pW7vv2S85BIoT23SSSRlXtjizOkcdZK4d31YlcT5wTOn9NhIEC+Q2fEff7kF/Z7Z2IvW7yAmmbemxGlOYGNd4YeBey2iTkWGtQ25MXMuwMtDP7o37OEparZAWPh9w4TkePkW4GPdQQ84XRG7VJZb4+0NAdrTRy9nkI3RNxS5+KDuyfh9UgcF6rSA3DEIz4nXH+Y/xEfEwFNOsX5fHQ1JmGwNWbFyCSjO13/HY1L4cfzSDwQxJz1OZ9d6ge0ck60Eivvi6TByrEiEupCiObd2X5awEt9GLFiowI6i/O5IhwJmlrtzmwhhTEHipmKng11YMpAWZ6mtYE8MJ8edzfkRPy+jfR6TOTE/f6IQzM/HdQj3LXh5QQ/vWboS2CaT33e8hJ3
*/