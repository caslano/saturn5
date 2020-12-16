//
// detail/win_event.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_EVENT_HPP
#define BOOST_ASIO_DETAIL_WIN_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_event
  : private noncopyable
{
public:
  // Constructor.
  BOOST_ASIO_DECL win_event();

  // Destructor.
  BOOST_ASIO_DECL ~win_event();

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock& lock)
  {
    this->signal_all(lock);
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ |= 1;
    ::SetEvent(events_[0]);
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    lock.unlock();
    if (have_waiters)
      ::SetEvent(events_[1]);
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    if (state_ > 1)
    {
      lock.unlock();
      ::SetEvent(events_[1]);
      return true;
    }
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    ::ResetEvent(events_[0]);
    state_ &= ~std::size_t(1);
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    while ((state_ & 1) == 0)
    {
      state_ += 2;
      lock.unlock();
#if defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjectsEx(2, events_, false, INFINITE, false);
#else // defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjects(2, events_, false, INFINITE);
#endif // defined(BOOST_ASIO_WINDOWS_APP)
      lock.lock();
      state_ -= 2;
    }
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock& lock, long usec)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    if ((state_ & 1) == 0)
    {
      state_ += 2;
      lock.unlock();
      DWORD msec = usec > 0 ? (usec < 1000 ? 1 : usec / 1000) : 0;
#if defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjectsEx(2, events_, false, msec, false);
#else // defined(BOOST_ASIO_WINDOWS_APP)
      ::WaitForMultipleObjects(2, events_, false, msec);
#endif // defined(BOOST_ASIO_WINDOWS_APP)
      lock.lock();
      state_ -= 2;
    }
    return (state_ & 1) != 0;
  }

private:
  HANDLE events_[2];
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_EVENT_HPP

/* win_event.hpp
/t5TwkTfPyb+Dd4/djh7T5fHRNl7urfl4e893dvyn7739EBMlL2ne1v+S/aebomNvPfR+qzlYe99lDBR9z6K/79076M5c131znWzz0WBzeHn9pzbHme9++G1i4Fw3aRtqrTc+r2StW169mNb7o+eE/ka/rDHq/l2wp8i4ZfXfnayyvYRezb2Z8T+uddpi63gtljbP8+ntkypafue/sS2f0gsdwX06EhpqHYybUtH2GvdJO7t3PMrrBRx40RicXvHe4V1JmvqZrCeZwHyqjuJOFR9lFlXv0Ku9T7ndPi0L0BblKSndVR9YpYdhqum6Jr5RLFfgb7IweRiLme1XC5h35Nr5hfOJnCK5nWrlPHdninIfk4Oe3si5Xu5e72+7ld4QvK3zxtJL9kXEnczuZ920KdE9nlvX3bm3OFp7EkRuYjp1TDsZBa/LM9J1rmcPbnSamHOmy7W+2b2P2o8v5d4cjwpou+vtdb+9XLt49VNJsr13uzyRtrjMAmRx8T/G+8jVn9zXVZ8FM5GFZwVpHtrjVz3Vetc1fM3ztyztuF7I0wf+57EvdTzujXL0Vei6XnF25TVpd9xT5qZuiZZlbin2mtdRe4T0TOyNdY+/8PZ79A5sN/h3Vr0jGiYTY11v0PTEe69Diqzx9E9mLD4WtPGhMn4mzj7MRb/zLSZYTIZyAwIyJwUpt9Nz30O1++me93asharCy0XfNDoDBX9YXIW9GKuc3K6rdsQBumFy6xjj8QfPwndI1EZZY/E8gi6PFeGn/t8dE77f2JOO32g7d7llNZ35zU6uXP80su/OHP5q7FH57QbOqf9tZxhWPsZzbQd/Jk9EOb3APPbOeNYxzI69lodtta3u+51OAF2gj0tXesLR8B0mAMzYBHsDX8K+8BLYV+4Utdu3gH7w426hvNpOBD+Se3Pq92svdzbsl5nOlXVU67GyMlf9LWX9ZSzPqtbrsp5D9J3OMqXMpIzeOXvDOQ66trgzroWuBscC3vAs2AvdR+ha4QnwkmwAp6ra+kma/meB/8ML4BtPYFwJ8ACOAqW2uFhGZwGy+FcXQtcCWfDy+EceD2cC9fAqXAjzIEvw1y4HS6AH8KL4dfwZ9Cva4GT4SWwt675PQneoGuDfwvPgGvgOHgjPAfeBKfCm2ExXALn6Rrin+ka4tvgFfBueCW8D/4aPgivh0/p9d6BhXA3nA4/hTNgU+5DMWwOq+COen5bWfHR0e8q/87vKv/p9XdHv638a7+tHF2T98/5vrKQA36rMDWY3Zj4s1hXh8k+6+h3lqN/R/+O/h39O/p39O/o39G//9e/f9/3/4KC2f+E7/8dWds+uA3zKD/EMoc7Kmso0RbOmTMxr3RGobP8v6vKrAyVGT87IJVfpHsEnLisH0PkhhWVFeermImrPFTmjLyZxSUL9IJOXDVM4uwKkjudpfc/mcPS+8KZtpSsXdjbyzI6qXZHWfufeqd8owuLpNZ1/6cHrfvnL/q6/4Xudf+y6X3fQ3LN8EIw+yBKkkPWoiPf8H0QxOXaB7HfG7ksatZFStfh7YPI5J5EK4/cCHsTFlEeqQ9Huu5h7YNwfWdeGaM693StynDMLsoiS68VVrnyZ5YHvrO+HSj7nKDvsRqmbZD/NOM/xvgfL/duqFx9mvGbJX4JQefHyKXMN8AV4h9vziFapfImrqB6UCx+7WpbOxLyDfvtwL3PMd+wjZukP+TepMW6701hK+pE5PIydTW/VUhdRf6w6uro4LpKXK66WhUbua5uXRcpXYdXV6trqav+OHd5LLaf3YjlcWR1dWtjcUezPvPPMAMutZ+LR+RarkaVGiRl30vbiRZS9o78W8wTj9Tz7DzWY+L2W08=
*/