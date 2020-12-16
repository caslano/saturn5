//
// detail/std_event.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_EVENT_HPP
#define BOOST_ASIO_DETAIL_STD_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <chrono>
#include <condition_variable>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event
  : private noncopyable
{
public:
  // Constructor.
  std_event()
    : state_(0)
  {
  }

  // Destructor.
  ~std_event()
  {
  }

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
    cond_.notify_all();
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
      cond_.notify_one();
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
      cond_.notify_one();
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
    state_ &= ~std::size_t(1);
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    unique_lock_adapter u_lock(lock);
    while ((state_ & 1) == 0)
    {
      waiter w(state_);
      cond_.wait(u_lock.unique_lock_);
    }
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock& lock, long usec)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    unique_lock_adapter u_lock(lock);
    if ((state_ & 1) == 0)
    {
      waiter w(state_);
      cond_.wait_for(u_lock.unique_lock_, std::chrono::microseconds(usec));
    }
    return (state_ & 1) != 0;
  }

private:
  // Helper class to temporarily adapt a scoped_lock into a unique_lock so that
  // it can be passed to std::condition_variable::wait().
  struct unique_lock_adapter
  {
    template <typename Lock>
    explicit unique_lock_adapter(Lock& lock)
      : unique_lock_(lock.mutex().mutex_, std::adopt_lock)
    {
    }

    ~unique_lock_adapter()
    {
      unique_lock_.release();
    }

    std::unique_lock<std::mutex> unique_lock_;
  };

  // Helper to increment and decrement the state to track outstanding waiters.
  class waiter
  {
  public:
    explicit waiter(std::size_t& state)
      : state_(state)
    {
      state_ += 2;
    }

    ~waiter()
    {
      state_ -= 2;
    }

  private:
    std::size_t& state_;
  };

  std::condition_variable cond_;
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_EVENT_HPP

/* std_event.hpp
aiOX7Z6dYc8FsXIdPGm9SmeU3QQ7626WvtKfC9fqTLRboEmvW+Ed8DZ4F7wd3g/vgJvgnfB9+Ct4wMQf1tPdLFm6m2WQ7mbJ090sFfBBWAUfhhfDX8MVcCv8CXwKboZPw1fgNvga/C18Bz4DP7T5i7/w9/Az3fnSmng/B7Pg8/B4+AIcB3fCAvgSLIQvQ51Np3MMSEOfs+ne0tl0+4y78G3dkfOO566VDbI/Rva9d63Mk/1K2AhW6Yy7BbqrYb7uaLgA9tXzE3RHzFDpR1i98jmgcwBgsvxLhB3lHzLVhh/BJHjAYy/rEPY+lb2Dsvd3z9l72bI3zufsvSsUv+/DZvAHitc1itdyeKzuFuqpu4WyZT4AXgVPgSvgcHg1HCVz9y4d+b9D/nvv0rlE/l2qu10ug9W6U+c2Pb8TLtaZe0vdO1m0txr2krveO1nOV7xKYUs4V3cklSs+ZbCr9KH03SP3En3S9z2l7/u64+UDj739spfkY+9z2fsCmudfyt5Md28vaS573rtwClTOZsHm0reWfhycrTMRz4WTjX2dWVgILzV6+bPBKPlzUP4Yd9fKn/REJ30awHawIbT3zsDusDEcDZvC0/X8HNgcLoKt4OWwE1wJj4PXw87wZj2/G/aGm2T/CdgFPg17wH2wJ3xP5h/a8qT9kPBuhbuhzX/n7xiOBDP6rAQn3MfCbrA97As7wJNNeOAsEx44R/pLpF8s/felXyH9zdLfLv2d0ptwrQtoPyJ8W+FqDFcrXJ8oPJ/CHPMewhGwLvGaCv+R4KTfZ7DYlAv4HVMu4EXwn3ARTET+SpgEfw6T4Rq5swGmwMdhHZOOev4yTIWvSG/Cu8fd42f3GtrwmvzeqfCO1/s3EfaAk3T30mTdJTVF5e0MvZ95cAqcAYvsvgonfGfBtXC6vjvnwHsk92vpn5T5Tulflf5N6fdJ/lPpP5N5vaCjbxJ0zNtLf5yj151g2tel33Mi7gSDiU55GQ9bSt9GelNOJsARMBeOlX6S9Hpfta+KMPm8r6fK/RFy/1S5P0Luj4Sj4Ci9R6fByXA0nCZ9KB7V8meaTzz6yZ8Bxh/p2xi9/DkeDocnwDHS50ofisf+Q8RjkNwfIvcHyf0hcv8kxeNkxSNH8ThF8UCveGj/j/yJjsdk+TPN+CN9G+lHGfty/0y5f4bcRx++A07u5/u4P13u58v96XI/X+lSoHSZJXdnwjMdvep17Y+BaT71ejPeU8PmsB5skRC2Vy17dXzstZK91jAFtoH6nmn/CGXb53tWN+h8zzrBdrAzbA97ws6wG8yT/kPbXtTeC497GXC53Ps7coD2q/P+fwHbwi/hcbBxguNuMhwAU+AgPR8M66l+S4Mj9HwkrA+nwAbwTD0/C2bA6dKrHGrvBHnmUw5vSnDiezNsDG+BHeEvYVd4h8JxJzxJz4fB9XCU9PJH+wzok/n4M0v+FMEu8HzYQ3obLsWjBJ4t85nGLVgsfaidk6H4LPBp51wrf1bBJtI3l74Q/lzfgdWwEl7vcbfiufjufl/uLjfuSt/c6OXuVXJ3hdy9GqpdyPplvZ8+7cIT5e4gmAUHw/ZwhMrFEKXTSbC3nveTfiA8ReViGJxkwgvPkJz813phf/8nyv9J8n+y/J8h/6fI/6nyf4b8nyr/z5D/Z8r/6fIfObUvtN5W7a/o9sXjKndPwRbwadgK/gkeI31HO8bjtPNfhOPhK3AGfFXtjtdgKdwNbZrDRXLnu/Al+D2jV7gqTNj03hYpXGme9bLdVX/0VDoMgF2kHyz9EOlHSj9K+umwDyyAvVU+MA/3S/bG718EVV8kwCSYCN07+8L24vdvA1rPaJ75uL9X8XoTJsO/eMo=
*/