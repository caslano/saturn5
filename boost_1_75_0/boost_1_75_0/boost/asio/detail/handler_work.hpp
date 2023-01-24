//
// detail/handler_work.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_WORK_HPP
#define BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// A helper class template to allow completion handlers to be dispatched
// through either the new executors framework or the old invocaton hook. The
// primary template uses the new executors framework.
template <typename Handler,
    typename IoExecutor = system_executor, typename HandlerExecutor
      = typename associated_executor<Handler, IoExecutor>::type>
class handler_work
{
public:
  explicit handler_work(Handler& handler) BOOST_ASIO_NOEXCEPT
    : io_executor_(),
      executor_(boost::asio::get_associated_executor(handler, io_executor_))
  {
  }

  handler_work(Handler& handler, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : io_executor_(io_ex),
      executor_(boost::asio::get_associated_executor(handler, io_executor_))
  {
  }

  static void start(Handler& handler) BOOST_ASIO_NOEXCEPT
  {
    HandlerExecutor ex(boost::asio::get_associated_executor(handler));
    ex.on_work_started();
  }

  static void start(Handler& handler,
      const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
  {
    HandlerExecutor ex(boost::asio::get_associated_executor(handler, io_ex));
    ex.on_work_started();
    io_ex.on_work_started();
  }

  ~handler_work()
  {
    io_executor_.on_work_finished();
    executor_.on_work_finished();
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(Function)(function),
        boost::asio::get_associated_allocator(handler));
  }

private:
  // Disallow copying and assignment.
  handler_work(const handler_work&);
  handler_work& operator=(const handler_work&);

  IoExecutor io_executor_;
  HandlerExecutor executor_;
};

// This specialisation dispatches a handler through the old invocation hook.
// The specialisation is not strictly required for correctness, as the
// system_executor will dispatch through the hook anyway. However, by doing
// this we avoid an extra copy of the handler.
template <typename Handler>
class handler_work<Handler, system_executor, system_executor>
{
public:
  explicit handler_work(Handler&) BOOST_ASIO_NOEXCEPT {}
  static void start(Handler&) BOOST_ASIO_NOEXCEPT {}
  ~handler_work() {}

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    boost_asio_handler_invoke_helpers::invoke(function, handler);
  }

private:
  // Disallow copying and assignment.
  handler_work(const handler_work&);
  handler_work& operator=(const handler_work&);
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

/* handler_work.hpp
WNFxkIPpRS/O6sWi7VJgagOUiDO+nUDgey9p3P3OD9zNFwO9/UuZMlgpcem13jFzcYAD4/B4+f6X1B6sqmw3ce7dCIEWtGEv0M4ravKpdQFNU4tnh9PgfC95/kuaLK3yM1lqqitSp8rU/oPAUrULSmlaWojtQA9d8Czhs4nS+9VxXsu8fDft9HcSWO1pEvIyJgqX+q8NG9rVxtrl7Bi4XcJC4Mw//6Fx5sgDwJlc/7XAmR4qIVUvYVifEort2HuMOUk4U7N+baJ3jLz6HzpfjNajbllwjCaaadpRPcm4jwzKz1DcVBB0TUgBCzAZGYaKlwBSOyGz3AG6kyqP/ocms1cCjVJdRPla5W1/R4YdQ3aNLmUKXiLPn8GyopZggGZzJEq9UmPGRN6WvwDFFgfTUGxf/zuJbT7O+Wxcd60/n0S33Vcc0kS3lYnusJN9RLcDAd/ykFQcUkV3qFTZnu2d2ADmlIaZk8Uu6FEp14Eqmx/OdUBfXbyAv1Bp8xzk08DaVMfC9Ty4GruAt14rtPsEB26xVJzsOShYvRPzcReYPQRiOzIgNhS7zEKmfzH0brvWN62sb9ae6NM3yTjBRBVc75ggW64XFpZJuT3wVILc9Dd9DKMgUTxtXp/hL+y1vg9VS11Z7xtKTulTMggePLNPVayxis3702Fhl3OZsgJ4ue5vmhw9Ug1ytDCrIHHdFf7FIEzJmjiqxQa+7VNs
*/