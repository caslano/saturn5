//
// detail/reactive_socket_recv_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class reactive_socket_recv_op_base : public reactor_op
{
public:
  reactive_socket_recv_op_base(socket_type socket,
      socket_ops::state_type state, const MutableBufferSequence& buffers,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recv_op_base::do_perform, complete_func),
      socket_(socket),
      state_(state),
      buffers_(buffers),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recv_op_base* o(
        static_cast<reactive_socket_recv_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = socket_ops::non_blocking_recv(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        (o->state_ & socket_ops::stream_oriented) != 0,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    if (result == done)
      if ((o->state_ & socket_ops::stream_oriented) != 0)
        if (o->bytes_transferred_ == 0)
          result = done_and_exhausted;

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recv",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  socket_ops::state_type state_;
  MutableBufferSequence buffers_;
  socket_base::message_flags flags_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class reactive_socket_recv_op :
  public reactive_socket_recv_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recv_op);

  reactive_socket_recv_op(socket_type socket, socket_ops::state_type state,
      const MutableBufferSequence& buffers, socket_base::message_flags flags,
      Handler& handler, const IoExecutor& io_ex)
    : reactive_socket_recv_op_base<MutableBufferSequence>(socket, state,
        buffers, flags, &reactive_socket_recv_op::do_complete),
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
    reactive_socket_recv_op* o(static_cast<reactive_socket_recv_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECV_OP_HPP

/* reactive_socket_recv_op.hpp
Iv2vni57YP/m6bJe7e9OP2Jx7wIXFrF/REzGmf+MmHyz+Zdj0ekkxP+d5PJb/z9JLml+WfjC3qEhs2FF9g2vtWHIJD9rR0zy84qIybj5lQUbXrR0GU9VUGbpTLPywKJBCp7t1lmjndwB96o12slvgHWdHadMjzvXCxnGnesHuj73agPDhovxNxaO2fZ7Q+jFG2O1jaDxAiPWXm01s7DY7gvd2GpjjYmM9kZwGW4CvXiT6EZzOnS/5dYCvQacFp7SwxzHa60+1ZqwY6NNnZZn3XoLSWL7zSzLa8Y5TdJe57Qss/t+NxcN6TFL9BtN175tEXGkF/G8Hhzr9ikPW0LjiQTKBOlbFXpfjzrCC3tlWfeP70L4W4OhBaRwtmFNH+lFtm+ErsPeFlorEfZ2YLjNgc5L2p60/YnvwP+2R32RtiM0PEPaToU2YGZO+uVcxDdprSJjtZ09XcZqu2hdTl4itqvH/PtjdzPMm42i8Riz3UOm97EywwwVHkPa9wgZfi/uyXplUW9pqEJLEP1zC/ZKcJu/vWPm+sB9wIr+Yoa8hMT2taxc1lES2y9i0m7NiJi0kz1gSw+aOcPeJZWt4r5ypmbjmRmcGNcVJU0W/Pz+2qZY0l9puPdhFjO+AQL2B1htotGsFz/RzAZA6+sDI9YkfTbr2BJn4kdYB2ld0kXPHMxMX95LaTqEdSi45xKaLr+3QtPZtuxtAUPUxN7ODDup2h19d/mhiqFpoWd6tT5WrXVabfcdf45i+gy9Ptb1FUxojfi5fuEmafSjh/SS0337uayTpuv/PKWTgxD/fKVT4tzlh+yjgYhLu39YwCqjtJ3ApHOKnj085OanUiNfTmxBwFCQxBYGTJ9NNBgwff/UopAhMdbXQx7HtXlFKwx+RJJnTcuHI94dpcfBywlOjyPtIwHXewgXB0zvIVyimP62dKTW87jslgZ8hiq7ZR6Ly+4dAddld1TEpOyODpguu2MCpsvunR6Ly67i8bjsjk1yKbuqx+OyG/V4XHa1gOuyq4cMZbeJYRkxmasfk7+993acddpAAkBt93LoU9U6NaXmf9ynUK/DY8zGGm0qk+NjMyis46a1Mz0Kxqsr1mRDQbHdxHR2/DPfWLHd5Jrteqz/mwk702Ou7JnJvBVz6qvs81MxL3YRZzYdx/uc+xrtSawxaE9vJ95EmPn0tvAC23XSdtoLPG+ZtIMXkM+VKRvyBPMTUpw8gbNtLW833Fk+q7VWGXPnHp9odR5s2fEqsXcFTI9PT7KMBlvuMWInewyPgb2bWXDlFLNTLPP7Y2KnOhb3u6dZFvS773F6ut99r+VBv/s+6NLssf37RUc4nO4PiN6dciMizFMyQ1OCfaRK4+WKi/pGSiMV88vY/E7l5z7sbE5031E/Ak0u5mfbj7KOq6ZY+xhraKZwd6WnxTG7/aG+nTQf9v7KNEfTgX2ixqbcN1JZMODP952hdK6M2CeqdDpJgX8s8P2UYHrMdxZrGJ+t6mTNYssUj93O1myiNW7Pcvg068HOds7zOcLoEfODuE03rIN/Rrg8Wmm6dR/nat7qtmt2PlJ0muEwPzcnp+DH84XZLJs8+GcBXCA2dl8Y9TkXsu5+i1wkf9Onb7qv9wD+PXgxGNzNc47Q8oT/LrEs8N/nRNf+I3apsBlheJ9XTId3mdLD8rjcsXR5XOF4ujyutDwojy+ILuWBZ66yTHxN+tXQpVry+3QN63HZyRm1PHdY2JVK/akzwK8Fw10DFlO811lWz7xnroeeOhv8BrAwni9ZvRXH82UwO16zd1PcaHRa7YD38Cb8rc9IvhmaPjP9FmjyOYBtvwIdnwIojq+yRnce0B5Q9zdiQdxfdzrFxHs=
*/