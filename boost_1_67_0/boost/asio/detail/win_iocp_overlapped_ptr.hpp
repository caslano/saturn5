//
// detail/win_iocp_overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/io_object_executor.hpp>
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
    const bool native = is_same<Executor, io_context::executor_type>::value;
    win_iocp_io_context* iocp_service = this->get_iocp_service(ex);

    typedef win_iocp_overlapped_op<Handler, io_object_executor<Executor> > op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_object_executor<Executor>(ex, native));

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
  static win_iocp_io_context* get_iocp_service(const Executor& ex)
  {
    return &use_service<win_iocp_io_context>(ex.context());
  }

  static win_iocp_io_context* get_iocp_service(
      const io_context::executor_type& ex)
  {
    return &ex.context().impl_;
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
+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
*/