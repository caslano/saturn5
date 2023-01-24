//
// detail/winrt_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_send_op* o(static_cast<winrt_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP

/* winrt_socket_send_op.hpp
ARpfg9NuJUmlQO7nmAfg04Xa94XJ8DUpMHmY3sYFi3oJrH9u9CbfFPiprVRr8gDxs8a8PCg9BYwW7178paUVxW/K7ZBJBZ6xzZNiCzSeWmo/09+YCrjBrnHTH6H2HGHi+M4/FTLZpiViIqg8ua51U7JTYVdk+7dgfZR/uztcHpMG7wzG35Z0QukTt1rKGKbBfbNqF1WvTjR+K6Scu5oG8zijxlz7iNo7bMMp+YI0qHDccWJcBJJP96PQBwrp0FfXMnHDIsTvjlIT7a3pcPODv+l08woC00m/VBiQDhNeJCs2rUD5jTY6eJakw2T9a3FsE1QfzVJWQ+UTLHu1+OKwMqT/XLpb+Y5PsPQlERI69ReBVbumBN7/BLNM6oINV6Lnk02BzO6qT0AaShadGYb0seqQudb0DJC8ex5bXYjKzwxKH7YvA1b25dHD81D/KC05VPU0A1SKvmbcOIjad1H41rSGDKgd7utWuS0Jjd+cB5FzPoM3eWjC/ueov84J3R5q+xnm6TeH34hB/EeY3A159RkUL92pi7NG8mu75vGu/TMcmuP0qlgexasxJHdNzITbJ7vGfHBFcxpc5UXXukyQTfM0mpwgycIsRTJU/TLhXLPIBJ09w1nYJGnajqxMWFlFE33ggu5PmyeGjskCkatBt+efkmFhh76uGWOUBWvOt6m8spRgYdPx9tPXs2DuG3/7EhLx49g4YXRRFuyo
*/