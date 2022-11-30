//
// detail/io_uring_descriptor_read_at_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_AT_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_AT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/io_uring_operation.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class io_uring_descriptor_read_at_op_base : public io_uring_operation
{
public:
  io_uring_descriptor_read_at_op_base(
      const boost::system::error_code& success_ec, int descriptor,
      descriptor_ops::state_type state, uint64_t offset,
      const MutableBufferSequence& buffers, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_descriptor_read_at_op_base::do_prepare,
        &io_uring_descriptor_read_at_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      state_(state),
      offset_(offset),
      buffers_(buffers),
      bufs_(buffers)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_descriptor_read_at_op_base* o(
        static_cast<io_uring_descriptor_read_at_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->descriptor_, POLLIN);
    }
    else if (o->bufs_.is_single_buffer && o->bufs_.is_registered_buffer)
    {
      ::io_uring_prep_read_fixed(sqe, o->descriptor_,
          o->bufs_.buffers()->iov_base, o->bufs_.buffers()->iov_len,
          o->offset_, o->bufs_.registered_id().native_handle());
    }
    else
    {
      ::io_uring_prep_readv(sqe, o->descriptor_,
          o->bufs_.buffers(), o->bufs_.count(), o->offset_);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_descriptor_read_at_op_base* o(
        static_cast<io_uring_descriptor_read_at_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      if (o->bufs_.is_single_buffer)
      {
        return descriptor_ops::non_blocking_read_at1(o->descriptor_,
            o->offset_, o->bufs_.first(o->buffers_).data(),
            o->bufs_.first(o->buffers_).size(), o->ec_,
            o->bytes_transferred_);
      }
      else
      {
        return descriptor_ops::non_blocking_read_at(o->descriptor_,
            o->offset_, o->bufs_.buffers(), o->bufs_.count(),
            o->ec_, o->bytes_transferred_);
      }
    }
    else if (after_completion)
    {
      if (!o->ec_ && o->bytes_transferred_ == 0)
        o->ec_ = boost::asio::error::eof;
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
  MutableBufferSequence buffers_;
  buffer_sequence_adapter<boost::asio::mutable_buffer,
      MutableBufferSequence> bufs_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class io_uring_descriptor_read_at_op
  : public io_uring_descriptor_read_at_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_descriptor_read_at_op);

  io_uring_descriptor_read_at_op(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state, uint64_t offset,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_descriptor_read_at_op_base<MutableBufferSequence>(
        success_ec, descriptor, state, offset, buffers,
        &io_uring_descriptor_read_at_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_descriptor_read_at_op* o
      (static_cast<io_uring_descriptor_read_at_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_AT_OP_HPP

/* io_uring_descriptor_read_at_op.hpp
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
*/