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
TTDxh8GdmzOaYO3S4Z81JzXBtOVtt4NGN4G1YVRJrWQTvFuhuUv6VyOsNV2GSfEaoXux+PHi8kbQyQyI9slrhMCmdcdoqY2g2rL7ps2HRlDW0M29H9oIbcsNBsLuN0KGcU/FtauNMFPm7npDn0ZId3kqUefaCLRK6y+GBxthxCYNr+sWjUD2KmSHbW4EoyvLz95d3giHjAPs9sxvBMOW6jVi6o0wnozOsVdoBK304xlRIxrBa972nvxfDTB1ppZ8SgN6XrCvFZ3/1gAbovKlZmQ0wM2L5UbXPjaA9dSVHoUvG6CwftZ83p0GaLHXxQvONwA9PXv2ZfScefPwTPaUgw0gTwTkeZs3gNv3oJq361C++ZfeRmk3wPyZCQ0XZjbAB7dc5iL0nEoVe7g4bFgDrDq59l73z3qwWyA9enRlPbSkrdboyaqHY1NdroRF10PjIrPzNffr4Xwe6TbHox4kyjUuPDWuB/9tZnammvWweLPt/QVS9WBz19Jlyfc6WNmDT7d7Uwers52fJ5+pAzXRp99Y2+uAJ7HMLEOrDpI3PrnsIFEHeTYx7+fk18LY/vWJ7Y9r4cyp6oOxjrWwdu2T6Rd1a8GrzXrCNjn0PH/2cIpKWQ20XAtOynpeAye/us+3dqwBJaWBxTU6NYAt2LKQHF4DU098ULHKrIbd02dYG1+tBpflOqOGb62Gy4+79h+eVA15etiak6U/QDcy
*/