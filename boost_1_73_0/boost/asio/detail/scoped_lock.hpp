//
// detail/scoped_lock.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP
#define BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to lock and unlock a mutex automatically.
template <typename Mutex>
class scoped_lock
  : private noncopyable
{
public:
  // Tag type used to distinguish constructors.
  enum adopt_lock_t { adopt_lock };

  // Constructor adopts a lock that is already held.
  scoped_lock(Mutex& m, adopt_lock_t)
    : mutex_(m),
      locked_(true)
  {
  }

  // Constructor acquires the lock.
  explicit scoped_lock(Mutex& m)
    : mutex_(m)
  {
    mutex_.lock();
    locked_ = true;
  }

  // Destructor releases the lock.
  ~scoped_lock()
  {
    if (locked_)
      mutex_.unlock();
  }

  // Explicitly acquire the lock.
  void lock()
  {
    if (!locked_)
    {
      mutex_.lock();
      locked_ = true;
    }
  }

  // Explicitly release the lock.
  void unlock()
  {
    if (locked_)
    {
      mutex_.unlock();
      locked_ = false;
    }
  }

  // Test whether the lock is held.
  bool locked() const
  {
    return locked_;
  }

  // Get the underlying mutex.
  Mutex& mutex()
  {
    return mutex_;
  }

private:
  // The underlying mutex.
  Mutex& mutex_;

  // Whether the mutex is currently locked or unlocked.
  bool locked_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

/* scoped_lock.hpp
J4XhnIvusJRxf9k9+Rss7YqoouGya7gxQVlOXb21RgluanlNVC9AiIYXDJDjpBg3l3QGZrJ/2j7Pfz/whIbbHzx/QEEZU7JISsyRsmbMwsZKin9SSoU+mkNiylFKhQIL6mrqk2r1X1l61Me3dAelfIsPE9Qpspq4qkL9uGGi1YMtkakCOq0P0OoahayynomXvI9YD0qsoSfGimrpd/VgsCLlFCFjhqZdOUAEfMMKD1Kbbjg4
*/