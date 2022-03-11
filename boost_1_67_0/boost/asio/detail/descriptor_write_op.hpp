//
// detail/descriptor_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP
#define BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP

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

template <typename ConstBufferSequence>
class descriptor_write_op_base : public reactor_op
{
public:
  descriptor_write_op_base(int descriptor,
      const ConstBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_write_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_write_op_base* o(static_cast<descriptor_write_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    status result = descriptor_ops::non_blocking_write(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
      ? done : not_done;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_write",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  int descriptor_;
  ConstBufferSequence buffers_;
};

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class descriptor_write_op
  : public descriptor_write_op_base<ConstBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(descriptor_write_op);

  descriptor_write_op(int descriptor, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_write_op_base<ConstBufferSequence>(
        descriptor, buffers, &descriptor_write_op::do_complete),
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
    descriptor_write_op* o(static_cast<descriptor_write_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP

/* descriptor_write_op.hpp
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
*/