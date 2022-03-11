//
// detail/descriptor_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP
#define BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class descriptor_read_op_base : public reactor_op
{
public:
  descriptor_read_op_base(int descriptor,
      const MutableBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_read_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_read_op_base* o(static_cast<descriptor_read_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = descriptor_ops::non_blocking_read(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
      ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_read",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  int descriptor_;
  MutableBufferSequence buffers_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class descriptor_read_op
  : public descriptor_read_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(descriptor_read_op);

  descriptor_read_op(int descriptor, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_read_op_base<MutableBufferSequence>(
        descriptor, buffers, &descriptor_read_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_read_op* o(static_cast<descriptor_read_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP

/* descriptor_read_op.hpp
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
*/