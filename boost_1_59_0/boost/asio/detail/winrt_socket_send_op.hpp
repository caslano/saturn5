//
// detail/winrt_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP

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

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class winrt_socket_send_op :
  public winrt_async_op<unsigned int>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_send_op);

  winrt_socket_send_op(const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<unsigned int>(&winrt_socket_send_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_send_op* o(static_cast<winrt_socket_send_op*>(base));
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
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->result_);
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
  ConstBufferSequence buffers_;
  Handler handler_;
  handler_work<Handler, IoExecutor> executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP

/* winrt_socket_send_op.hpp
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
*/