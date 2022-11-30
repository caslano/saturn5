//
// detail/winrt_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_work.hpp>
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
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_recv_op* o(static_cast<winrt_socket_recv_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

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
  handler_work<Handler, IoExecutor> executor_;
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