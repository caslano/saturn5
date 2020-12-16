//
// detail/impl/kqueue_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2005 Stefan Arentz (stefan at soze dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP
#define BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_KQUEUE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Time_Traits>
void kqueue_reactor::add_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_add_timer_queue(queue);
}

// Remove a timer queue from the reactor.
template <typename Time_Traits>
void kqueue_reactor::remove_timer_queue(timer_queue<Time_Traits>& queue)
{
  do_remove_timer_queue(queue);
}

template <typename Time_Traits>
void kqueue_reactor::schedule_timer(timer_queue<Time_Traits>& queue,
    const typename Time_Traits::time_type& time,
    typename timer_queue<Time_Traits>::per_timer_data& timer, wait_op* op)
{
  mutex::scoped_lock lock(mutex_);

  if (shutdown_)
  {
    scheduler_.post_immediate_completion(op, false);
    return;
  }

  bool earliest = queue.enqueue_timer(time, timer, op);
  scheduler_.work_started();
  if (earliest)
    interrupt();
}

template <typename Time_Traits>
std::size_t kqueue_reactor::cancel_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& timer,
    std::size_t max_cancelled)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  std::size_t n = queue.cancel_timer(timer, ops, max_cancelled);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
  return n;
}

template <typename Time_Traits>
void kqueue_reactor::move_timer(timer_queue<Time_Traits>& queue,
    typename timer_queue<Time_Traits>::per_timer_data& target,
    typename timer_queue<Time_Traits>::per_timer_data& source)
{
  mutex::scoped_lock lock(mutex_);
  op_queue<operation> ops;
  queue.cancel_timer(target, ops);
  queue.move_timer(target, source);
  lock.unlock();
  scheduler_.post_deferred_completions(ops);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_KQUEUE)

#endif // BOOST_ASIO_DETAIL_IMPL_KQUEUE_REACTOR_HPP

/* kqueue_reactor.hpp
ED+xK50JrgaHge8FR4FrwHHgDeB0sBIs0/AacB14Lbhe7cpfB94CbgA/BW5UO9qbwN0af7/Ia783Z3vkbJDkK1vaq46r5H8IuFTt/r4bHKX2eMdoOE/DReBV4HxwOXilhiEJrwJXgNeBK8EtYC14I3g7uAOsBD+r9nrrwGvUPu9a8DvgevAAWKV2nzeBJ9WucRJ53gZ2AavB3uAHwUzwFjAP/JDaff4wOFXDRRqeB34ErFD+zeBHwRvBZeAO8Fq7XZEFscdj+Dg/EPv9QcathbHHj0Mh3RvWPXH45LzfAeW7Cb6B4AfBbPUrMULDMzQ8H7wVvAL8KFgOfgy8BtwObgM/Ad4EfhK8GawF68DbwK+Dt4P3afgBDT8C7gB/pvwvgbvUDvsXwLfUr0Uyef4M2An8LNgTvNM8h3T/Ecz3eQ4tgy8NvArMBcvt4/nC+OqjZmF89VEfZ300Kd+TIW99/EPHi7fUnvvbaq87Sft1sr6vpICTwI76fncOWKx22OeAXcBSMBW8DOyu73Xnav2lqR39dB0PeoFVYG/wRrCP2nvP0PGgL7gHzNR6HAD+EBwIPq5hLQfdF0JW3h+d5bDXbp/mkvj4suLkK4rC91XDR1ycfDWGT+YSDr7FNr66OPkagvl4DtrKL06+0KL4+LLi5CuKk68iTr6aOPnqYvBN6BQy9tGP1mKr6DbsF0MLobVQNJvptcTfC5Vih3vheuzjdEsONe31t3PUvN5u6wgKY18HKoX87Kbv5Ho9ZNlOPxj2t59+MhzNhjp0XYttpCngSsiypb6Dv3dDy6aRNhjNrvph4i3b6mkbnDaVJhBeCK2FaiNx0DHIbWtp4Ean7fXijWp/3WV76V6u3zoWfcGTkN0Ge1oVtoUgty32oip4wQrQZZOdgcdhl93YZK+v8tplP1lFGKylDNI2cQ/oFOGiCMJXAVr22us3OW09NRK27LY3b2q13Z7Ji10e5GfDfQnX7Xbcd2z22ocK06bc9tyPwt+4GYRS9lLekfjrW+1H5fG3ZUOq916njfc1xKXmwwdGbEvtAi177w3X+9t8P3q90+57yd74bL/nbkE/6BT3vwW026e6l3AZ4SOg2oI39qpObiHP/J2ztW3twZdtjW0TvjfXqrfGZxN+P3yW3asj/P0AvJk3IAflcm0JGGQnfssNHeK2FV8Hby1/N4ADCR8FLbvxQ22240u2wQuuBd12tOq5dpK/94OHCR8D06q5xt95oNuufEm1sS0vviDChC0b8zuqjZ154yNiH9emEHcYtNudT73RaXu+mPABxsxmKO12bNBDS6At0C5oH3QQOgll3ZEcKoFWQjXQvdBB6DjUewf256ElUBW0A7oX2g81Q2mfxq48tBBaC22H7oX2Q0ehzp/h/lAJFIZ2QPugw1Dos/QHaCFUBe2EHoaaoNSd5Hlnux2x9l/7r/3X/mv/tf9SoHVn3f7f8qqqDZVXt5gAPHMbgBdlsqZyzNjPm7FkyWXzZl6+ZLZa0RMben3HhIxdkc76yP+SrsF8DHo7n/n0FDln4LrJCj5oq9JzBnqOwPbteXrIkjtfv1/nXhIerWG+Vpyq50CM/PKqDVVbw6tsZxGabDIZhLuJTKXtO2Q57mBsqnWQ+Ov1LLElP0T4i/S7jirbWeJewr9M4tOlFLifzfbaKImfpmFbnjkVcRi+vA6sW4+IfDt3nc22hH57oTxL4DnOtdTURSH393UZylMNzz9HwXPOkNTOXWz2+FzfUfw98g0+126CsnvGPq/cI9Sx56WRPCO2asMG8m3/Lpr6ss7ImGumDoS3yHwDLeXsOI9fl+y1F/KPfNrcVJ/2YvPJUOS0GQL/6dsMKfKxGVLg4xc=
*/