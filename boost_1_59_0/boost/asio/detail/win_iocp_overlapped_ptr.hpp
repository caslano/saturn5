//
// detail/win_iocp_overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/io_context.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/win_iocp_overlapped_op.hpp>
#include <boost/asio/detail/win_iocp_io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Wraps a handler to create an OVERLAPPED object for use with overlapped I/O.
class win_iocp_overlapped_ptr
  : private noncopyable
{
public:
  // Construct an empty win_iocp_overlapped_ptr.
  win_iocp_overlapped_ptr()
    : ptr_(0),
      iocp_service_(0)
  {
  }

  // Construct an win_iocp_overlapped_ptr to contain the specified handler.
  template <typename Executor, typename Handler>
  explicit win_iocp_overlapped_ptr(const Executor& ex,
      BOOST_ASIO_MOVE_ARG(Handler) handler)
    : ptr_(0),
      iocp_service_(0)
  {
    this->reset(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  // Destructor automatically frees the OVERLAPPED object unless released.
  ~win_iocp_overlapped_ptr()
  {
    reset();
  }

  // Reset to empty.
  void reset()
  {
    if (ptr_)
    {
      ptr_->destroy();
      ptr_ = 0;
      iocp_service_->work_finished();
      iocp_service_ = 0;
    }
  }

  // Reset to contain the specified handler, freeing any current OVERLAPPED
  // object.
  template <typename Executor, typename Handler>
  void reset(const Executor& ex, Handler handler)
  {
    win_iocp_io_context* iocp_service = this->get_iocp_service(ex);

    typedef win_iocp_overlapped_op<Handler, Executor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, ex);

    BOOST_ASIO_HANDLER_CREATION((ex.context(), *p.p,
          "iocp_service", iocp_service, 0, "overlapped"));

    iocp_service->work_started();
    reset();
    ptr_ = p.p;
    p.v = p.p = 0;
    iocp_service_ = iocp_service;
  }

  // Get the contained OVERLAPPED object.
  OVERLAPPED* get()
  {
    return ptr_;
  }

  // Get the contained OVERLAPPED object.
  const OVERLAPPED* get() const
  {
    return ptr_;
  }

  // Release ownership of the OVERLAPPED object.
  OVERLAPPED* release()
  {
    if (ptr_)
      iocp_service_->on_pending(ptr_);

    OVERLAPPED* tmp = ptr_;
    ptr_ = 0;
    iocp_service_ = 0;
    return tmp;
  }

  // Post completion notification for overlapped operation. Releases ownership.
  void complete(const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    if (ptr_)
    {
      iocp_service_->on_completion(ptr_, ec,
          static_cast<DWORD>(bytes_transferred));
      ptr_ = 0;
      iocp_service_ = 0;
    }
  }

private:
  template <typename Executor>
  static win_iocp_io_context* get_iocp_service(const Executor& ex,
      typename enable_if<
        can_query<const Executor&, execution::context_t>::value
      >::type* = 0)
  {
    return &use_service<win_iocp_io_context>(
        boost::asio::query(ex, execution::context));
  }

  template <typename Executor>
  static win_iocp_io_context* get_iocp_service(const Executor& ex,
      typename enable_if<
        !can_query<const Executor&, execution::context_t>::value
      >::type* = 0)
  {
    return &use_service<win_iocp_io_context>(ex.context());
  }

  static win_iocp_io_context* get_iocp_service(
      const io_context::executor_type& ex)
  {
    return &boost::asio::query(ex, execution::context).impl_;
  }

  win_iocp_operation* ptr_;
  win_iocp_io_context* iocp_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP

/* win_iocp_overlapped_ptr.hpp
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
*/