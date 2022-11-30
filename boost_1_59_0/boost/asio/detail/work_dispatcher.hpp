//
// detail/work_dispatcher.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP
#define BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/allocator.hpp>
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/prefer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename Executor, typename = void>
struct is_work_dispatcher_required : true_type
{
};

template <typename Handler, typename Executor>
struct is_work_dispatcher_required<Handler, Executor,
    typename enable_if<
      is_same<
        typename associated_executor<Handler,
          Executor>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type> : false_type
{
};

template <typename Handler, typename Executor, typename = void>
class work_dispatcher
{
public:
  template <typename CompletionHandler>
  work_dispatcher(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      const Executor& handler_ex)
    : handler_(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)),
      executor_(boost::asio::prefer(handler_ex,
          execution::outstanding_work.tracked))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  work_dispatcher(const work_dispatcher& other)
    : handler_(other.handler_),
      executor_(other.executor_)
  {
  }

  work_dispatcher(work_dispatcher&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      executor_(BOOST_ASIO_MOVE_CAST(work_executor_type)(other.executor_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    execution::execute(
        boost::asio::prefer(executor_,
          execution::blocking.possibly,
          execution::allocator((get_associated_allocator)(handler_))),
        boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(Handler)(handler_)));
  }

private:
  typedef typename decay<
      typename prefer_result<const Executor&,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type work_executor_type;

  Handler handler_;
  work_executor_type executor_;
};

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Handler, typename Executor>
class work_dispatcher<Handler, Executor,
    typename enable_if<!execution::is_executor<Executor>::value>::type>
{
public:
  template <typename CompletionHandler>
  work_dispatcher(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler,
      const Executor& handler_ex)
    : work_(handler_ex),
      handler_(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  work_dispatcher(const work_dispatcher& other)
    : work_(other.work_),
      handler_(other.handler_)
  {
  }

  work_dispatcher(work_dispatcher&& other)
    : work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<Executor>)(other.work_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    typename associated_allocator<Handler>::type alloc(
        (get_associated_allocator)(handler_));
    work_.get_executor().dispatch(
        boost::asio::detail::bind_handler(
          BOOST_ASIO_MOVE_CAST(Handler)(handler_)), alloc);
    work_.reset();
  }

private:
  executor_work_guard<Executor> work_;
  Handler handler_;
};

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WORK_DISPATCHER_HPP

/* work_dispatcher.hpp
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
*/