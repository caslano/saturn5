//
// detail/win_iocp_handle_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_handle_write_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_handle_write_op);

  win_iocp_handle_write_op(const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_handle_write_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_handle_write_op* o(static_cast<win_iocp_handle_write_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    if (owner)
    {
      // Check whether buffers are still valid.
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
      handler(o->handler_, ec, bytes_transferred);
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
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_WRITE_OP_HPP

/* win_iocp_handle_write_op.hpp
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
*/