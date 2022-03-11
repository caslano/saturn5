//
// detail/win_iocp_handle_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& ec, std::size_t bytes_transferred)
  {
    // Take ownership of the operation object.
    win_iocp_handle_write_op* o(static_cast<win_iocp_handle_write_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
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