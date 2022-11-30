//
// detail/reactive_socket_sendto_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Endpoint>
class reactive_socket_sendto_op_base : public reactor_op
{
public:
  reactive_socket_sendto_op_base(const boost::system::error_code& success_ec,
      socket_type socket, const ConstBufferSequence& buffers,
      const Endpoint& endpoint, socket_base::message_flags flags,
      func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_sendto_op_base::do_perform, complete_func),
      socket_(socket),
      buffers_(buffers),
      destination_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_sendto_op_base* o(
        static_cast<reactive_socket_sendto_op_base*>(base));

    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    status result;
    if (bufs_type::is_single_buffer)
    {
      result = socket_ops::non_blocking_sendto1(o->socket_,
          bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(), o->flags_,
          o->destination_.data(), o->destination_.size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = socket_ops::non_blocking_sendto(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->destination_.data(), o->destination_.size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_sendto",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  ConstBufferSequence buffers_;
  Endpoint destination_;
  socket_base::message_flags flags_;
};

template <typename ConstBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_sendto_op :
  public reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_sendto_op);

  reactive_socket_sendto_op(const boost::system::error_code& success_ec,
      socket_type socket, const ConstBufferSequence& buffers,
      const Endpoint& endpoint, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_sendto_op_base<ConstBufferSequence, Endpoint>(
        success_ec, socket, buffers, endpoint, flags,
        &reactive_socket_sendto_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_sendto_op* o(static_cast<reactive_socket_sendto_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_SENDTO_OP_HPP

/* reactive_socket_sendto_op.hpp
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
*/