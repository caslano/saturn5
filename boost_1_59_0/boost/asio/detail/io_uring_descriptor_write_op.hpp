//
// detail/io_uring_descriptor_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence>
class io_uring_descriptor_write_op_base : public io_uring_operation
{
public:
  io_uring_descriptor_write_op_base(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state,
      const ConstBufferSequence& buffers, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_descriptor_write_op_base::do_prepare,
        &io_uring_descriptor_write_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      state_(state),
      buffers_(buffers),
      bufs_(buffers)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_descriptor_write_op_base* o(
        static_cast<io_uring_descriptor_write_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->descriptor_, POLLOUT);
    }
    else if (o->bufs_.is_single_buffer && o->bufs_.is_registered_buffer)
    {
      ::io_uring_prep_write_fixed(sqe, o->descriptor_,
          o->bufs_.buffers()->iov_base, o->bufs_.buffers()->iov_len,
          0, o->bufs_.registered_id().native_handle());
    }
    else
    {
      ::io_uring_prep_writev(sqe, o->descriptor_,
          o->bufs_.buffers(), o->bufs_.count(), -1);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_descriptor_write_op_base* o(
        static_cast<io_uring_descriptor_write_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      if (o->bufs_.is_single_buffer)
      {
        return descriptor_ops::non_blocking_write1(
            o->descriptor_, o->bufs_.first(o->buffers_).data(),
            o->bufs_.first(o->buffers_).size(), o->ec_,
            o->bytes_transferred_);
      }
      else
      {
        return descriptor_ops::non_blocking_write(
            o->descriptor_, o->bufs_.buffers(), o->bufs_.count(),
            o->ec_, o->bytes_transferred_);
      }
    }

    if (o->ec_ && o->ec_ == boost::asio::error::would_block)
    {
      o->state_ |= descriptor_ops::internal_non_blocking;
      return false;
    }

    return after_completion;
  }

private:
  int descriptor_;
  descriptor_ops::state_type state_;
  ConstBufferSequence buffers_;
  buffer_sequence_adapter<boost::asio::const_buffer,
      ConstBufferSequence> bufs_;
};

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class io_uring_descriptor_write_op
  : public io_uring_descriptor_write_op_base<ConstBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_descriptor_write_op);

  io_uring_descriptor_write_op(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : io_uring_descriptor_write_op_base<ConstBufferSequence>(success_ec,
        descriptor, state, buffers, &io_uring_descriptor_write_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_descriptor_write_op* o
      (static_cast<io_uring_descriptor_write_op*>(base));
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
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_OP_HPP

/* io_uring_descriptor_write_op.hpp
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
*/