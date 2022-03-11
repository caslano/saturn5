//
// detail/winrt_async_manager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_ASYNC_MANAGER_HPP
#define BOOST_ASIO_DETAIL_WINRT_ASYNC_MANAGER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <future>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class winrt_async_manager
  : public execution_context_service_base<winrt_async_manager>
{
public:
  // Constructor.
  winrt_async_manager(execution_context& context)
    : execution_context_service_base<winrt_async_manager>(context),
      scheduler_(use_service<scheduler_impl>(context)),
      outstanding_ops_(1)
  {
  }

  // Destructor.
  ~winrt_async_manager()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
    if (--outstanding_ops_ > 0)
    {
      // Block until last operation is complete.
      std::future<void> f = promise_.get_future();
      f.wait();
    }
  }

  void sync(Windows::Foundation::IAsyncAction^ action,
      boost::system::error_code& ec)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto promise = std::make_shared<std::promise<boost::system::error_code>>();
    auto future = promise->get_future();

    action->Completed = ref new AsyncActionCompletedHandler(
      [promise](IAsyncAction^ action, AsyncStatus status)
      {
        switch (status)
        {
        case AsyncStatus::Canceled:
          promise->set_value(boost::asio::error::operation_aborted);
          break;
        case AsyncStatus::Error:
        case AsyncStatus::Completed:
        default:
          boost::system::error_code ec(
              action->ErrorCode.Value,
              boost::system::system_category());
          promise->set_value(ec);
          break;
        }
      });

    ec = future.get();
  }

  template <typename TResult>
  TResult sync(Windows::Foundation::IAsyncOperation<TResult>^ operation,
      boost::system::error_code& ec)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto promise = std::make_shared<std::promise<boost::system::error_code>>();
    auto future = promise->get_future();

    operation->Completed = ref new AsyncOperationCompletedHandler<TResult>(
      [promise](IAsyncOperation<TResult>^ operation, AsyncStatus status)
      {
        switch (status)
        {
        case AsyncStatus::Canceled:
          promise->set_value(boost::asio::error::operation_aborted);
          break;
        case AsyncStatus::Error:
        case AsyncStatus::Completed:
        default:
          boost::system::error_code ec(
              operation->ErrorCode.Value,
              boost::system::system_category());
          promise->set_value(ec);
          break;
        }
      });

    ec = future.get();
    return operation->GetResults();
  }

  template <typename TResult, typename TProgress>
  TResult sync(
      Windows::Foundation::IAsyncOperationWithProgress<
        TResult, TProgress>^ operation,
      boost::system::error_code& ec)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto promise = std::make_shared<std::promise<boost::system::error_code>>();
    auto future = promise->get_future();

    operation->Completed
      = ref new AsyncOperationWithProgressCompletedHandler<TResult, TProgress>(
        [promise](IAsyncOperationWithProgress<TResult, TProgress>^ operation,
          AsyncStatus status)
        {
          switch (status)
          {
          case AsyncStatus::Canceled:
            promise->set_value(boost::asio::error::operation_aborted);
            break;
          case AsyncStatus::Started:
            break;
          case AsyncStatus::Error:
          case AsyncStatus::Completed:
          default:
            boost::system::error_code ec(
                operation->ErrorCode.Value,
                boost::system::system_category());
            promise->set_value(ec);
            break;
          }
        });

    ec = future.get();
    return operation->GetResults();
  }

  void async(Windows::Foundation::IAsyncAction^ action,
      winrt_async_op<void>* handler)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto on_completed = ref new AsyncActionCompletedHandler(
      [this, handler](IAsyncAction^ action, AsyncStatus status)
      {
        switch (status)
        {
        case AsyncStatus::Canceled:
          handler->ec_ = boost::asio::error::operation_aborted;
          break;
        case AsyncStatus::Started:
          return;
        case AsyncStatus::Completed:
        case AsyncStatus::Error:
        default:
          handler->ec_ = boost::system::error_code(
              action->ErrorCode.Value,
              boost::system::system_category());
          break;
        }
        scheduler_.post_deferred_completion(handler);
        if (--outstanding_ops_ == 0)
          promise_.set_value();
      });

    scheduler_.work_started();
    ++outstanding_ops_;
    action->Completed = on_completed;
  }

  template <typename TResult>
  void async(Windows::Foundation::IAsyncOperation<TResult>^ operation,
      winrt_async_op<TResult>* handler)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto on_completed = ref new AsyncOperationCompletedHandler<TResult>(
      [this, handler](IAsyncOperation<TResult>^ operation, AsyncStatus status)
      {
        switch (status)
        {
        case AsyncStatus::Canceled:
          handler->ec_ = boost::asio::error::operation_aborted;
          break;
        case AsyncStatus::Started:
          return;
        case AsyncStatus::Completed:
          handler->result_ = operation->GetResults();
          // Fall through.
        case AsyncStatus::Error:
        default:
          handler->ec_ = boost::system::error_code(
              operation->ErrorCode.Value,
              boost::system::system_category());
          break;
        }
        scheduler_.post_deferred_completion(handler);
        if (--outstanding_ops_ == 0)
          promise_.set_value();
      });

    scheduler_.work_started();
    ++outstanding_ops_;
    operation->Completed = on_completed;
  }

  template <typename TResult, typename TProgress>
  void async(
      Windows::Foundation::IAsyncOperationWithProgress<
        TResult, TProgress>^ operation,
      winrt_async_op<TResult>* handler)
  {
    using namespace Windows::Foundation;
    using Windows::Foundation::AsyncStatus;

    auto on_completed
      = ref new AsyncOperationWithProgressCompletedHandler<TResult, TProgress>(
        [this, handler](IAsyncOperationWithProgress<
          TResult, TProgress>^ operation, AsyncStatus status)
        {
          switch (status)
          {
          case AsyncStatus::Canceled:
            handler->ec_ = boost::asio::error::operation_aborted;
            break;
          case AsyncStatus::Started:
            return;
          case AsyncStatus::Completed:
            handler->result_ = operation->GetResults();
            // Fall through.
          case AsyncStatus::Error:
          default:
            handler->ec_ = boost::system::error_code(
                operation->ErrorCode.Value,
                boost::system::system_category());
            break;
          }
          scheduler_.post_deferred_completion(handler);
          if (--outstanding_ops_ == 0)
            promise_.set_value();
        });

    scheduler_.work_started();
    ++outstanding_ops_;
    operation->Completed = on_completed;
  }

private:
  // The scheduler implementation used to post completed handlers.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  // Count of outstanding operations.
  atomic_count outstanding_ops_;

  // Used to keep wait for outstanding operations to complete.
  std::promise<void> promise_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_ASYNC_MANAGER_HPP

/* winrt_async_manager.hpp
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
*/