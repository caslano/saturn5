//
// detail/winrt_async_manager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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