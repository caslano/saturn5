//
// detail/timer_queue_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class timer_queue_base
  : private noncopyable
{
public:
  // Constructor.
  timer_queue_base() : next_(0) {}

  // Destructor.
  virtual ~timer_queue_base() {}

  // Whether there are no timers in the queue.
  virtual bool empty() const = 0;

  // Get the time to wait until the next timer.
  virtual long wait_duration_msec(long max_duration) const = 0;

  // Get the time to wait until the next timer.
  virtual long wait_duration_usec(long max_duration) const = 0;

  // Dequeue all ready timers.
  virtual void get_ready_timers(op_queue<operation>& ops) = 0;

  // Dequeue all timers.
  virtual void get_all_timers(op_queue<operation>& ops) = 0;

private:
  friend class timer_queue_set;

  // Next timer queue in the set.
  timer_queue_base* next_;
};

template <typename Time_Traits>
class timer_queue;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_BASE_HPP

/* timer_queue_base.hpp
0r8V+bH7tzqyaZ9dRo7vXOToo9a6jBwhc9j1u6IkghwlLZCDujzlsN+LDRs75ein1qlc5eBe9Fg/qo0gS20LZEnMim5MFmQ5ZemPLA1GFtt95fHuboggR0ML5JjtObfiNuP/Bh2S97QOSZ/rl/5ac8tHv+/TeNCSVUvn3eRlK/3/sxl31znx1i35waa3yG9GbdfILcxvS///RwftuNkT8Lbn3cJuT3m8tz31Zja+2iiv12D4mrYLX9tEvf1tfNYJka+3UskhfDwTTL8sF77dRC9md1D7vgT7g8PBQnAPcH/wAPAgsAScAu4FVsn5WXJ+DlgEniTnF8j5M8Fi8GI5f5mcvwqcCN4s52+V83dJ+nFwGPikOm/svmUtFOzhYve9k8gzCMwGh4DdJG3ig57o3W99bPGxG4UvR/js8bEb4FP4EJgCPgymgivBNPARMANcAXYBHwW3BB8De4OPg/2En/roB1ljA4ulvhSwIKD/BF8iuFDqOx9MBy8Ae4AXgduBN4PbgzeCfSVt7O+bmFeUNXw18yP3zxyoXvjKhc+uL3Wb9P8d4DaS7inpPuCd4A7gcnAYeDeYL+lC8F5wHHgfuK+kD1T5Un9uYK0EHCn1twYHSP0zZXxmgVuAZ4BbgWeDW4O1tn6vk+vs69LvZfBtCh4s5Q6Rdh8GDgErwRGSHgWWgwVy3thvn+zdn1k2viLP8QHt4xjl9apOju65VHdy5PGGj984kZ838PF7ILr25ZwSXftKTomufbWnRNe+hgjtGxClHXjVj+igQLdDq39sfvzZuC14y3ThYtWDW/fj+tGF+z/Ygmf8FJ1e3F9hDx7XjWu5blz3n0CoDJoPLYNWQh9DKT/T79BIqBq6FFoOvQGl/EI7oAKoAloALYZWQO9DSb/SVigXKoFqfo3r3sWP+BE/4kf8iB/xI37Ej//XscH0/6fOqT50tjIAaJn+fyCu35weWr9/YnF+4Yj8Eb7R+ZN8E8bn7ZlvlPM5lH5+K1tcv7ku+vlt1F7fPL0/5ryYLa7f953D9vvmxa7jwrUcMZ1+SvDQFzzWo23NjOu3qId3XL9yp66+1mtu8OqX5sX1Q/bQ+ipcdPbTlR+EeWb/31mn7FemhukBUMZbD8Dke+oBkB+7HkBqDHoAgT4Y6qKr347rda0xe7UufeA6FynT5J4t+bHv2VKX556tPU5DcbL4sIW2gWogn7LDOM7Eu3KTR+u//eru71/K9tR+GOoC++7JtnhrhidHp8eo8dTpKivT+PTnweOrmD6r2tLX6SrXLzJl0ZNH5HrO/6jThzhiTKmx+UbnTRNdVPFlb9MRTVXziFpDYkz58KURjDGlfTzkMu6LWqPv2kv5eNgmvXXb9MRdcFHv6p9e+JfDv0rxp+Y6/MlLOR2zaGDf5sUnQn9b9+uvdj8OMvbLjA5lqearN37gTX864xGJvPZ5sSI5LL6FPFuKakysFuXKY+ywvfKHF5uAJrHHMynbyFlfV2W34FafBDRRY5o90CWmT03s8Uy4nms8kxEpzvZl0h+1bu2zBTRpJ/d9WBulnMQz6eAazwSe2OOZUKcznkkH73gmnds45euEfPXu8hFwyFM2KZMl95wj3hD5sccbMnI59KupI2xOfe4iUzfGt9FNJlGk9phTlGkyRgv5scdoyR4YOUZLQKYzUj3i/tTEEPenBfeJiSsT1r6SNPe4OBnHNz8uDmWa6nPyY+/zaOLiBO79waJbva2yXRGcjYBFxwbi4jT/Hekvu5l+x6DH4BkDx87H/rEj5k2W2FBM03wZCYP4u8TYSEh5uELi1Mi78Uad9wR6FBm2WC+8J7iyva2P+68t97vwHDpb111I/gydn5LQm1Y=
*/