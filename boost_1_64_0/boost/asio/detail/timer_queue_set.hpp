//
// detail/timer_queue_set.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP
#define BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/timer_queue_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class timer_queue_set
{
public:
  // Constructor.
  BOOST_ASIO_DECL timer_queue_set();

  // Add a timer queue to the set.
  BOOST_ASIO_DECL void insert(timer_queue_base* q);

  // Remove a timer queue from the set.
  BOOST_ASIO_DECL void erase(timer_queue_base* q);

  // Determine whether all queues are empty.
  BOOST_ASIO_DECL bool all_empty() const;

  // Get the wait duration in milliseconds.
  BOOST_ASIO_DECL long wait_duration_msec(long max_duration) const;

  // Get the wait duration in microseconds.
  BOOST_ASIO_DECL long wait_duration_usec(long max_duration) const;

  // Dequeue all ready timers.
  BOOST_ASIO_DECL void get_ready_timers(op_queue<operation>& ops);

  // Dequeue all timers.
  BOOST_ASIO_DECL void get_all_timers(op_queue<operation>& ops);

private:
  timer_queue_base* first_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/timer_queue_set.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_TIMER_QUEUE_SET_HPP

/* timer_queue_set.hpp
MaN7YA0Wa4Rf9MZemD7+12ITvPo+ylWznxjlhWtUXt7c+pHGdlKN+msg/VxywjHrN6e8zxAhTvD95pTJebaDkeb9xlnidW9B958cu/V5tuxWxnL5/Qj8U+GVd7P7kbpXfUc077lC5K7ACOAfkF+WOz/x5COOcZQvQD+aU11SXmaxTxv1wHG6k/8y+PPI/61hvzZ/R2D5XuSfDP/l5D9lOMPUXrQNCnuC/Talx3XCb4efxlH8YNehrBp+93eLuST/jmYf9pyyuZp+tI7CY+TZq83kXyL3ZNeS/wXcy08h4+E5B8rvF9tJJhlx4BfjA91TT8SJpf3ZI1GX+6JQnoJTv3UvI58+y5yOUvdnX0R92LUOADmzfpzIcZKieY92lDMmtI1i6Mtq/iMh10j5u77y9A+W4e8uHyP8JNwnmf77uuC1R9lLe7p8VtCw5zrXuOdazss7Yoxt/DO0ubrr5BlK3XMR93vIaPs95K3PT8pwy/OTCA/+/OSpEU0/P6nOkVtjjfr/Cek1SP01uvPZwc91ujf40b3Bj+4NzdD98yB0H67qbsLRfxrpKZUG3fm5zK3/H3X6Q95afxluqT/Cg9f/j0Ho/2O17Zvw8/9VjLce/XmMN7aBL3VlkOWnDLL8lEFWM8rgyyDKIJPnHDvz51/EZTAcbqEY5N3zKx4g8udcI+LLM094Z68soNkH9w5dVNk2pNsv4lWbQaotdA5HDqnQTsg87C6famlTSMrESbvq0gYIzvYUVM6jtKZ6p8V21eVzJH78vMNpxpFsP1oV4HLFM5T/cuXv2Xz+Suoryxc6sp0iT/lCJ1yDTp4xl8+90v17z/PM27+f7d5sgvsEdeh0t7t54gGtyjPRC6/VPM9xukrbNTXkv1/JRX5six9+kQy3RRknRe47uJn8DykO/EvlTmU5D0szinweOEkyGfI8NMLLRKraM1F3kkwsdI2UexbW0rVKcNRG0zzcHSUwBvqXwmEevF93Dknal/8a/vIE9zkkB+bCb+P925f3Nf9VUF3gjnXvpYtMbAh8NQJ5Vsnz88b5z7hGAnmfZ+cRHvzZ+fAOgfG255hw6X8DXVxSF8M4ZnjvdfnRw9UMPRIC5NKPMeHS/xZ67JJ6GOYl07WTXX502dUMXZb51kXOMcdNdPkOujRKXazmGOO7VaMffRqboQ/y8qnPAB672kJO/D6DS4FrgFuUiLKcx/pU5tN7iuL7vCnLd5WcBglyvK/g+KyXlO0t32XeJ389lcO6OE058Bj4HoXvIb9Dxu/lmcMwNxcWlcn5JxF4dJ7nnaZExulueP8R6h/n9K3ed2JoTUf125TTJN9JEe8YjSiPPMyvhX0gFwrbXhfiHeMu63eMBI6zCHGKRJzYKfr3CzlmdkzA8wvGyjNw61EuXwXwDsFzneH8Jp/R5zlM1okcY1Husn0I2Vw5X3LZ6p4zDtPeNNwPbjwJ2Aoo2k1FiWw3JcjBZ5up4Pm8p/CjXDeS/1O89YXTnrmZcFVw98I1wHHbQnzZtkQesp7upPh/5Xampt/Rsl2tofAz3K5U+e6W7UroeTfJ/IPbFcdBrXRDnV2goL64rlR3RvqDr7sE77qDzk2vtyEqz0RHd4ab+VnlHrjvMX7FVVO9VVSi4ecXgsbD3QWMZcdlPYLk53NdqvEzTNcAJ8rwNLkmkE3+myzLuj1wMMncSP5imUYPyuNbGrfKxClu2S6438i+IrBvPPUjKnunn2eNCm158rVF2rU3LmOXsYzlOh3uC9fFfXmPs2c6ecqdOdwV20iM8dpyp0c08zJHGbOsXZahslD4b5XPeDbNM95EKZ8u23srkr/B57gZSjKLuMzVNFJNuW+iSXYurZfmol0=
*/