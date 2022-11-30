//
// detail/io_uring_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_NULL_BUFFERS_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class io_uring_null_buffers_op : public io_uring_operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_null_buffers_op);

  io_uring_null_buffers_op(const boost::system::error_code& success_ec,
      int descriptor, int poll_flags, Handler& handler, const IoExecutor& io_ex)
    : io_uring_operation(success_ec,
        &io_uring_null_buffers_op::do_prepare,
        &io_uring_null_buffers_op::do_perform,
        &io_uring_null_buffers_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex),
      descriptor_(descriptor),
      poll_flags_(poll_flags)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_null_buffers_op* o(static_cast<io_uring_null_buffers_op*>(base));

    ::io_uring_prep_poll_add(sqe, o->descriptor_, o->poll_flags_);
  }

  static bool do_perform(io_uring_operation*, bool after_completion)
  {
    return after_completion;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_null_buffers_op* o(static_cast<io_uring_null_buffers_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
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
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
  int descriptor_;
  int poll_flags_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_URING_NULL_BUFFERS_OP_HPP

/* io_uring_null_buffers_op.hpp
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
*/