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
l/0ruGhxnTif88b55jM/FNjlMewN3wTJv1/3rogj6L6fRgk9ZbJZjviM5D4CFXoB9Lypvy7yGbiS7P+iiPX+DuN6RPXja+LqRNcDgzR60g+Esrs2V9AxMpUwvjZ15F8HHc8httfHQzY9vOOp+Nwb+dwYFFIe0pvOarsG76sUPov9GCVKaXQYzyfz5TJhj3TnKI4zKhNPjPMtEwHjff1R433LSLL0+96LG1n3XOjX9WB6xL04nsuIVjrEOyEmAaFl1OUFtsl6RgszTK6l/RL5V6ifKEGWbfgkGSZFjkF42Hte9Ucl0K7fg8MMlmuC/4X8ZeoxxaV7H5RlUvZXPEt25ep7PJ66WB5roPl7onyXYxt+l6uGn/u4kCqZJw3reE7wjqEYR3MYRolrTn9/pGMsVSJom0rb4sg2Ur0d/+lZ2tDvwn0ZurV2uQ+E3+eeomOuVo/CwtCPJ9dZf41sCtWPFYfVM7VcN+lJslurXoRUvYP+LLE2dRDqj+0QdLuL1nW7HrdDFG4GZwB+XEb3RYDb6hnc9vl+CKX3DpzhEnNcOL1Zis+aznI9HgSQYy0+476cfPAB3v5uatN9OWKNHlwfbY0ew7sZ4tHIeCiPRf/NBrlNljWyrTa/S/D3L593CalxXudovmZ5c7XJrTXUm69Zbq1BbqfJbadNbqfJ/dNpkNtpdX9O2uTBn++c+NFTFztvvP3++9e0uvhzO61xO81yO+15Oy1zO21yOw3y5mvDW2uW22mKN1+z3Foz3lZjnjTLK5UGzfIctUGzfKtOs3yr1CyXv2m+ym6V+i5ojCbqfNIsvot/h8PdxL+nwG3m3/PgbuDfeawFnqXwnEieOyL2uUAkh/6gJ+iJA78AB4LHwEngl6zFl67wPD2wJ4d3gt05/CwOPx/sBs4DtfPmcLibLc77D9glgN+B/cDvwfXgSQ5fpPDcIXAphw8GF3L4XNiFs4ZqMlgA9mWN38EiDDhOhANnsn82+xewBrA41gW6+FZn2efTB5zODzmfPuJ8+liXT6GD7PNpAoefyvk0RafRmc3h6jmcXqMzDXadwf4gPQeBo8EBIK1jDF4AZrHW7GDwGnAIeCM4FLwFHAbeDQ4H7+Pw+8S5wZf5uO+Ag2R+8FhvcLpFfjzM6XkUTAP/BI4AH9OFr+PwtRbhn+Lr/wxf/2fBzeBzHH6eNs4VvJjDB4GTOTzS4OnCWrbJ4B/ACaxpO4k1bM9lTdvz2b+K/eL4ZQqPqRTXlI8fAhbw8RNZezQFFOlLBQeDvcA5YD+wGOwNbgTTwF+xZv4eKg/efM0AXyd7TZOcx/OBW/i8ek3yQax1Cj/lyzBwjLhunI5ssIrmE8h84rFruAeN+cQarm1YwzUJrAJTWau1D/szwEpwBngZOIv3a8ev5uPPszh+KR+/DOwJrgJTwDVgGvv7gheC08GV4Eze/xWlh8dWAal8/ACQX91IM1ZwExjGWrtdwM1gIni9rrxl83FCLcrbIT7O22Ar8B2wHfiuvrxz+E4W4e/l8HvA1jrt+r36+qOR89dy+J18/rv4/Hfr8mF3I/lwBYe/kvPhKpDaCs6Ha3Sa98d06chRz0zzPh0um9uPCIt6rY6v/ytge/Cv+najkXAvcLiXONyLHC5HhMtmTXcOJ/JrNIfrxPneheuPeDAb7ApOBLuBc8EE8CKwBx93t/aNmb91Fxk0nH/J9/s14AhwI2sNXwsuADeBi8Gd4DrW3r5ZXD/wDtbg/i1rbT8KbmEt7RvAT8Gt4PfgNjAE574VDAVrwAzwDnAI+FtwFHgn53+e/CZH3ysp3snedpf+xsEugTXxk8CpHO9prJFcxRrJ08Hl4Ayur2aC14NzON6wIS0=
*/