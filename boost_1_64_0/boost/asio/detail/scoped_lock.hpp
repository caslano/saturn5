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
gzwrAHMn1V2AptyQIqRigGKNVNa3yybEp/GO+6TCHDxKb2OJkKNYmlglNA852Gv2f4jRSaR3LNF3S/iDKEIZxOdX/GUAnHz6mN6MioDbzHn7fTDpbn5NCZzLA+2cPqqRUWfhkae7oljmK1kRp5ctbdsdMXcqlnrQD2FANd6Twf+yvCN04JzHjyIjgQv2hhU5+hNlCMOkBsophUdquT4ear6wBUUw8zC8z2C/GJdHxErAyGCtG706Gr/VA5ekGlgpJLvKSLqLa7T+LTG9VL4m5fD8dldq2F8VNmLz9BZtlTOWaZnBZeahONiiZU/d20BOetOzY2kql0AyCGppZ8FTortPYbLJxcYZCDqdVwF4OjWMVUhTuAPyjKK39AWr10f07emgi3ty5DeTxoYhjwfEwX8Pnxtm/Mycykxx1ZSm5PwY/Hl28J1hNJRT50OKqa9M/LCf2IuXfIcV/TI5y0ZuAeiK1wJoBo1JDr0cV6wh7Q60jp/+/OQ4S7JkY1qvaJQDd3Y0cP5Q0r53sxsJUdp2y1w1kCqwBUtMzkvom1AUfKEkzXQpPnlTo8LuMQ==
*/