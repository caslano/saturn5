//
// detail/io_uring_descriptor_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_OP_HPP
#define BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_OP_HPP

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

template <typename MutableBufferSequence>
class io_uring_descriptor_read_op_base : public io_uring_operation
{
public:
  io_uring_descriptor_read_op_base(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state,
      const MutableBufferSequence& buffers, func_type complete_func)
    : io_uring_operation(success_ec,
        &io_uring_descriptor_read_op_base::do_prepare,
        &io_uring_descriptor_read_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      state_(state),
      buffers_(buffers),
      bufs_(buffers)
  {
  }

  static void do_prepare(io_uring_operation* base, ::io_uring_sqe* sqe)
  {
    io_uring_descriptor_read_op_base* o(
        static_cast<io_uring_descriptor_read_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      ::io_uring_prep_poll_add(sqe, o->descriptor_, POLLIN);
    }
    else if (o->bufs_.is_single_buffer && o->bufs_.is_registered_buffer)
    {
      ::io_uring_prep_read_fixed(sqe, o->descriptor_,
          o->bufs_.buffers()->iov_base, o->bufs_.buffers()->iov_len,
          0, o->bufs_.registered_id().native_handle());
    }
    else
    {
      ::io_uring_prep_readv(sqe, o->descriptor_,
          o->bufs_.buffers(), o->bufs_.count(), -1);
    }
  }

  static bool do_perform(io_uring_operation* base, bool after_completion)
  {
    io_uring_descriptor_read_op_base* o(
        static_cast<io_uring_descriptor_read_op_base*>(base));

    if ((o->state_ & descriptor_ops::internal_non_blocking) != 0)
    {
      if (o->bufs_.is_single_buffer)
      {
        return descriptor_ops::non_blocking_read1(
            o->descriptor_, o->bufs_.first(o->buffers_).data(),
            o->bufs_.first(o->buffers_).size(), o->ec_,
            o->bytes_transferred_);
      }
      else
      {
        return descriptor_ops::non_blocking_read(
            o->descriptor_, o->bufs_.buffers(), o->bufs_.count(),
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
  MutableBufferSequence buffers_;
  buffer_sequence_adapter<boost::asio::mutable_buffer,
      MutableBufferSequence> bufs_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class io_uring_descriptor_read_op
  : public io_uring_descriptor_read_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(io_uring_descriptor_read_op);

  io_uring_descriptor_read_op(const boost::system::error_code& success_ec,
      int descriptor, descriptor_ops::state_type state,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : io_uring_descriptor_read_op_base<MutableBufferSequence>(success_ec,
        descriptor, state, buffers, &io_uring_descriptor_read_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    io_uring_descriptor_read_op* o
      (static_cast<io_uring_descriptor_read_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_IO_URING_DESCRIPTOR_READ_OP_HPP

/* io_uring_descriptor_read_op.hpp
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
*/