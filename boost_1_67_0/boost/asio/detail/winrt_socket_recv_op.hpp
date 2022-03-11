//
// detail/winrt_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class winrt_socket_recv_op :
  public winrt_async_op<Windows::Storage::Streams::IBuffer^>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_recv_op);

  winrt_socket_recv_op(const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<Windows::Storage::Streams::IBuffer^>(
          &winrt_socket_recv_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_recv_op* o(static_cast<winrt_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    std::size_t bytes_transferred = o->result_ ? o->result_->Length : 0;
    if (bytes_transferred == 0 && !o->ec_ &&
        !buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::all_empty(o->buffers_))
    {
      o->ec_ = boost::asio::error::eof;
    }

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, bytes_transferred);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_RECV_OP_HPP

/* winrt_socket_recv_op.hpp
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
*/