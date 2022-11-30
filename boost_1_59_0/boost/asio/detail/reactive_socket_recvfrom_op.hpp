//
// detail/reactive_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

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

template <typename MutableBufferSequence, typename Endpoint>
class reactive_socket_recvfrom_op_base : public reactor_op
{
public:
  reactive_socket_recvfrom_op_base(const boost::system::error_code& success_ec,
      socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(success_ec,
        &reactive_socket_recvfrom_op_base::do_perform, complete_func),
      socket_(socket),
      protocol_type_(protocol_type),
      buffers_(buffers),
      sender_endpoint_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recvfrom_op_base* o(
        static_cast<reactive_socket_recvfrom_op_base*>(base));

    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    std::size_t addr_len = o->sender_endpoint_.capacity();
    status result;
    if (bufs_type::is_single_buffer)
    {
      result = socket_ops::non_blocking_recvfrom1(
          o->socket_, bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(), o->flags_,
          o->sender_endpoint_.data(), &addr_len,
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = socket_ops::non_blocking_recvfrom(o->socket_,
          bufs.buffers(), bufs.count(), o->flags_,
          o->sender_endpoint_.data(), &addr_len,
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }

    if (result && !o->ec_)
      o->sender_endpoint_.resize(addr_len);

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recvfrom",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  int protocol_type_;
  MutableBufferSequence buffers_;
  Endpoint& sender_endpoint_;
  socket_base::message_flags flags_;
};

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_recvfrom_op :
  public reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recvfrom_op);

  reactive_socket_recvfrom_op(const boost::system::error_code& success_ec,
      socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>(
        success_ec, socket, protocol_type, buffers, endpoint, flags,
        &reactive_socket_recvfrom_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_socket_recvfrom_op* o(
        static_cast<reactive_socket_recvfrom_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

/* reactive_socket_recvfrom_op.hpp
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
*/