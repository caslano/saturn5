//
// detail/win_iocp_handle_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/error.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class win_iocp_handle_read_op : public operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(win_iocp_handle_read_op);

  win_iocp_handle_read_op(const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : operation(&win_iocp_handle_read_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& result_ec,
      std::size_t bytes_transferred)
  {
    boost::system::error_code ec(result_ec);

    // Take ownership of the operation object.
    win_iocp_handle_read_op* o(static_cast<win_iocp_handle_read_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    if (owner)
    {
      // Check whether buffers are still valid.
      buffer_sequence_adapter<boost::asio::mutable_buffer,
          MutableBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    // Map non-portable errors to their portable counterparts.
    if (ec.value() == ERROR_HANDLE_EOF)
      ec = boost::asio::error::eof;

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
  MutableBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_HANDLE_READ_OP_HPP

/* win_iocp_handle_read_op.hpp
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
*/