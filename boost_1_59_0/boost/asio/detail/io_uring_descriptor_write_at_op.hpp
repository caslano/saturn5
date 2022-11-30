//
// detail/io_uring_descriptor_write_at_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_AT_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_AT_OP_HPP

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
class io_uring_descriptor_write_at_op_base : public io_uring_operation
{
public:
  io_uring_descriptor_write_at_op_base(
      const boost::system::error_code& success_ec, int descriptor,
      descriptor_ops::state_type state, uint64_t offset,
      const ConstBufferSequence& buffers, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_descriptor_write_at_op_base::do_prepare,
        &io_uring_descriptor_write_at_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      state_(state),
      offset_(offset),
      buffers_(buffers),
      bufs_(buffers)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_descriptor_write_at_op_base* o(
        static_cast<io_uring_descriptor_write_at_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->descriptor_, POLLOUT);
    }
    else if (o->bufs_.is_single_buffer && o->bufs_.is_registered_buffer)
    {
      ::io_uring_prep_write_fixed(sqe, o->descriptor_,
          o->bufs_.buffers()->iov_base, o->bufs_.buffers()->iov_len,
          o->offset_, o->bufs_.registered_id().native_handle());
    }
    else
    {
      ::io_uring_prep_writev(sqe, o->descriptor_,
          o->bufs_.buffers(), o->bufs_.count(), o->offset_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_descriptor_write_at_op_base* o(
        static_cast<io_uring_descriptor_write_at_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      if (o->bufs_.is_single_buffer)
      {
        return descriptor_ops::non_blocking_write_at1(o->descriptor_,
            o->offset_, o->bufs_.first(o->buffers_).data(),
            o->bufs_.first(o->buffers_).size(), o->ec_,
            o->bytes_transferred_);
      }
      else
      {
        return descriptor_ops::non_blocking_write_at(o->descriptor_,
            o->offset_, o->bufs_.buffers(), o->bufs_.count(),
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
  uint64_t offset_;
  ConstBufferSequence buffers_;
  buffer_sequence_adapter<boost::asio::const_buffer,
      ConstBufferSequence> bufs_;
};

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class io_uring_descriptor_write_at_op
  : public io_uring_descriptor_write_at_op_base<ConstBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_descriptor_write_at_op);

  io_uring_descriptor_write_at_op(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state, uint64_t offset,
      const ConstBufferSequence& buffers, Handler& handler,
      const IoExecutor& io_ex)
    : io_uring_descriptor_write_at_op_base<ConstBufferSequence>(
        success_ec, descriptor, state, offset, buffers,
        &io_uring_descriptor_write_at_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_descriptor_write_at_op* o
      (static_cast<io_uring_descriptor_write_at_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_WRITE_AT_OP_HPP

/* io_uring_descriptor_write_at_op.hpp
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
*/